#!/bin/bash

data_file="enviro_store.json"

# Get last Monday
last_monday=$(date +"%Y-%m-%d" -d "last monday")

# Get this Sunday
this_sunday=$(date +"%Y-%m-%d" -d "this sunday")

# Extract values using jq
temperatures=$(jq '.[] | select(.Date >= "'$last_monday'" and .Date <= "'$this_sunday'") | .Temperature' "$data_file")
humidity=$(jq '.[] | select(.Date >= "'$last_monday'" and .Date <= "'$this_sunday'") | .Humidity' "$data_file")
visibility=$(jq '.[] | select(.Date >= "'$last_monday'" and .Date <= "'$this_sunday'") | .Visibility' "$data_file")


# Calculate the average using awk
average_temperature=$(echo "$temperatures" | awk '{ sum += $1 } END { printf "%.2f\n", sum / NR }')
average_humidity=$(echo "$humidity" | awk '{ sum += $1 } END { printf "%.2f\n", sum / NR }')
average_visibility=$(echo "$visibility" | awk '{ sum += $1 } END { printf "%.2f\n", sum / NR }')


# Calculate the max and min using awk
max_temp=$(echo "$temperatures" | awk 'BEGIN {max = -inf} {if ($1 > max) max = $1} END {printf "%.2f\n", max}')
min_temp=$(echo "$temperatures" | awk 'BEGIN {min = inf} {if (min == inf || $1 < min) min = $1} END {printf "%.2f\n", min}')


max_humidity=$(echo "$humidity" | awk 'BEGIN {max = -inf} {if ($1 > max) max = $1} END {printf "%.2f\n", max}')
min_humidity=$(echo "$humidity" | awk 'BEGIN {min = inf} {if (min == inf || $1 < min) min = $1} END {printf "%.2f\n", min}')

max_visibility=$(echo "$visibility" | awk 'BEGIN {max = -inf} {if ($1 > max) max = $1} END {printf "%.2f\n", max}')
min_visibility=$(echo "$visibility" | awk 'BEGIN {min = inf} {if (min == inf || $1 < min) min = $1} END {printf "%.2f\n", min}')


# Extract data for the week

data=$(jq '.[] | select(.Date >= "'$last_monday'" and .Date <= "'$this_sunday'")' "enviro_store.json") # this data is in the form of separate dictionaries

# Format data
new_data=$(jq -s '.' <<<$data) # formats dictionary objects in the array separated by commas
formatted_data=$(jq -r '.[] | [.Date, .Time, .Temperature, .Humidity, .Visibility, .["Weather Description"]] | join("\t\t\t\t")' <<< "$new_data" | column -t -s $'\t\t\t\t')  # formats data into columns

# Generate the report
cat << EOF > report.txt

                  *********************************************         
                  *********************************************

                  WEATHER REPORT FOR $last_monday TILL $this_sunday

                  *********************************************
                  *********************************************

Average Temperature: $average_temperature °C
Maximum Temperature: $max_temp°C
Minimum Temperature: $min_temp°C

Average Humidity: $average_humidity%
Maximum Humidity: $max_humidity%
Minimum Humidity: $min_humidity%

Average Visibilty: $average_visibility m
Maximum Visibility: $max_visibility m
Minimum Visibility: $min_visibility m

DATA POINTS:
____________


   Date             Time             Temperature         Humidity   Visibility  Description

$formatted_data
EOF

echo "Report generated: report.txt"
echo "Sending Report"

mutt -s "Weekly Report" -e "set content_type=text/plain" -a "report.txt" -- aqibaabdulqadir@gmail.com <<EOF
Please review attached report.
EOF

