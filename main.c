// This C program is using the libcurl library to make an HTTP request to the OpenWeatherMap API,
// retrieve weather data, and write the response to a local file.

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include "headers/cJSON.h"
#include "headers/bashCalls.h"


typedef struct
{ // struct to store Environmental data
    float temperature;
    float humidity;
    char* weatherDes;
    float visibility;

} EnvironmentalData;


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


        // Check if the "main" object and its properties exist
        if (mainObject != NULL && weatherObject != NULL)
        {
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
        }
        else
        {
            // Handle missing "main" object
            printf("missing main object");
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

void check_and_alert(EnvironmentalData data)
{
    if (data.temperature > 50.0)
    {
        system("echo 'Temperature alert' | mail -s 'Alert' user@example.com");

    }
}

void analyze_data(EnvironmentalData data)
{

    if (data.temperature > 30)
    {
        printf("High temperature alert: %f\n", data.temperature);
    }
}

void save_data(EnvironmentalData data)
{
    FILE *fp = fopen("environment_data.txt", "a");
<<<<<<< HEAD
    if (fp != NULL) {
        time_t t = time(NULL);
        struct tm *timeinfo = localtime(&t);
        char timestamp[25]; 
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %I:%M:%S %p", timeinfo);

        fprintf(fp, "%s, Temperature: %f, Humidity: %f\n", timestamp, data.temperature, data.humidity);
=======
    if (fp != NULL)
    {
        fprintf(fp, "Temperature: %5.2f, Humidity: %f, WeatherDescription: %s, Visibility: %f\n", data.temperature, data.humidity, data.weatherDes, data.visibility);
>>>>>>> 6b0270c (On branch main)
        fclose(fp);
    }
    else
    {
        // Handle file opening error
        printf("Failed to open file for writing data\n");
    }
}

<<<<<<< HEAD
int main(void) {

    FILE *fp;
    char *url = "http://api.openweathermap.org/data/2.5/weather?q=Karachi&appid=ac40257f82101fbacf3f2dee95130387";
    char outfilename[FILENAME_MAX] = "output.json";
    char *receivedData = NULL;

    // beginning of CURL specific functions to retrieve data
    CURL *curl; 
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);                           // sets option of URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback);   // sets option of write function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);                      // sets option of write data stream
        res = curl_easy_perform(curl);                                      // performs the http request
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    else{
        printf("Failed to initialise CURL");
    }
    // End of CURL specific query setter

    EnvironmentalData data = parse_data(cont);
    analyze_data(data);
    save_data(data);
    free(receivedData);
=======
int main(void)
{
    int i = 0;
    EnvironmentalData *data = NULL; // an array of struct EnvironmentalData

    char* cont = retrieveData();
    printf("%s", cont);
    data = realloc(data, sizeof(EnvironmentalData) * (i+1));
    data[i] = parse_data(cont); // retrieves global variable containing content of current query
    analyze_data(data[i]);
    save_data(data[i]);
    i += 1;
>>>>>>> 6b0270c (On branch main)
    return 0;
}

// command to link all the wrkspace files before execution
// gcc -o main main.c libcjson.a -lcurl -lm
// main         : object file
// main.c       : source file   linked with
// libcjson.a   : cjson library linked with
// -lcurl       : curl  library linked with
// -lm          : math  library linked with
// execuion command
// ./main
