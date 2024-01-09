// This C program is using the libcurl library to make an HTTP request to the OpenWeatherMap API,
// retrieve weather data, and write the response to a local file.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "headers/cJSON.h"
#include "headers/bashCalls.h"


EnvironmentalData parse_data(const char *json)
{

    cJSON *root = cJSON_Parse(json);
    cJSON_Print(root);
    EnvironmentalData data;

    if (root != NULL)
    {
        cJSON *mainObject = cJSON_GetObjectItem(root, "main");                      //hashmap
        cJSON *weatherObject = cJSON_GetObjectItemCaseSensitive(root, "weather");   //array
        cJSON *visibiltyObject = cJSON_GetObjectItem(root, "visibility");

        cJSON *tempItem = cJSON_GetObjectItem(mainObject, "temp");
        cJSON *humidityItem = cJSON_GetObjectItem(mainObject, "humidity");
        cJSON *first_weather_entry = cJSON_GetArrayItem(weatherObject, 0);

        // Get the "description" field from the first element
        cJSON *description = cJSON_GetObjectItemCaseSensitive(first_weather_entry, "main");
        // Check if the temperature and humidity properties exist
        if (tempItem != NULL && humidityItem != NULL && description != NULL && visibiltyObject != NULL)
        {
            data.temperature = tempItem->valuedouble - 273;
            data.humidity = humidityItem->valuedouble;
            data.weatherDes = strdup(description->valuestring); // Copy the description string
            data.visibility = visibiltyObject->valuedouble;
        }
        else
        {
            // Handle missing properties
            printf("missing properties error");
            data.temperature = 0.0;
            data.humidity = 0.0;
            data.weatherDes = "NULL";
            data.visibility = 0.0;
        }

        cJSON_Delete(root);
    }
    else
    {
        // Handle JSON parsing error
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            printf("JSON parsing error at position: %ld\n", error_ptr - json);
        }
        else
        {
            printf("JSON parsing error\nCheck for Wifi connection\n");
        }

        data.temperature = 0.0;
        data.humidity = 0.0;
        data.weatherDes = "NULL";
        data.visibility = 0.0;
    }
    return data;
}

void save_data(EnvironmentalData data)
{
    printf("Yes");
    const char *file_path = "enviro_store.json";

    // Read the existing JSON file
    FILE *file = fopen(file_path, "r");
    if (!file) {
        fprintf(stderr, "Error opening file for reading\n");
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file); // returns current position of stream
    fseek(file, 0, SEEK_SET);

    char *json_content = (char *)malloc(file_size + 1);
    fread(json_content, 1, file_size, file);
    json_content[file_size] = '\0';

    fclose(file);

    // Parse the existing JSON data
    cJSON *root = cJSON_Parse(json_content);
    free(json_content);

    if (!root) {
        fprintf(stderr, "Error parsing JSON\n");
    }

    time_t raw_time;
    struct tm *current_time;

    time(&raw_time);
    current_time = localtime(&raw_time);

    // Add date and time to cJSON object
    char date_buffer[11]; // "YYYY-MM-DD\0"
    char time_buffer[9];  // "HH:MM:SS\0"

    strftime(date_buffer, sizeof(date_buffer), "%Y-%m-%d", current_time);
    strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", current_time);

    // Append new records to the JSON array
    cJSON *new_records = cJSON_CreateObject();
    cJSON_AddStringToObject(new_records, "Date", date_buffer);
    cJSON_AddStringToObject(new_records, "Time", time_buffer);
    cJSON_AddNumberToObject(new_records, "Temperature", data.temperature);
    cJSON_AddNumberToObject(new_records, "Humidity", data.humidity);
    cJSON_AddNumberToObject(new_records, "Visibility", data.visibility);
    cJSON_AddStringToObject(new_records, "Weather Description", data.weatherDes);

    cJSON_AddItemToArray(root, new_records);
    
    // Write the updated JSON data back to the file
    file = fopen(file_path, "w");
    if (!file) {
        fprintf(stderr, "Error opening file for writing\n");
        cJSON_Delete(root);
    }

    char *json_string = cJSON_Print(root);
    fprintf(file, "%s", json_string);
    fclose(file);
    free(json_string);

    cJSON_Delete(root);

    printf("New records have been appended to %s\n", file_path);

}

int main(void){
    EnvironmentalData data; // an array of struct EnvironmentalData

    char* cont = retrieveData();
    printf("%s", cont);
    data = parse_data(cont); // retrieves global variable containing content of current query
    check_anomaly(data);
    save_data(data);

    return 0;
}

// command to link all the wrkspace files before execution
// gcc bashCalls.c main.c  -o main libcjson.a -lm
// main         : object file
// main.c       : source file   linked with
// libcjson.a   : cjson library linked with
// -lcurl       : curl  library linked with
// -lm          : math  library linked with
// execuion command
// ./main
