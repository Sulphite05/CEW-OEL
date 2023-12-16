// This C program is using the libcurl library to make an HTTP request to the OpenWeatherMap API, 
// retrieve weather data, and write the response to a local file. 

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include "headers/cJSON.h"

char* cont;

typedef struct {
    float temperature;
    float humidity;

} EnvironmentalData;


static size_t WriteFileCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    FILE *fp = (FILE *)userp;
    size_t written = fwrite(contents, size, nmemb, fp);
    cont = contents;
    return written;
}


EnvironmentalData parse_data(const char* json) {

    cJSON *root = cJSON_Parse(json);
    cJSON_Print(root);
    EnvironmentalData data;

    if (root != NULL) {
        cJSON *mainObject = cJSON_GetObjectItem(root, "main");

        // Check if the "main" object and its properties exist
        if (mainObject != NULL) {
            cJSON *tempItem = cJSON_GetObjectItem(mainObject, "temp");
            cJSON *humidityItem = cJSON_GetObjectItem(mainObject, "humidity");

            // Check if the temperature and humidity properties exist
            if (tempItem != NULL && humidityItem != NULL) {
                data.temperature = tempItem->valuedouble;
                data.humidity = humidityItem->valuedouble;
            } else {
                // Handle missing properties (optional)
                // You can set default values or handle the case as needed.
                printf("missing properties error");
                data.temperature = 0.0;
                data.humidity = 0.0;
            }
        } else {
            // Handle missing "main" object (optional)
            // You can set default values or handle the case as needed.
            printf("missing main object");
            data.temperature = 0.0;
            data.humidity = 0.0;
        }

        cJSON_Delete(root);
    } else {
        // Handle JSON parsing error (optional)
        // You can log an error message or handle the case as needed.
         const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
        printf("JSON parsing error at position: %ld\n", error_ptr - json);
    } else {
        printf("JSON parsing error\n");
    }

    data.temperature = 0.0;
    data.humidity = 0.0;
}


    return data;
}


void analyze_data(EnvironmentalData data) {

    if (data.temperature > 50.0) {
        printf("High temperature alert: %f\n", data.temperature);
    }
}

void save_data(EnvironmentalData data) {
    FILE *fp = fopen("environment_data.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "Temperature: %f, Humidity: %f\n", data.temperature, data.humidity);
        fclose(fp);
    } else {
        // Handle file opening error
        printf("Failed to open file for writing.\n");
    }
}


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
    return 0;
}