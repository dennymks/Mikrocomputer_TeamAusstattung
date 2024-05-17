/*
 * blinker_led.c
 *
 *  Created on: Mar 20, 2024
 *      Author: Lukas, Denny
 */
#include "blinker_led.h"


//---Initalisierungsfunktion---

void LED_Init(void){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	//Clock für Ports aktivieren

	if (LED_PORT_LINKS == GPIOA){ __HAL_RCC_GPIOA_CLK_ENABLE();}
	else if (LED_PORT_LINKS == GPIOB){ __HAL_RCC_GPIOB_CLK_ENABLE();}
	else if (LED_PORT_LINKS == GPIOC){ __HAL_RCC_GPIOC_CLK_ENABLE();}
	else if (LED_PORT_LINKS == GPIOD){ __HAL_RCC_GPIOD_CLK_ENABLE();}

	if (LED_PORT_RECHTS == GPIOA){ __HAL_RCC_GPIOA_CLK_ENABLE();}
	else if (LED_PORT_RECHTS == GPIOB){ __HAL_RCC_GPIOB_CLK_ENABLE();}
	else if (LED_PORT_RECHTS == GPIOC){ __HAL_RCC_GPIOC_CLK_ENABLE();}
	else if (LED_PORT_RECHTS == GPIOD){ __HAL_RCC_GPIOD_CLK_ENABLE();}




	//Konfiguartion Blinker Links

	//Konfiguration für rote LED

	GPIO_InitStruct.Pin = RED_LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT_LINKS, &GPIO_InitStruct);

	// Konfiguration für grüne LED

    GPIO_InitStruct.Pin = GREEN_LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT_LINKS, &GPIO_InitStruct);

	// Konfiguration für blaue LED

    GPIO_InitStruct.Pin = BLUE_LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT_LINKS, &GPIO_InitStruct);



    //Konfiguartion Blinker Rechts

    //Konfiguration für rote LED

    GPIO_InitStruct.Pin = RED_LED_PIN;
   	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   	GPIO_InitStruct.Pull = GPIO_NOPULL;
   	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT_RECHTS, &GPIO_InitStruct);

   	// Konfiguration für grüne LED

    GPIO_InitStruct.Pin = GREEN_LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT_RECHTS, &GPIO_InitStruct);

    // Konfiguration für blaue LED

    GPIO_InitStruct.Pin = BLUE_LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT_RECHTS, &GPIO_InitStruct);

}


