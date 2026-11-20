#include <avr/io.h>
#include <interrupt.h>
#include "timer.h"

void timer_inic(void)
{
//INIC. TIMER 0 -> PWM dos motores
	//Configuração dos pinos do T/C0 como saída PD5(OC0B) e PD6(OC0A)
	DDRD |= (1 << PIN_PWM_ENA) | (1 << PIN_PWM_ENB);
	// Inicialização do PWM a zero
	OCR0A = 0;
	OCR0B = 0;
	// Configurar Timer0 em Fast PWM
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01)  | (1 << WGM00);
	// Prescaler = 8
	TCCR0B = (1 << CS01); //F_PWM = 5,86 kHz
	
//INIC. TIMER 2 -> 1ms	
	// Modo CTC
	TCCR2A = (1 << WGM21);

	// OCR2A = 93
	OCR2A = 93;

	// Zera contador
	TCNT2 = 0;

	// Limpa flag de comparação
	TIFR2 = (1 << OCF2A);

	// Habilita interrupção de comparação
	TIMSK2 = (1 << OCIE2A);

	// Prescaler = 128
	TCCR2B = (1 << CS22) | (1 << CS20);
}