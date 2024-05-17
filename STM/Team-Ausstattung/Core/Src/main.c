
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "hupe.h"
#include "blinker_led.h"
#include "drv_Timer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PORT_DATA GPIOE
#define DRIVING	GPIO_PIN_0
#define RIGHT_INDICATOR GPIO_PIN_4
#define LEFT_INDICATOR GPIO_PIN_3
#define HORN GPIO_PIN_2
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart4;

/* USER CODE BEGIN PV */
GPIO_PinState horn_state, previous_pin_state;
uint8_t t,z;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_UART4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void processInputs(GPIO_PinState left_indicator, GPIO_PinState right_indicator, GPIO_PinState driving);
void callback(void);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */

  DF_Init();	//Init DF-Player
  LED_Init();	//Init LEDs
  drv_timer4_init();	//Init Timer
  drv_timer4_CB_init(callback);	//Init callback for Timer


  previous_pin_state = GPIO_PIN_RESET;
  t = 0;
  z = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

void processInputs(GPIO_PinState left_indicator, GPIO_PinState right_indicator, GPIO_PinState driving) {

    int combinedState = (left_indicator << 2) | right_indicator <<1 | driving;

    switch(combinedState) {
        case 0b000:
        	//Fall: Blinker links aus, Blinker rechts aus, Fahren aus
        	LED_BothOn(RED);
        	t=0;
        	z = 0;
            break;
        case 0b001:
        	//Fall: Blinker links aus, Blinker rechts aus, Fahren an
            LED_BothOn(GREEN);
            t=0;
            z = 0;
            break;
        case 0b010:
            //Fall: Blinker links aus, Blinker rechts an, Fahren aus
        	if (t>=6 || z == 0)
        	{
        		LED_Off(WHITE, BLINKERLINKS);
        		LED_Toggle(ORANGE, BLINKERRECHTS);
        		t = 0;
        		z = 1;
        		break;
        	}
        	z = 1;
        	t++;
            break;
        case 0b011:
            //Fall: Blinker links aus, Blinker rechts an, Fahren an
        	if (t>=6 || z == 0)
        	{
        		LED_On(GREEN, BLINKERLINKS);
        		LED_AlternateColour(ORANGE, GREEN, BLINKERRECHTS);
        		t = 0;
        		z = 1;
        		break;
        	}
        	z = 1;
            t++;
            break;
        case 0b100:
           //Fall: Blinker links an, Blinker rechts aus, Fahren aus
        	if (t>=6 || z == 0)
        	{
        		LED_Off(WHITE, BLINKERRECHTS);
        		LED_Toggle(ORANGE, BLINKERLINKS);
        		t=0;
        		z = 1;
        		break;
        	}
        	z = 1;
        	t++;
            break;
        case 0b101:
            //Fall: Blinker links an, Blinker rechts aus, Fahren an
        	if (t>=6 || z == 0)
        	{
        		LED_On(GREEN, BLINKERRECHTS);
        		LED_AlternateColour(ORANGE, GREEN, BLINKERLINKS);
        		t=0;
        		z = 1;
        		break;
        	}
        	z = 1;
        	t++;
            break;
        case 0b110:
            //Fall: Blinker links an, Blinker rechts an, Fahren aus
        	if (t>=6 || z == 0)
        	{
        		if (Colour_Status(ORANGE, BLINKERLINKS) != Colour_Status(ORANGE, BLINKERRECHTS))
        		{
        			LED_Toggle(ORANGE, BLINKERLINKS);
        		}
        		LED_Toggle(ORANGE, BLINKERLINKS);
        		LED_Toggle(ORANGE, BLINKERRECHTS);
        		t=0;
        		z = 1;
        		break;
        	}
        	z = 1;
        	t++;
            break;
        case 0b111:
            //Fall: Blinker links an, Blinker rechts an, Fahren an
        	if (t>=6 || z == 0)
        	{
        		if(Colour_Status(ORANGE, BLINKERRECHTS) != Colour_Status(ORANGE, BLINKERLINKS))
        		{
        			LED_AlternateColour(ORANGE, GREEN, BLINKERRECHTS);
        		}
        		LED_AlternateColour(ORANGE, GREEN, BLINKERRECHTS);
        		LED_AlternateColour(ORANGE, GREEN, BLINKERLINKS);
        		t=0;
        		z = 1;
        		break;
        	}
        	z = 1;
        	t++;
            break;
        default:
            // Standardfall oder Fehlerbehandlung
            break;
    }

}


void callback(void)
{
	 horn_state = HAL_GPIO_ReadPin(PORT_DATA, HORN);

	 if(horn_state == GPIO_PIN_SET && previous_pin_state == GPIO_PIN_RESET)
	 {
		 Send_cmd(0x03, 0x00, 0x01);		//Hupen sound abspielen
	 }
	 previous_pin_state = horn_state;

	 processInputs(HAL_GPIO_ReadPin(PORT_DATA, LEFT_INDICATOR), HAL_GPIO_ReadPin(PORT_DATA, RIGHT_INDICATOR), HAL_GPIO_ReadPin(PORT_DATA, DRIVING));

}



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */
	//__HAL_RCC_UART4_CLK_ENABLE();
  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
