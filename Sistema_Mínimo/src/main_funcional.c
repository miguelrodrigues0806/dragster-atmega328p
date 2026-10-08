#include <avr/io.h>

void inic(void);
int ler_ADC(void);


int main(void) {
	inic();

	while (1) {
		// 2. Lê o ADC e atualiza o PWM de forma limpa e direta
		OCR0A= ler_ADC();
	}
	return 0;
}

void inic(void){
	//PORTD -> PD6 saída PWM
	DDRD |= (1<<PORTD6);
	
	//PORTB -> Led
	DDRB |= (1<<PORTB1);
	PORTB &= ~(1<<PORTB1);
	
	//TIMER1 -> Modo CTC 1s 
	//COM1A1/COM1A0: Toggle OC1A on compare match
	//f_OC1A = f_clk/(2*N*(1+0CR1A))
	//N=256 / f_clk = 8MHz / f_OC1A = 1Hz
	//WGM13/WGM12/WGM11/WGM10: CTC TOP=OCR1A
	//CS12/CS11/CS10: prescaler 256
	OCR1A = 15624;
	TCCR1A = (1<<COM1A0);
	TCCR1B = (1<<CS12)|(1<<WGM12);
	TIMSK1 = 0;

	
	//TIMER0 -> modo PWM
	//COM0A1/COM0A0: Clear OC0A on compare match, set OC0A at BOTTOM
	//WGM02/WGM01/WGM00: TOP = 0xFF (255)
	//CS02/CS01/CS00Configurar PWM prescaler 64 fpwm próximo de 500Hz -> 490,196
	TCCR0A = (1<< COM0A1)|(1<<WGM01)|(1<<WGM00); 
	TCCR0B = (1<<CS01)|(1<<CS00);
	
	
	//ADC
	ADMUX = (1<<ADLAR)|(1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1); //prescaler 64 -> 125kHz
	
	sei();
	
}

unsigned char ler_ADC(void){
	
	ADCSRA |= (1<<ADSC);
	
	while ((ADCSRA & (1<<ADSC)) != 0);
	
	return ADCH;
}

