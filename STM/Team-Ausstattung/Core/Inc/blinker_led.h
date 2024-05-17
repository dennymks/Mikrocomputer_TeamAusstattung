/*
 * blinker_led.h
 *
 *  Created on: Mar 20, 2024
 *      Author: Lukas, Denny
 */

#include "stm32f4xx_hal.h"
#ifndef INC_BLINKER_LED_H_
#define INC_BLINKER_LED_H_



//----LED Pins----
//müssen für beide Ports identisch sein!

#define RED_LED_PIN GPIO_PIN_10
#define GREEN_LED_PIN GPIO_PIN_9
#define BLUE_LED_PIN GPIO_PIN_8



//----LED Ports-------

#define LED_PORT_LINKS GPIOD
#define LED_PORT_RECHTS GPIOA

//ab hier nix verändern!!

//---Defines------

#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4
#define WHITE 5

#define BLINKERRECHTS 42
#define BLINKERLINKS 43

//----Funkitionen----

void LED_Init(void);
void LED_On(uint8_t colour, uint8_t Blinker);
void LED_Off(uint8_t colour, uint8_t Blinker);
void LED_Toggle(uint8_t colour, uint8_t Blinker);
void LED_AlternateColour(uint8_t colour1, uint8_t coulour2, uint8_t Blinker);
uint8_t Colour_Status(uint8_t colour, uint8_t Blinker);
void LED_BothOn(uint8_t colour);
void LED_BothOff(uint8_t colour);


#endif /* INC_BLINKER_LED_H_ */
