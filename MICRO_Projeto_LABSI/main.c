/*
 * Projeto_LABSI.c
 *
 * Created: 17/11/2026 17:05:19
 * Author : migue
 */ 

#include <avr/io.h>
#include "pinout.h"
#include "motores.h"

void inic(void);

int main(void)
{
    inic();
	motores_init();
    while (1) 
    {
    }
}

void inic(void){
	
	//PORTB -> PB1 saída led 1Hz
	DDRB |= (1<<PIN_LED_1HZ);
	PORTB &=~(1<<PIN_LED_1HZ);
	
	//TIMER1 -> Modo CTC 1s
	//COM1A1/COM1A0: Toggle OC1A on compare match
	//f_OC1A = f_clk/(2*N*(1+0CR1A))
	//N=256 / f_clk = 12MHz / f_OC1A = 1Hz
	//WGM13/WGM12/WGM11/WGM10: CTC TOP=OCR1A
	//CS12/CS11/CS10: prescaler 256
	//OCR1A = 23437; //cristal externo
	OCR1A = 15624; //cristal interno 8MHz 
	TCCR1A = (1<<COM1A0);
	TCCR1B = (1<<CS12)|(1<<WGM12);
	
}