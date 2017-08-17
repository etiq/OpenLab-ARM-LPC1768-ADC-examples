#include "lpc17xx.h"
#include "delay.h"
#include "uart.h"

#define		ADC_CLOCK		1000000				//(SHOULD BE LESS THAN OR EQUAL TO 13MHz)

/* These are the pin definitions for the ADC pins defined under PINSELECT1 */

#define		AD0_0			14
#define		AD0_1			16
#define		AD0_2			18
#define		AD0_3			20

/* These are the pin definitions for the AD control 32 bit register ADCR */

#define 	ADCR_SEL0				0
#define 	ADCR_SEL1				1
#define 	ADCR_SEL2				2
#define 	ADCR_SEL3				3
#define 	ADCR_SEL4				4
#define 	ADCR_SEL5				5
#define 	ADCR_SEL6				6
#define 	ADCR_SEL7				7

#define		ADCR_CLKDIV			8
#define		ADCR_BURST		 16
#define		ADCR_PDN			 21
#define		ADCR_START		 24
#define		ADCR_EDGE			 27

/* These are the pin definitions for the AD result and status*/

#define ADC_OFFSET			(1<<4)
#define ADC_RESULT				4		
#define ADC_DONE				(1<<31)
#define ADC_OVERRUN			(1<<30)


void split(unsigned char s)
{
	unsigned char a[4];
	int i=0;

	while(i<4){
		a[i] = s%10;
		s = s/10;
		i++;
	}
	do
	{
		--i;
		UART0_WriteChar(a[i]+48);
	}while(i);
}

int main()
{
	uint32_t clock, DataReg, ADC_Data;
	uint8_t channelNum;	
	unsigned int adc0_value;

	SystemInit();

	channelNum = 0;		

	UART0_INIT();
	
	LPC_SC->PCONP |= (1 << 12);				// Power up the ADC module
  LPC_PINCON->PINSEL1 &= ~0x002FC000;	/* Funtions as ADC (0-3) pins when 01 is selected resp. under PINSEL1 reg.
																				P0.23 (15,14), P0.24 (17,16), P0.25 (19,18), P0.26 (21,20)*/
  LPC_PINCON->PINSEL1 |= (0x01 << AD0_0); // We will be using AD0 channel only.
	
	/* The peripheral clock selection for ADC is in the PCLKSEL0 register (bits 24 & 25).
	The reset value for this pair is 00. 
	So the default case is also 00.*/
	
  clock = SystemFrequency/4;

	LPC_ADC->ADCR |= (1 << ADCR_SEL0);																														// Select channel 0 on ADC0
	LPC_ADC->ADCR |= ((clock/ADC_CLOCK - 1)	<< ADCR_CLKDIV);																				// CLKDIV = (clock/ADC_CLOCK - 1)
	LPC_ADC->ADCR |= ((0 << ADCR_BURST) | (1 << ADCR_PDN) | (0 << ADCR_START) | (0 << ADCR_EDGE));
	
	UART0_WriteString("Analog to Digital Conversion\r\n");
	while(1){

		LPC_ADC->ADCR &= 0xFFFFFF00;
		LPC_ADC->ADCR |= (1 << ADCR_START) | (1 << ADCR_SEL0);		//Select AD0 channel and start the conversion process.

		do{
		DataReg = *(volatile unsigned long *)(LPC_ADC_BASE + ADC_OFFSET + ADC_RESULT * channelNum);
			}while(!(DataReg & ADC_DONE));														// When ADC_DONE is 1, the conversion is complete.
        
		LPC_ADC->ADCR &= 0xF8FFFFFF;															//Stop AD0 conversion process.
		ADC_Data = (DataReg>>ADC_RESULT)&0xFFF;									// The max value for the result will be in the range Vrefp (0xfff) and Vrefn (0x000)

		UART0_WriteString("ADC0: ");
		split( ADC_Data );	/* return A/D conversion value */
		UART0_WriteString("\r\n");
	  delay_ms(50);
	}
}