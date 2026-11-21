#include <avr/io.h>
#include <avr/interrupt.h>
#include "pinout.h"
#include "timer2.h"

static volatile uint8_t contador_500ms = 0;
static volatile uint8_t flag_1s = 0;

void timer2_inic(void){
	
	//PORTB -> PB1 saída led 1Hz
	DDRB |= (1<<PIN_LED_1HZ);
	PORTB &=~(1<<PIN_LED_1HZ);
	
	//Cristal de 12MHz
	//gerar uma base de tempo de T_ISR= 0,667ms
	//f_ISR = 1500Hz
	//1500 interrupções corresponde a 1s
	//750 interrupções corresponde a 500ms perfeito para o led de 1Hz
	//500ms ligado e 500ms desligado
	
	TCCR2A =(1<<WGM21);
	TCCR2B =(1<<CS22);
	TCNT2 = 0;
	OCR2A = 124;
	TIMSK2 = (1<<OCIE2A);
}

uint8_t timer2_1s(void){
	if(flag_1s == 1){
		flag_1s = 0;
		return 1;
	}
	
	else{
		return 0;
	}
}

ISR(TIMER2_COMPA_vect){
	static uint16_t contador_led = 0;
	contador_led ++;
	if(contador_led >= LED_OFF){
		PORTB^=(1<<PIN_LED_1HZ);
		contador_500ms ++;
		contador_led = 0;
	}
	if(contador_500ms == 2){
		flag_1s =1;
		contador_500ms = 0;
	}
	
}
