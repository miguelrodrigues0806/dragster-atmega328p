#include <avr/io.h>
#include <avr/interrupt.h>
#include "pinout.h"
#include "CNY70.h"

void ADC_Init(void)
{
    ADMUX = (1 << REFS0); //Configuração da tensão de referência do ADC -> AREF = AVCC = 5V

    ADCSRA = (1 << ADEN) |  //Ativa o ADC
             (1 << ADPS2)|  //Configuração do prescaler = 64
             (1 << ADPS1);  //Configuração do prescaler = 64

    DIDR0 = (1 << ADC0D) | //Desativação do buffer da entrada analógica de PC0
            (1 << ADC1D) | //Desativação do buffer da entrada analógica de PC1
            (1 << ADC2D);  //Desativação do buffer da entrada analógica de PC2
}

uint16_t Read_ADC(uint8_t canal)
{
    ADMUX = (ADMUX & 0xF0) | (canal & 0x0F); //

    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));

    return ADC;
}