/*
 * pinout.h
 *
 * Created: 17/11/2026 17:12:10
 *  Author: migue
 */ 


#ifndef PINOUT_H_
#define PINOUT_H_
#include <avr/io.h>

#if (F_CPU == 12000000UL)
	#define LED_OFF 750
	#define LED_ON 1500
#elif (F_CPU == 8000000UL)
	#define LED_OFF 500
	#define LED_ON 1000
#else
	#error "F_CPU nao suportado para os calculos do TIMER2!"
#endif

// Comunicação (USART) (Módulos HC-12)
#define PIN_RX          PORTD0 // PD0
#define PIN_TX          PORTD1 // PD1

// Sensor de Obstáculos (SONAR HC-SR04)
#define PIN_SONAR_ECHO  PORTD2 // PD2 (INT0)
#define PIN_BTN_START   PORTD3 // PD3 (INT1)
#define PIN_SONAR_TRIG  PORTD4 // PD4

// Motores - PWM (Timer 0)
#define PIN_PWM_ENA     PORTD5 // PD5 (OC0B)
#define PIN_PWM_ENB     PORTD6 // PD6 (OC0A)

// Motores - Direção (L298N)
#define PIN_MOT_IN1     PORTB0 // PB0
#define PIN_MOT_IN2     PORTB2 // PB2
#define PIN_MOT_IN3     PORTB4 // PB4
#define PIN_MOT_IN4     PORTB5 // PB5

// Sinalização
#define PIN_LED_1HZ     PORTB1 // PB1

// Sensores Analógicos (ADC)
#define ADC_CNY_LEFT    PORTC0 // PC0 (A0)
#define ADC_CNY_CENTER  PORTC1 // PC1 (A1)
#define ADC_CNY_RIGHT   PORTC2 // PC2 (A2)
#define ADC_BATTERY     PORTC5 // PC5 (A5)

//Encoders
#define PIN_ENC_LEFT		PORTC3 // PC3
#define PIN_ENC_RIGHT		PORTC4 // PC4


#endif /* PINOUT_H_ */