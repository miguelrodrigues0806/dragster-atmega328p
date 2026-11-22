#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include "pinout.h"
#include "motores.h"
#include "timer2.h"
#include "sonar.h"
#include "CNY70.h"
#include "usart.h"
#include "encoders.h"


uint16_t RPM_left = 0;
uint16_t RPM_right= 0;

int main(void)
{
	char msg[32];
	
    timer2_inic();
	usart_inic();
	encoders_init();



	sei();
	
    while (1) 
    {
		
		if(timer2_1s()){
	
		}
		
		if(timer2_20ms()){
			encoders_calcula_rpm();
			
			
			
		}
		
		if(timer2_100ms()){
			snprintf(msg, sizeof(msg), "Right: %u | Left: %u\r\n", RPM_right, RPM_left);
			usart_print(msg);
			
		}
		
		RPM_left = encoder_get_rpm_left();
		RPM_right = encoder_get_rpm_right();

		
		
    }
}

