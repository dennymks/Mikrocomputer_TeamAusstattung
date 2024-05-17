/*
 * hupe.c
 *
 *  Created on: Apr 21, 2024
 *      Author: denny, lukas
 */

#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "hupe.h"

extern UART_HandleTypeDef huart4;
#define DF_UART &huart4

#define Quelle 0x02  // SD KARTE


/*************************************** NACH DIESER ZEILE KEINE ÄNDERUNGEN *************************************************/


# define Start_Byte 0x7E
# define End_Byte   0xEF
# define Version    0xFF
# define Cmd_Len    0x06
# define Feedback   0x00    //Wenn Feedback benötigt wird: 0x01, Kein Feedback: 0

/* Sendet ein Befehlspaket über die UART-Schnittstelle
   cmd: Befehl, der gesendet werden soll
   Parameter1: Erster Parameter des Befehls
   Parameter2: Zweiter Parameter des Befehls
  */
void Send_cmd (uint8_t cmd, uint8_t Parameter1, uint8_t Parameter2)
{
	uint16_t Checksum = Version + Cmd_Len + cmd + Feedback + Parameter1 + Parameter2;
	Checksum = 0-Checksum;

	uint8_t CmdSequence[10] = { Start_Byte, Version, Cmd_Len, cmd, Feedback, Parameter1, Parameter2, (Checksum>>8)&0x00ff, (Checksum&0x00ff), End_Byte};
	HAL_UART_Transmit(DF_UART, CmdSequence, 10, 100);
}

/*Initialisiert das DF-Modul*/
void DF_Init ()
{
	Send_cmd(0x3F, 0x00, Quelle); // Befehl, um die Quelle auf die TF-Karte zu setzen
	HAL_Delay(500);
	Send_cmd(0x06, 0x00, 0x1E); // Befehl, um die Lautstärke einzustellen
	HAL_Delay(500);
}
