#include <avr/io.h>
#include "pinout.h"
#include "motores.h"

void motores_init(void) {
	// Configurar pinos de dire��o do L298N como sa�da e a n�vel baixo (parados)
	DDRB |= (1 << PIN_MOT_IN1) | (1 << PIN_MOT_IN2) | (1 << PIN_MOT_IN3) | (1 << PIN_MOT_IN4);
	PORTB &= ~((1 << PIN_MOT_IN1) | (1 << PIN_MOT_IN2) | (1 << PIN_MOT_IN3) | (1 << PIN_MOT_IN4));
	
	//INIC. TIMER 0 -> PWM dos motores
	//Configura��o dos pinos do T/C0 como sa�da PD5(OC0B) e PD6(OC0A)
	DDRD |= (1 << PIN_PWM_ENA) | (1 << PIN_PWM_ENB);
	// Inicializa��o do PWM a zero
	OCR0A = 0;
	OCR0B = 0;
	// Configurar Timer0 em Fast PWM
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01)  | (1 << WGM00);
	// Prescaler = 8
	TCCR0B = (1 << CS01); //F_PWM = 5,86 kHz
}