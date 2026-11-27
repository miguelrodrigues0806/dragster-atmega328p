#include <avr/io.h>
#include "pinout.h"
#include "sonar.h"
#include <avr/interrupt.h>

#if (F_CPU == 12000000UL)
#define TRIG_PULSE_TICKS 16 //16 * 0,667us = 10,67us
#define TIME_TICK 2/3
#elif (F_CPU == 8000000UL)
#define TRIG_PULSE_TICKS 11 //11 * 1us = 11us
#define  TIME_TICK 1
#else
#error "Unsupported F_CPU value"
#endif

static volatile uint16_t ticks = 0;
static volatile uint8_t flag_echo = 0;
static volatile uint16_t ultimo_tempo = 0;

void timer1_sonar_inic(void){
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	TIMSK1 = 0;
	TCCR1B = (1<<CS11); // Prescaler 8
}

void sonar_init(void){

	DDRD|= (1<<PIN_SONAR_TRIG);
	DDRD&=~(1<<PIN_SONAR_ECHO);
	PORTD&=~(1<<PIN_SONAR_TRIG);
	EICRA |=(1<<ISC00);
	EICRA &=~(1<<ISC01);
	EIMSK |=(1<<INT0);
	timer1_sonar_inic();
}

void sonar_trigger(void){
	uint16_t t_inicio = TCNT1;
	PORTD|=(1<<PIN_SONAR_TRIG);

	while((uint16_t)(TCNT1-t_inicio)<TRIG_PULSE_TICKS){
		//Fica aqui durante o tempo do pulso de trigger
	}

	PORTD&=~(1<<PIN_SONAR_TRIG);
}

uint16_t sonar_ticks(void){
	if(flag_echo){
		flag_echo = 0;
		ultimo_tempo = ticks*TIME_TICK;
		return ticks*TIME_TICK;
	}
	return ultimo_tempo;
}

uint16_t sonar_distance_cm(void){
	uint32_t t = sonar_ticks();
	return (t*343)/20000; // Velocidade do som = 343,42 m/s 
}

ISR(INT0_vect){
	static uint16_t t1 = 0;
	uint16_t t2 = 0;
	if(PIND & (1<<PIN_SONAR_ECHO)){
		t1 = TCNT1;
	}
	else{
		t2 = TCNT1;
		ticks = t2 - t1;
		flag_echo = 1;
		

	}
}
