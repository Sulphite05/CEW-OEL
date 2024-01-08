#!/bin/bash
gcc bashCalls.c main.c -o main libcjson.a  -lcurl -lm
./main