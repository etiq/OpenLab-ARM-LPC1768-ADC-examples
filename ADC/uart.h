/*
 * File name            : uart.h
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : June 09, 2017, 9:44 AM
 * Description          : UART0 Header File
 */

#include <lpc17xx.h>

/* Function to transmit a character */
void UART0_WriteChar(char ch);

/* Function to transmit a string */
void UART0_WriteString(char *str);

/* Function to read a character */
char UART0_ReadChar(void);
	
void UART0_INIT(void);