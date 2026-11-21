#include <avr/io.h>
#include <avr/interrupt.h>
#include "pinout.h"
#include "usart.h"

#define UBRR_value ((F_CPU/(16UL *9600UL))-1)
volatile char rx_byte = 0;

void usart_inic(void){
	UBRR0H =(uint8_t)(UBRR_value >> 8);
	UBRR0L =(uint8_t)(UBRR_value);
	UCSR0A =0;
	UCSR0B =(1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	UCSR0C =(1<<UCSZ01)|(1<<UCSZ00);
	
}

ISR(USART_RX_vect){
	rx_byte = UDR0;
}

void usart_transmit(char dado){
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0=dado;
	
	
}

void usart_print(const char *str){
	while(*str){
		usart_transmit(*str++);
	}
}