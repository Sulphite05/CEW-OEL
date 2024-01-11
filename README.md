# API Reporting System

<<<<<<< HEAD
## Overview

Welcome to the API Reporting System! This system is designed to facilitate data storage, API communication, email functionality, and data analysis. The key components used in this system are C language for programming, [cJSON](https://github.com/DaveGamble/cJSON) for data storage, [libcurl](https://curl.se/libcurl/) for API communication, [mutt](https://mutt.org/) for mailing, [jq](https://stedolan.github.io/jq/) for data analysis, and [gnuplot](http://www.gnuplot.info/) for data visualisation.

## Requirements

Before getting started, make sure you have the following dependencies installed:

1. **cJSON**: A lightweight JSON library for data storage.

    [cJSON GitHub](https://github.com/DaveGamble/cJSON)

2. **libcurl**: A library for making HTTP requests, essential for API communication.

    [libcurl](https://curl.se/libcurl/)

3. **mutt**: A command-line email client for sending emails.

    [mutt](https://mutt.org/)

4. **jq**: A lightweight and flexible command-line JSON processor for data analysis.

    [jq](https://stedolan.github.io/jq/)

5. **gnuplot**: A library to process data for visualisation through graphs

    [gnuplot](http://www.gnuplot.info/)


## Usage

### 1. cJSON (Data Storage)

cJSON is integrated into the system for efficient data storage. You can use cJSON to serialize and deserialize JSON data. Here's a simple example in C:

```c
#include <stdio.h>
#include "cJSON.h"

int main() {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "name", "John Doe");
    cJSON_AddNumberToObject(root, "age", 30);

    char *jsonString = cJSON_Print(root);

    // Store jsonString as needed

    cJSON_Delete(root);
    free(jsonString);

    return 0;
}
```

### 2. libcurl (API Communication)

libcurl is utilized for making API requests. You can easily integrate it into your code to communicate with external APIs. Here's a basic example in C:

```c
#include <stdio.h>
#include <curl/curl.h>

int main() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.example.com/data");
        
        // Set other options as needed
        
        res = curl_easy_perform(curl);
        
        // Check for errors
        
        curl_easy_cleanup(curl);
    }

    return 0;
}
```

### 3. mutt (Mailing)

For mailing functionality, mutt can be used to send emails from the command line. You can create and send emails with attachments as needed. Here's a basic example:

```bash
echo "Body of the email" | mutt -s "Subject" -a attachment.txt -- recipient@example.com
```

### 4. jq (Data Analysis)

jq is employed for data analysis. You can use it to filter, transform, and manipulate JSON data from the command line. Here's a simple example:

```bash
cat data.json | jq '.users | .[] | select(.age > 25) | .name'
```

### 4. gnuplot (Data Visualisation)

gnuplot is employed for data visualisation. You can use it to plot data from the dat files using gp files and the command line. Here's a simple example:

```bash
gnuplot plot_script.gp
```

## Project Usage

This API Reporting System is a university project created for educational purposes. You are free to use, modify, and distribute the code for non-commercial, educational, and research purposes. However, please be mindful of academic integrity and give appropriate credit if you use or reference this project in your work.

## Contributors

Aqiba Abdul Qadir   CS22003 </br>
Mehwish Hussain     CS22016 </br>
Tooba Aftab         CS22020

Happy coding!
=======
# API Reporting System

## Overview

Welcome to the API Reporting System! This system is designed to facilitate data storage, API communication, email functionality, and data analysis. The key components used in this system are [cJSON](https://github.com/DaveGamble/cJSON) for data storage, [libcurl](https://curl.se/libcurl/) for API communication, [mutt](https://mutt.org/) for mailing, and [jq](https://stedolan.github.io/jq/) for data analysis.

## Requirements

Before getting started, make sure you have the following dependencies installed:

1. **cJSON**: A lightweight JSON library for data storage.

    [cJSON GitHub](https://github.com/DaveGamble/cJSON)

2. **libcurl**: A library for making HTTP requests, essential for API communication.

    [libcurl](https://curl.se/libcurl/)

3. **mutt**: A command-line email client for sending emails.

    [mutt](https://mutt.org/)

4. **jq**: A lightweight and flexible command-line JSON processor for data analysis.

    [jq](https://stedolan.github.io/jq/)

<<<<<<< HEAD
>>>>>>> 8d521ca (On branch main)
=======
## Usage

### 1. cJSON (Data Storage)

cJSON is integrated into the system for efficient data storage. You can use cJSON to serialize and deserialize JSON data.
>>>>>>> 9193553 (On branch main)
