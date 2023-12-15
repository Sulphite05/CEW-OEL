// This C program is using the libcurl library to make an HTTP request to the OpenWeatherMap API, 
// retrieve weather data, and write the response to a local file. 

#include <stdio.h>
#include <curl/curl.h>

typedef struct {
    float temperature;
    float humidity;

} EnvironmentalData;

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);  // size_t is a special unsigned integer type
    // It stores the maximum size of a theoretically possible array or an object
    return written;
}

// EnvironmentalData parse_data(const char* json);

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
    }
}

int main(void) {
    CURL *curl; 
    FILE *fp;
    CURLcode res;
    char *url = "http://api.openweathermap.org/data/2.5/weather?q=Pakistan&appid=ac40257f82101fbacf3f2dee95130387";
    char outfilename[FILENAME_MAX] = "output.json";

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);                   // sets options of URL, write function, write data stream
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);  
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    // EnvironmentalData data = parse_data(outfilename);
    // analyze_data(data);
    // save_data(data);
    return 0;
}
