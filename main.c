// This C program is using the libcurl library to make an HTTP request to the OpenWeatherMap API,
// retrieve weather data, and write the response to a local file.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    FILE *fp = fopen("environment_data.txt", "a");
    if (fp != NULL)
    {
        fprintf(fp, "Temperature: %5.2f, Humidity: %f, WeatherDescription: %s, Visibility: %f\n", data.temperature, data.humidity, data.weatherDes, data.visibility);
        fclose(fp);
    }
    else
    {
        // Handle file opening error
        printf("Failed to open file for writing data\n");
    }
}

int main(void)
{
    int i = 0;
    EnvironmentalData *data = NULL; // an array of struct EnvironmentalData

    char* cont = retrieveData();
    printf("%s", cont);
    data = realloc(data, sizeof(EnvironmentalData) * (i+1));
    data[i] = parse_data(cont); // retrieves global variable containing content of current query
    check_anomaly(data[i]);
    save_data(data[i]);
    i += 1;
    return 0;
}

// command to link all the wrkspace files before execution
// gcc bashCalls.c main.c  -o main libcjson.a  -lcurl -lm
// main         : object file
// main.c       : source file   linked with
// libcjson.a   : cjson library linked with
// -lcurl       : curl  library linked with
// -lm          : math  library linked with
// execuion command
// ./main
