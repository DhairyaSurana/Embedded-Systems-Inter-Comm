#include "json_parse.h"
#include <string.h>


/* Prints out struct values to UART */
void printDevData(dev_data d) {

    UART_PRINT("DEVICE STRUCT {\r\n\r\n");

    UART_PRINT("    id: ");
    UART_PRINT("%s", d.id);
    UART_PRINT("\r\n");

    UART_PRINT("    pub: ");
    UART_PRINT("%d", d.pub);
    UART_PRINT("\r\n");

    UART_PRINT("    rec: ");
    UART_PRINT("%d", d.rec);
    UART_PRINT("\r\n");

    UART_PRINT("    time: ");
    UART_PRINT("%d", d.time);
    UART_PRINT("\r\n");

    UART_PRINT("    status: ");
    UART_PRINT("%s", d.status);
    UART_PRINT("\r\n");

    UART_PRINT("    atDestination: ");
    UART_PRINT("%s", d.atDestination);
    UART_PRINT("\r\n");

    UART_PRINT("    x: ");
    UART_PRINT("%d", d.x);
    UART_PRINT("\r\n");

    UART_PRINT("    y: ");
    UART_PRINT("%d", d.y);
    UART_PRINT("\r\n");

    UART_PRINT("    width: ");
    UART_PRINT("%d", d.width);
    UART_PRINT("\r\n");

    UART_PRINT("    height: ");
    UART_PRINT("%d", d.height);
    UART_PRINT("\r\n");


    UART_PRINT("    distance: ");
    UART_PRINT("%d", d.dist);
    UART_PRINT("\r\n");

    UART_PRINT("    signature: ");
    UART_PRINT("%d", d.signature);
    UART_PRINT("\r\n");

    UART_PRINT("    topic1: ");
    UART_PRINT("%s", d.topic1);
    UART_PRINT("\r\n");

    UART_PRINT("    topic2: ");
    UART_PRINT("%s", d.topic2);
    UART_PRINT("\r\n");

    UART_PRINT("    topic3: ");
    UART_PRINT("%s", d.topic3);
    UART_PRINT("\r\n");

    UART_PRINT("    topic4: ");
    UART_PRINT("%s", d.topic4);


    UART_PRINT("\r\n}\r\n");

}

/* Wrapper for cJSON_GetObjectItemCaseSensitive function*/
int getIntValue(cJSON *obj, char *field) {

    int val = cJSON_GetObjectItemCaseSensitive(obj, field)->valueint;
    return (val != 64943) ? val : -1;       // -1 indicates values not found
}

char *getStrValue(cJSON *obj, char *field) {
    return cJSON_GetObjectItemCaseSensitive(obj, field)->valuestring;
}


/* Returns a struct with values from str string (JSON format) */
struct dev_data getJSONData(char *str) {

    // initialize struct
    dev_data d_data = {"None", -1, -1, -1, -1, -1, -1, -1, -1, -1, "None", "false", "None", "None", "None", "None"};
    cJSON *json_obj = cJSON_Parse(str);

    int size = cJSON_GetArraySize(json_obj);
    if(size == 0) {
        UART_PRINT("ERROR: Empty string or improper format.\r\n");
        return d_data;
    }

    d_data.id = getStrValue(json_obj, "id");
    d_data.pub = getIntValue(json_obj, "pub");
    d_data.rec = getIntValue(json_obj, "rec");



    UART_PRINT("ID: %s\r\n", d_data.id);
    UART_PRINT("SIZE: %d\r\n", size);

        if(strcmp(d_data.id, "ultra") == 0) {

                d_data.time = getIntValue(json_obj, "time");
                d_data.dist = getIntValue(json_obj, "distance");
                d_data.status = getStrValue(json_obj, "status");

        }

        else if(strcmp(d_data.id, "arm") == 0) {

                d_data.time = getIntValue(json_obj, "time");
                d_data.status = getStrValue(json_obj, "status");


        }

        else if(strcmp(d_data.id, "rover") == 0) { // rover

                d_data.time = getIntValue(json_obj, "time");
                d_data.status = getStrValue(json_obj, "status");
                d_data.atDestination = getStrValue(json_obj, "atDestination");


        }

        else if(strcmp(d_data.id, "pixy") == 0) { // pixy

                d_data.time = getIntValue(json_obj, "time");
                d_data.x = getIntValue(json_obj, "x_coordinate");
                d_data.y = getIntValue(json_obj, "y_coordinate");
                d_data.height = getIntValue(json_obj, "height");
                d_data.width = getIntValue(json_obj, "width");
                d_data.signature = getIntValue(json_obj, "signature");

        }

        else if(strcmp(d_data.id, "topics") == 0) {

                d_data.topic1 = getStrValue(json_obj, "topic1");
                d_data.topic2 = getStrValue(json_obj, "topic2");
                d_data.topic3 = getStrValue(json_obj, "topic3");
                d_data.topic4 = getStrValue(json_obj, "topic4");

        }

        else {

            d_data.id = "rover";

            d_data.time = getIntValue(json_obj, "time");
            d_data.status = getStrValue(json_obj, "status");
            d_data.atDestination = getStrValue(json_obj, "atDestination");
            d_data.id = getStrValue(json_obj, "id");
                d_data.pub = getIntValue(json_obj, "pub");
                d_data.rec = getIntValue(json_obj, "rec");

        }

        cJSON_Delete(json_obj);
        return d_data;

}
