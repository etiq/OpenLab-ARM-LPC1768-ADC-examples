/*
 * File name            : uart.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : June 09, 2017, 9:44 AM
 * Description          : UART0 c file
 */

#include <lpc17xx.h>
#include "uart.h"

#define  BAUDRATE			9600
#define  PC_UART0			3

/* CR - Control Register, SR - Status Register, DR - Data Ready */

#define FIFO_CR				LPC_UART0->FCR	
#define LINE_CR				LPC_UART0->LCR
#define LINE_SR				LPC_UART0->LSR

#define TX_BUFFER			LPC_UART0->THR
#define RX_BUFFER			LPC_UART0->RBR

#define WORDLEN_LCR   	(0x03<<0)			// 8-bit word length
#define DLAB_LCR      		(1<<7)

#define EN_FIFOCR   			(1<<0)
#define R0_RESET_FIFOCR   (1<<1)
#define T0_RESET_FIFOCR   (2<<1)

#define RX_DR   	  				0
#define TX_DR	    					5

#define DLLSB					LPC_UART0->DLL
#define DLMSB					LPC_UART0->DLM


/* Function to transmit a character */
void UART0_WriteChar(char ch)
{
    while(!((LINE_SR)&(1<<TX_DR)));  // The THRE Bit is 1 when THR is clear and is 0 when a write occurs on UnTHR
    TX_BUFFER = ch; 
}

/* Function to transmit a string */
void UART0_WriteString(char *str)
{
	while(*str != '\0')
	{
		UART0_WriteChar(*str);
		str++;
	}
}

/* Function to read a character */
char UART0_ReadChar()
{
    char ch; 
    while(!((LINE_SR)&(1<<RX_DR)));  // 0-UART FIFO EMPTY, 1-UART FIFO FILLED
		ch = RX_BUFFER;                // Read the received data    
    return ch;
}

void UART0_INIT()
{
		char ch;
    int i;
		uint32_t Clock_Frequency,Divisor_Latch_Val;

		SystemInit();

		LPC_SC->PCONP |= (1<<PC_UART0);
	
		LPC_PINCON->PINSEL0 &= ~0x000000F0;						//CLEAR THE TX and RX PINS
    LPC_PINCON->PINSEL0 |= 0x00000050;            // Enable the TX and RX pins for UART0 

    FIFO_CR = EN_FIFOCR + R0_RESET_FIFOCR + T0_RESET_FIFOCR ; // Enable FIFO and reset Rx/Tx FIFO buffers    

	/** The 8-bit character length must also be selected through the U0LCR register by entering values <1,1> for bits 0 and 1.
		1 Stop Bit and No parity bits are also selected with the Divisor Latch Access Bit.**/
		LINE_CR = WORDLEN_LCR + DLAB_LCR;
	
	/* The default system frequency is used.*/
    Clock_Frequency = SystemFrequency/4;

    Divisor_Latch_Val = (Clock_Frequency/(16 * BAUDRATE )); 
		
    DLLSB =  Divisor_Latch_Val & 0xFF;
    DLMSB =  Divisor_Latch_Val - DLLSB;

		LINE_CR &= ~DLAB_LCR;  // Clear DLAB after setting DLL,DLM
}