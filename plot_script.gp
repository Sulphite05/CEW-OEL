# plot_script.gp
set terminal pngcairo enhanced font 'Verdana,10'
set output 'weather_plot.png'

set datafile separator " "
set xdata time
set timefmt "%Y-%m-%d %H:%M:%S"
set format x "%a"

set multiplot layout 3,1

start_date = system("awk 'NR==2 {print $1}' weather_data.dat")
end_date = system("awk 'END {print $1}' weather_data.dat")

set key outside


# Temperature
set title sprintf("Temperature Data from %s to %s", start_date, end_date)
set ylabel "Temperature (°C)"
plot 'weather_data.dat' using 1:3 with linespoints title 'Temperature'

# Humidity
set title sprintf("Humidity Data from %s to %s", start_date, end_date)
set ylabel "Humidity (%)"
plot 'weather_data.dat' using 1:5 with linespoints title 'Humidity'

# Visibility
set title sprintf("Visibility Data from %s to %s", start_date, end_date)
set ylabel "Visibility (m)"
plot 'weather_data.dat' using 1:5 with linespoints title 'Visibility'

unset multiplot
