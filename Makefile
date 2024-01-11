.PHONY: all

PING_COMMAND = ping -c 1 8.8.8.8
GCC_COMMAND = gcc
COMPILATION_OPTIONS = bashCalls.c main.c -o main libcjson.a -lm
RUN_COMMAND = ./main

all: ping compile run

ping:
	@$(PING_COMMAND)

compile:
	@$(GCC_COMMAND) $(COMPILATION_OPTIONS)

run:
	@$(RUN_COMMAND)
