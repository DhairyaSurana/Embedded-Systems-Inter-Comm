#include "cJSON.h"
#include "uart_term.h"
#include <stdbool.h>

typedef struct dev_data {

    // Common values
    char* id;
    int pub;
    int rec;

    int time;

    // ultra
    int dist;

    // pixy
    int x;
    int y;
    int height;
    int width;
    int signature;

    char* status; // ultra and arm
    char* atDestination; // rover

    char* topic1;
    char* topic2;
    char* topic3;
    char* topic4;

} dev_data;

/* Prints out struct values to UART */
void printDevData(dev_data d);

/* Wrapper for cJSON_GetObjectItemCaseSensitive function*/
int getIntValue(cJSON *obj, char *field);

char *getStrValue(cJSON *obj, char *field);

/* Returns a struct with values from str string (JSON format) */
struct dev_data getJSONData(char *str);
