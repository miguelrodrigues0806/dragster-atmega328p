// config.h - Atribuição Oficial de Pinos ATmega328P
#ifndef CONFIG_H
#define CONFIG_H

// Comunicação Bluetooth (USART)
#define PIN_RX          0 // PD0
#define PIN_TX          1 // PD1

// Sensores de Obstáculos e Controlo
#define PIN_SONAR_ECHO  2 // PD2 (INT0)
#define PIN_BTN_START   3 // PD3 (INT1)
#define PIN_SONAR_TRIG  4 // PD4

// Motores - PWM (Timer 0)
#define PIN_PWM_ENA     5 // PD5 (OC0B)
#define PIN_PWM_ENB     6 // PD6 (OC0A)

// Motores - Direção (L298N)
#define PIN_MOT_IN1     0 // PB0
#define PIN_MOT_IN2     2 // PB2
#define PIN_MOT_IN3     4 // PB4
#define PIN_MOT_IN4     5 // PB5

// Sinalização LABSI
#define PIN_LED_1HZ     1 // PB1

// Sensores Analógicos (ADC)
#define ADC_CNY_LEFT    0 // PC0 (A0)
#define ADC_CNY_CENTER  1 // PC1 (A1)
#define ADC_CNY_RIGHT   2 // PC2 (A2)
#define ADC_BATTERY     5 // PC5 (A5)

#endif