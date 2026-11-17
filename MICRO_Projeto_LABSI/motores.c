#include <avr/io.h>
#include "pinout.h"
#include "motores.h"

void motores_init(void) {
	// Configurar pinos de direção do L298N como saída e a nível baixo (parados)
	DDRB |= (1 << PIN_MOT_IN1) | (1 << PIN_MOT_IN2) | (1 << PIN_MOT_IN3) | (1 << PIN_MOT_IN4);
	PORTB &= ~((1 << PIN_MOT_IN1) | (1 << PIN_MOT_IN2) | (1 << PIN_MOT_IN3) | (1 << PIN_MOT_IN4));
}