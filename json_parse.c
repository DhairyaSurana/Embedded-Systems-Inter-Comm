#include "json_parse.h"



/* Prints out struct values to UART */
void printDevData(dev_data d) {

    UART_PRINT("DEVICE STRUCT {\r\n\r\n");

    UART_PRINT("    id: ");
    UART_PRINT("%d", d.id);
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
    UART_PRINT("%d", d.status);
    UART_PRINT("\r\n");

    UART_PRINT("    atDestination: ");
    UART_PRINT("%d", d.atDestination);
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

    UART_PRINT("\r\n}\r\n");

}

/* Wrapper for cJSON_GetObjectItemCaseSensitive function*/
int getValue(cJSON *obj, char *field) {

    int val = cJSON_GetObjectItemCaseSensitive(obj, field)->valueint;
    return (val != 64943) ? val : -1;       // -1 indicates values not found
}

/* Returns a struct with values from str string (JSON format) */
struct dev_data getJSONData(char *str) {

    cJSON *json_obj = cJSON_Parse(str);

    // initializint struct
    dev_data d_data = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    d_data.id = getValue(json_obj, "id");
    d_data.pub = getValue(json_obj, "pub");
    d_data.rec = getValue(json_obj, "rec");
    d_data.time = getValue(json_obj, "time");

    switch(cJSON_GetArraySize(json_obj)) {

        case 5: // ultra or arm

            d_data.dist = getValue(json_obj, "distance");
            d_data.status = getValue(json_obj, "status");

            cJSON_Delete(json_obj);
            return d_data;

        case 6: // rover

            d_data.status = getValue(json_obj, "status");
            d_data.atDestination = getValue(json_obj, "atDestination");

            cJSON_Delete(json_obj);
            return d_data;

        case 9: // pixy

            d_data.x = getValue(json_obj, "x_coordinate");
            d_data.y = getValue(json_obj, "y_coordinate");
            d_data.height = getValue(json_obj, "height");
            d_data.width = getValue(json_obj, "width");
            d_data.signature = getValue(json_obj, "signature");

            cJSON_Delete(json_obj);
            return d_data;

        default: // Incorrect size error handling

            UART_PRINT("ERROR: Incorrect size\r\n");
            dev_data null_data = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

            cJSON_Delete(json_obj);
            return null_data;

    }

}
