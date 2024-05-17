/*



#include "stm32f4xx_hal.h"
#include "blinker_led.h"


int main(void)
{
    HAL_Init();

    LED_Init();

// ----Testen von Blinkerlinks----

    //Testet LED_On, LED_Off von jeder Farbe

    LED_On(RED, BLINKERLINKS);

    HAL_Delay(750);

    LED_Off(RED, BLINKERLINKS);

    HAL_Delay(750);

    LED_On(GREEN, BLINKERLINKS);

    HAL_Delay(750);

    LED_Off(GREEN, BLINKERLINKS);

    HAL_Delay(750);

    LED_On(BLUE, BLINKERLINKS);

    HAL_Delay(750);

    LED_Off(BLUE, BLINKERLINKS);

    HAL_Delay(750);

    LED_On(ORANGE, BLINKERLINKS);

    HAL_Delay(750);

    LED_Off(ORANGE, BLINKERLINKS);

    HAL_Delay(750);

    LED_On(WHITE, BLINKERLINKS);

    HAL_Delay(750);

    LED_Off(WHITE, BLINKERLINKS);

    HAL_Delay(1000);

    //Testet LED_Toggle von jeder Farbe

    LED_On(RED, BLINKERLINKS);

    HAL_Delay(750);

    for(int i = 0; i<5; i++){
    	LED_Toggle(RED, BLINKERLINKS);
    	HAL_Delay(750);
    }


    LED_On(GREEN, BLINKERLINKS);

    HAL_Delay(750);


    for(int i = 0; i<5; i++){
    	LED_Toggle(GREEN, BLINKERLINKS);
        HAL_Delay(750);
    }

    HAL_Delay(750);


    LED_On(BLUE, BLINKERLINKS);

    HAL_Delay(750);


    for(int i = 0; i<5; i++){
       	LED_Toggle(BLUE, BLINKERLINKS);
        HAL_Delay(750);
    }

    LED_On(ORANGE, BLINKERLINKS);

    HAL_Delay(750);


    for(int i = 0; i<5; i++){
        LED_Toggle(ORANGE, BLINKERLINKS);
        HAL_Delay(750);
    }

    HAL_Delay(750);

    LED_On(WHITE, BLINKERLINKS);

    HAL_Delay(750);


    for(int i = 0; i<5; i++){
    	LED_Toggle(WHITE, BLINKERLINKS);
        HAL_Delay(750);
    }

    HAL_Delay(1000);


    //Testen von LED_AlternateColour

    for(int i = 0; i<5; i++){
    	LED_AlternateColour(GREEN, ORANGE, BLINKERLINKS);
        HAL_Delay(750);
    }

    HAL_Delay(750);

    for(int i = 0; i<5; i++){
    	LED_AlternateColour(RED, ORANGE, BLINKERLINKS);
        HAL_Delay(750);
    }

    HAL_Delay(750);

    for(int i = 0; i<5; i++){
    	LED_AlternateColour(BLUE, ORANGE, BLINKERLINKS);
        HAL_Delay(750);
    }

    LED_Off(WHITE, BLINKERLINKS);

    HAL_Delay(1000);


// ----Testen von Blinkerrechts----

    //Testet LED_On, LED_Off von jeder Farbe

    LED_On(RED, BLINKERRECHTS);

    HAL_Delay(750);

    LED_Off(RED, BLINKERRECHTS);

    HAL_Delay(750);

    LED_On(GREEN, BLINKERRECHTS);

    HAL_Delay(750);

    LED_Off(GREEN, BLINKERRECHTS);

    HAL_Delay(750);

    LED_On(BLUE, BLINKERRECHTS);

    HAL_Delay(750);

    LED_Off(BLUE, BLINKERRECHTS);

    HAL_Delay(750);

    LED_On(ORANGE, BLINKERRECHTS);

    HAL_Delay(750);

    LED_Off(ORANGE, BLINKERRECHTS);

    HAL_Delay(750);

    LED_On(WHITE, BLINKERRECHTS);

    HAL_Delay(750);

    LED_Off(WHITE, BLINKERRECHTS);

    HAL_Delay(1000);

    //Testet LED_Toggle von jeder Farbe

    LED_On(RED, BLINKERRECHTS);

    HAL_Delay(750);

    for(int i = 0; i<5; i++){
        LED_Toggle(RED, BLINKERRECHTS);
       	HAL_Delay(750);
    }


    LED_On(GREEN, BLINKERRECHTS);

    HAL_Delay(750);

    for(int i = 0; i<5; i++){
       	LED_Toggle(GREEN, BLINKERRECHTS);
       	HAL_Delay(750);
    }

    HAL_Delay(750);

    LED_On(BLUE, BLINKERRECHTS);

    HAL_Delay(750);

    for(int i = 0; i<5; i++){
    	LED_Toggle(BLUE, BLINKERRECHTS);
      	HAL_Delay(750);
    }

    LED_On(ORANGE, BLINKERRECHTS);

    HAL_Delay(750);


    for(int i = 0; i<5; i++){
    	LED_Toggle(ORANGE, BLINKERRECHTS);
    	HAL_Delay(750);
	}

    HAL_Delay(750);

    LED_On(WHITE, BLINKERRECHTS);
    HAL_Delay(750);


    for(int i = 0; i<5; i++){
    	LED_Toggle(WHITE, BLINKERRECHTS);
        HAL_Delay(750);
    }

    HAL_Delay(1000);


    //Testen von LED_AlternateColour

    for(int i = 0; i<5; i++){
       	LED_AlternateColour(GREEN, ORANGE, BLINKERRECHTS);
       	HAL_Delay(750);
    }

    HAL_Delay(750);

    for(int i = 0; i<5; i++){
       	LED_AlternateColour(RED, ORANGE, BLINKERRECHTS);
       	HAL_Delay(750);
    }

    HAL_Delay(750);

    for(int i = 0; i<5; i++){
    	LED_AlternateColour(BLUE, ORANGE, BLINKERRECHTS);
    	HAL_Delay(750);
    }

    LED_Off(WHITE, BLINKERRECHTS);
}

*/
