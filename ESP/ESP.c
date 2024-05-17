
#include "UART_DRIVER.h"
#include "UART_DRIVER_2.h"
#include "can.h"
#include "package.h"
#include <stdio.h>
#include "driver\gpio.h"
#include "freeRTOS\freeRTOS.h"
#include "freeRTOS\task.h"

#define PIN_HORN GPIO_NUM_25
#define PIN_LEFT_INDICATOR GPIO_NUM_26
#define PIN_RIGHT_INDICATOR GPIO_NUM_27
#define PIN_THROTTLE GPIO_NUM_5

void app_main(void)
{
    package_t package;

    printf("Board set to Slave mode\n");

    const can_config_t config = {
        .tx_pin = GPIO_NUM_18,
        .rx_pin = GPIO_NUM_19,
        .id = CAN_ID_CLIENT_COMFORT};

    can_initialize(&config);

    uint8_t HORN = 0;
    uint8_t LEFT_INDICATOR = 0;
    uint8_t RIGHT_INDICATOR = 0;
    uint8_t THROTTLE = 0;

    gpio_set_direction(PIN_HORN, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_LEFT_INDICATOR, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_RIGHT_INDICATOR, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_THROTTLE, GPIO_MODE_OUTPUT);

    gpio_set_level(PIN_HORN, 1);
    gpio_set_level(PIN_LEFT_INDICATOR, 1);
    gpio_set_level(PIN_RIGHT_INDICATOR, 1);
    gpio_set_level(PIN_THROTTLE, 1);

    vTaskDelay(pdMS_TO_TICKS(3000));

    gpio_set_level(PIN_HORN, 0);
    gpio_set_level(PIN_LEFT_INDICATOR, 0);
    gpio_set_level(PIN_RIGHT_INDICATOR, 0);
    gpio_set_level(PIN_THROTTLE, 0);

    while (1)
    {
        package = can_receive();

        switch (package.type)
        {
        case PACKAGE_TYPE_THROTTLE:
            printf("RECEIVED package THROTTLE\n");
            package.type = PACKAGE_TYPE_THROTTLE;
            throttle_data_t *DATA_T = ((throttle_data_t *)package.data);
            THROTTLE = DATA_T->throttle;
            printf("%d\n", THROTTLE);
            if (THROTTLE > 0)
            {
                gpio_set_level(PIN_THROTTLE, 1);
                printf("T+\n");
            }
            else
            {
                gpio_set_level(PIN_THROTTLE, 0);
                printf("T-\n");
            }

            // can_send(CAN_ID_HOST, package);
            break;

        case PACKAGE_TYPE_HORN:
            printf("Received request for HORN\n");
            package.type = PACKAGE_TYPE_HORN;
            horn_data_t *DATA_H = ((horn_data_t *)package.data);
            HORN = DATA_H->is_on;
            printf("%d\n", HORN);
            if (HORN == 1)
            {
                printf("H+\n");
                gpio_set_level(PIN_HORN, 1);
            }
            else
            {
                gpio_set_level(PIN_HORN, 0);
                printf("H-\n");
            }

            // can_send(CAN_ID_HOST, package);
            break;

        case PACKAGE_TYPE_LEFT_INDICATOR:
            printf("Received request for LEFT INDICATOR\n");
            package.type = PACKAGE_TYPE_LEFT_INDICATOR;

            left_indicator_data_t *DATA_L = ((left_indicator_data_t *)package.data);
            LEFT_INDICATOR = DATA_L->is_on;
            printf("%d\n", LEFT_INDICATOR);
            if (LEFT_INDICATOR == 1)
            {
                printf("L+\n");
                gpio_set_level(PIN_LEFT_INDICATOR, 1);
            }
            else
            {
                gpio_set_level(PIN_LEFT_INDICATOR, 0);
                printf("L-\n");
            }

            // can_send(CAN_ID_HOST, package);
            break;

        case PACKAGE_TYPE_RIGHT_INDICATOR:
            printf("Received request for RIGHT INDICATOR\n");
            package.type = PACKAGE_TYPE_RIGHT_INDICATOR;

            right_indicator_data_t *DATA_R = ((right_indicator_data_t *)package.data);
            RIGHT_INDICATOR = DATA_R->is_on;
            printf("%d\n", RIGHT_INDICATOR);
            if (RIGHT_INDICATOR == 1)
            {
                printf("R+\n");
                gpio_set_level(PIN_RIGHT_INDICATOR, 1);
            }
            else
            {
                gpio_set_level(PIN_RIGHT_INDICATOR, 0);
                printf("R-\n");
            }

            // can_send(CAN_ID_HOST, package);
            break;

        case PACKAGE_TYPE_ERROR:
            printf("Package type error\n");
            package.type = PACKAGE_TYPE_ERROR;
            break;
        default:
            printf("Invalid package type\n");
            break;
        }

        can_send(CAN_ID_HOST, package);
    }
}
