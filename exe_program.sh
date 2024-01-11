#!/bin/bash
ping -c 1 8.8.8.8 && gcc bashCalls.c main.c -o main libcjson.a -lm && ./main
