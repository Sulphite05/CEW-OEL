typedef struct
{ // struct to store Environmental data
    float temperature;
    float humidity;
    char* weatherDes;
    float visibility;

} EnvironmentalData;

#ifndef BASHCALLS_H
#define BASHCALLS_H
// Function declarations
char* retrieveData();
void check_anomaly(EnvironmentalData data);
#endif

