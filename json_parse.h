#include "cJSON.h"
#include "uart_term.h"

typedef struct dev_data {

    // Common values
    int id;
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

    int status; // ultra and arm
    int atDestination; // rover

} dev_data;

/* Prints out struct values to UART */
void printDevData(dev_data d);

/* Wrapper for cJSON_GetObjectItemCaseSensitive function*/
int getValue(cJSON *obj, char *field);

/* Returns a struct with values from str string (JSON format) */
struct dev_data getJSONData(char *str);
