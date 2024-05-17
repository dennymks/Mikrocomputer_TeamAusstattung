

//---INCLUDES--
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#ifndef INC_DRV_TIMER_H_
#define INC_DRV_TIMER_H_


//---FUNCTIONS--

void drv_timer4_init(void);
void drv_timer4_CB_init(void(*)());
void TIM4_IRQHandler();

#endif /* INC_DRV_TIMER_H_ */