/*----Einschaltfunktion----
Schaltet LEDs eines Blinkers auf die angegebene Farbe
Funktion ist absolut, d.h. es wird immer auf die angegebene Farbe umgeschalten
egal welche Farbe vorher geleuchtet hat
*/
void LED_On(uint8_t colour, uint8_t Blinker){
	GPIO_TypeDef* gpio_port = NULL;

	//Blinkerportauswählen

	if (Blinker == BLINKERLINKS){
		gpio_port = LED_PORT_LINKS;
	}
	else gpio_port = LED_PORT_RECHTS;

	switch (colour)
	{
		//schaltet LEDs auf Rot
		case RED:
			HAL_GPIO_WritePin(gpio_port, RED_LED_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(gpio_port, GREEN_LED_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(gpio_port, BLUE_LED_PIN, GPIO_PIN_RESET);
			break;
		//schaltet LEDs auf Grün
		case GREEN:
			HAL_GPIO_WritePin(gpio_port, GREEN_LED_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(gpio_port, RED_LED_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(gpio_port, BLUE_LED_PIN, GPIO_PIN_RESET);
			break;
		//schaltet LEDs auf Blau
		case BLUE:
			HAL_GPIO_WritePin(gpio_port, BLUE_LED_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(gpio_port, RED_LED_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(gpio_port, GREEN_LED_PIN, GPIO_PIN_RESET);
			break;
		//schaltet LEDs auf Orange
		case ORANGE:
			HAL_GPIO_WritePin(gpio_port, RED_LED_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(gpio_port, GREEN_LED_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(gpio_port, BLUE_LED_PIN, GPIO_PIN_RESET);
			break;
		//schaltet LEDs auf Weiß
		case WHITE:
			HAL_GPIO_WritePin(gpio_port, RED_LED_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(gpio_port, GREEN_LED_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(gpio_port, BLUE_LED_PIN, GPIO_PIN_SET);
			break;
		//bei fehlerhafter Eingabe wird nix gemacht
		default: break;
	}
}


/*----Ausschaltfunktion----
Schaltet die angegebene Farbe eines Blinkers aus
Funktion ist absolut, d.h. es wird immer nur die angegebene Farbe ausgeschalten
egal welche Farbe vorher geleuchtet hat
Bsp:
		Orange leuchtet
		LEd_Off(RED, BLINKERRECHTS)
		Grün leuchtet weiter
*/


void LED_Off(uint8_t colour, uint8_t Blinker){

	GPIO_TypeDef* gpio_port = NULL;

	//Blinkerportauswählen

	if (Blinker == BLINKERLINKS){
		 gpio_port = LED_PORT_LINKS;
	}
	else gpio_port = LED_PORT_RECHTS;



	switch (colour)
		{
			//schaltet Farbe Rot aus
			case RED:
				HAL_GPIO_WritePin(gpio_port, RED_LED_PIN, GPIO_PIN_RESET);
				break;
			//schaltet Farbe Grün aus
			case GREEN:
				HAL_GPIO_WritePin(gpio_port, GREEN_LED_PIN, GPIO_PIN_RESET);
				break;
			//schaltet Farbe Blau aus
			case BLUE:
				HAL_GPIO_WritePin(gpio_port, BLUE_LED_PIN, GPIO_PIN_RESET);
				break;
			//schaltet Farbe Orange aus
			case ORANGE:
				HAL_GPIO_WritePin(gpio_port, RED_LED_PIN, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(gpio_port, GREEN_LED_PIN, GPIO_PIN_RESET);
				break;
			//schaltet Farbe Weiß aus
			case WHITE:
				HAL_GPIO_WritePin(gpio_port, RED_LED_PIN, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(gpio_port, GREEN_LED_PIN, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(gpio_port, BLUE_LED_PIN, GPIO_PIN_RESET);
				break;
			//bei Fehlerhafter Eingabe passiert nix
			default: break;
		}

}

/*----Togglefunktion----
Toggled die angegebene Farbe bei einem Blinker bei jedem Aufruf
Übeprüft ob eine Mischfarbe oder die Farbe noch nicht eingeschaltet war falls ja wird erstmal die angegebene Farbe eingechaltet
sonst wird die Farbe bei dem jeweiligen Aufruf aus oder angeschalten
*/


void LED_Toggle(uint8_t colour, uint8_t Blinker){

	GPIO_TypeDef* gpio_port = NULL;

	//Blinkerportauswählen
	if (Blinker == BLINKERLINKS){
			gpio_port = LED_PORT_LINKS;
	}
	else gpio_port = LED_PORT_RECHTS;



	switch (colour)
			{
				//Toggled Rot
				case RED:
					if(Colour_Status(ORANGE, Blinker) || Colour_Status(WHITE, Blinker) || !Colour_Status(RED, Blinker))
						{
							LED_On(RED, Blinker);
						}

					else {HAL_GPIO_TogglePin(gpio_port, RED_LED_PIN);}

					break;

				//Toggled Grün
				case GREEN:
					if(!Colour_Status(GREEN, Blinker) || Colour_Status(WHITE, Blinker) || Colour_Status(ORANGE, Blinker))
					{
						LED_On(GREEN, Blinker);
					}
					else {HAL_GPIO_TogglePin(gpio_port, GREEN_LED_PIN);}

					break;

				//Toggled Blue
				case BLUE:
					if(!Colour_Status(BLUE, Blinker) || Colour_Status(WHITE, Blinker) || Colour_Status(ORANGE, Blinker))
					{
						LED_On(BLUE, Blinker);
					}

					else {HAL_GPIO_TogglePin(gpio_port, BLUE_LED_PIN);}

					break;

				//Toggled Orange
				case ORANGE:
					if(!Colour_Status(ORANGE, Blinker) || Colour_Status(WHITE, Blinker))
						{
							LED_On(ORANGE, Blinker);
						}

					else{
						HAL_GPIO_TogglePin(gpio_port, RED_LED_PIN);
						HAL_GPIO_TogglePin(gpio_port, GREEN_LED_PIN);
						}

					break;

				//Toggled Weiß
				case WHITE:
					if(!Colour_Status(WHITE, Blinker))
						{
							LED_On(WHITE, Blinker);
							break;
						}

					else{
						HAL_GPIO_TogglePin(gpio_port, RED_LED_PIN);
						HAL_GPIO_TogglePin(gpio_port, GREEN_LED_PIN);
						HAL_GPIO_TogglePin(gpio_port, BLUE_LED_PIN);
						break;
					}

			//Toggled nichts bei fehlerhafter Eingabe
				default: break;
			}

}


/*----AlternateColourfunktion----
Toggled zwischen den angegebenen Farben bei einem Blinker bei jedem Aufruf
Überprüft ob die beiden angegbenenen Farben den gleichen Status haben, wenn ja wird erstmal colour1 getoggled
sonst wird die Farbe bei dem jeweiligen Aufruf aus oder angeschalten
*/
void LED_AlternateColour(uint8_t colour1, uint8_t colour2, uint8_t Blinker){


	if (Colour_Status(colour1, Blinker) == Colour_Status(colour2, Blinker)){
		LED_Toggle(colour1, Blinker);
	}

	else if (Colour_Status(colour1, Blinker) != Colour_Status(colour2, Blinker)){
		if(Colour_Status(colour1, Blinker))
		{
			LED_Toggle(colour1, Blinker);
			LED_Toggle(colour2, Blinker);
		}
		else
		{
			LED_Toggle(colour2, Blinker);
			LED_Toggle(colour1, Blinker);
		}
	}


}


/*---Statusfunktion für BLinker-----
gibt 1 zurück wenn nur die Farbe an dem angegebenen Blinker leuchtet
sonst 0
*/
uint8_t Colour_Status(uint8_t colour, uint8_t Blinker){

	GPIO_TypeDef* gpio_port = NULL;

	//Blinkerportauswählen
	if (Blinker == BLINKERLINKS){
			gpio_port = LED_PORT_LINKS;
		}
	else gpio_port = LED_PORT_RECHTS;


	switch (colour)
			{
				case RED:
					return HAL_GPIO_ReadPin(gpio_port, RED_LED_PIN) && !HAL_GPIO_ReadPin(gpio_port, GREEN_LED_PIN) && !HAL_GPIO_ReadPin(gpio_port, BLUE_LED_PIN);
					break;

				case GREEN:
					return HAL_GPIO_ReadPin(gpio_port, GREEN_LED_PIN) && !HAL_GPIO_ReadPin(gpio_port, RED_LED_PIN) && !HAL_GPIO_ReadPin(gpio_port, BLUE_LED_PIN);
					break;

				case BLUE:
					return HAL_GPIO_ReadPin(gpio_port, BLUE_LED_PIN) && !HAL_GPIO_ReadPin(gpio_port, GREEN_LED_PIN) && !HAL_GPIO_ReadPin(gpio_port, RED_LED_PIN);
					break;

				case ORANGE:
					return HAL_GPIO_ReadPin(gpio_port, RED_LED_PIN) && HAL_GPIO_ReadPin(gpio_port, GREEN_LED_PIN) && !HAL_GPIO_ReadPin(gpio_port, BLUE_LED_PIN);
					break;

				case WHITE:
					return HAL_GPIO_ReadPin(gpio_port, RED_LED_PIN) && HAL_GPIO_ReadPin(gpio_port, GREEN_LED_PIN) && HAL_GPIO_ReadPin(gpio_port, BLUE_LED_PIN);
					break;

				//bei Fehlerhaften Parametern wird 31 zurückgegeben
				default:
					return 31;
					break;
			}
}


/*----Einschaltfunktion beider Blinker----
Schaltet beide Blinker auf die gewünschte Farbe
Nutzt LED_On und ist deshlab ebenfalls absolut!
*/

void LED_BothOn(uint8_t colour){

	switch (colour)
	{
		case RED:
			LED_On(RED, BLINKERRECHTS);
			LED_On(RED, BLINKERLINKS);
			break;

		case GREEN:
			LED_On(GREEN, BLINKERRECHTS);
			LED_On(GREEN, BLINKERLINKS);
			break;

		case BLUE:
			LED_On(BLUE, BLINKERRECHTS);
			LED_On(BLUE, BLINKERLINKS);
			break;

		case ORANGE:
			LED_On(ORANGE, BLINKERRECHTS);
			LED_On(ORANGE, BLINKERLINKS);
			break;

		case WHITE:
			LED_On(WHITE, BLINKERRECHTS);
			LED_On(WHITE, BLINKERLINKS);
			break;

		//bei Fehlerhaften Parametern passiert nichts
		default: break;
	}
}

/*---Ausschaltfunktion beider Blinker
Shaltet beide Blinker aus, egal welche Farbe vorher leutchtete-----*/

void LED_BothOff(uint8_t colour){

	//White wird verwendet
	LED_Off(WHITE, BLINKERRECHTS);
	LED_Off(WHITE, BLINKERLINKS);
}
