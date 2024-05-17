//--INCLUDES--
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "drv_Timer.h"


//--Pointer--
static void (*timerpointer)();							/* Zeiger für Callbackfunktion */

//--FUNKTIONEN--

void drv_timer4_init(void){
	RCC->APB1ENR|= RCC_APB1ENR_TIM4EN_Msk;				/* Takt für Tim4 aktivieren */
	TIM4->CR1 |= TIM_CR1_DIR_Msk;						/* Timer aufwärtszählen */
	TIM4->CR1 |= TIM_CR1_ARPE_Msk;						/* Auto-Reload aktivieren */
	TIM4->PSC = 1000;									/* Vorteiler einstellen für 50ms */
	TIM4->ARR = 800;									/* Auto-Reload Wert setzen */
	TIM4->DIER |= TIM_DIER_UIE_Msk;						/* Interrupt mit UIF-Flag aktivieren */
	NVIC_SetPriority(TIM4_IRQn,1);
}


void drv_timer4_CB_init(void(*callback)()){
	timerpointer = callback;							/* Zeiger auf gegebene Funktion setzen */
	TIM4->CR1 |= TIM_CR1_CEN_Msk;						/* Timer TIM4 aktivieren - erst hier aktivieren, sonst wird der Interrupt aufgerufen bevor der Callback definiert ist */
	NVIC_EnableIRQ (TIM4_IRQn);							/* Timer Interrupt aktivieren */
}


void TIM4_IRQHandler(){
		NVIC_DisableIRQ(TIM4_IRQn);						/* Interrupt deaktivieren */
		(*timerpointer)();								/* Callback-Funktion ausführen */
		TIM4->SR &= ~(TIM_SR_UIF_Msk);					/* UIF-Bit zurücksetzen */
		NVIC_EnableIRQ(TIM4_IRQn);						/* Interrupt wieder aktivieren */
}
