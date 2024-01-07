#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/bashCalls.h"

char *retrieveData()
{

    FILE *fp = popen("/bin/bash data_automation.sh", "r");
    if (fp == NULL)
    {
        perror("Error opening pipe");
    }

    // Read the output of the Bash script
    char buffer[4096];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), fp);
    buffer[bytesRead] = '\0';

    // Close the pipe
    pclose(fp);

    // Allocate memory for the result and copy the content
    char *result = strdup(buffer);

    return result;
}

void check_anomaly(EnvironmentalData data)
{
    if (data.temperature > 30 || data.visibility < 1000)
    {
        const char *recipient = "aqibaabdulqadir@gmail.com";
        const char *subject;
        char body[512];

        if (data.temperature > 30)
        {
            
            subject = "HIGH Temperature Alert";
            printf("%s", subject);
            snprintf(body, sizeof(body),
                     "The current temperature is %.2f°C.\n"
                     "Please take necessary actions.\n",
                     data.temperature);
        }
        if (data.visibility < 1000)
        {
            subject = "LOW Visibility Alert";
            printf("%s", subject);
            snprintf(body, sizeof(body),
                     "The current visibility is %.2fm.\n"
                     "Please take necessary actions.\n",
                     data.visibility);
        }

        // Build the mutt command
        char command[1024];
        snprintf(command, sizeof(command), "mutt -s \"%s\" -- %s <<EOF\n%s\nEOF", subject, recipient, body);

        // Execute the mutt command
        int result = system(command);

        if (result == 0)
        {
            printf("Email sent successfully.\n");
        }
        else
        {
            fprintf(stderr, "Failed to send email.\n");
        }
    }
}
