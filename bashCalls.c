#include <stdio.h>
#include <string.h>
#include "headers/bashCalls.h"

char* retrieveData(){
    
    FILE *fp = popen("/bin/bash data_automation.sh", "r");
    if (fp == NULL) {
        perror("Error opening pipe");
    }

    // Read the output of the Bash script
    char buffer[4096];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), fp);
    buffer[bytesRead] = '\0';

    // Close the pipe
    pclose(fp);

    // Allocate memory for the result and copy the content
    char* result = strdup(buffer);

    return result;
}
