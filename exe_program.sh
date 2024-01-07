#!/bin/bash
touch /home/aqiba/Desktop/file.txt
gcc bashCalls.c main.c -o main libcjson.a  -lcurl -lm
./main