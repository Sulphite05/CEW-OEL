#!/bin/bash
date >> raw_data.txt
data=$(curl "http://api.openweathermap.org/data/2.5/weather?q=Karachi&appid=ac40257f82101fbacf3f2dee95130387")
echo $data >> raw_data.txt
echo $data
echo -e '\n\n' >> raw_data.txt
