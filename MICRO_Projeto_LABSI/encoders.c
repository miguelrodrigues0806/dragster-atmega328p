#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "encoders.h"
#include "pinout.h"


#define PULSOS_VOLTA   40 //Resolução dos Encoders -> 20 ranhuras por disco

static uint8_t estado_anterior; //A variável static permite com que o valor dessa variável não se altere ao serem chamadas interrupções

volatile uint16_t pulsos_left = 0; //Variável que guarda a quantidade de pulsos contabilizados no enc_left 
volatile uint16_t pulsos_right = 0; //Variável que guarda a quantidade de pulsos contabilizados no enc_right

volatile uint16_t rpm_left = 0; ////Variável que guarda o valor do RPM no enc_left
volatile uint16_t rpm_right = 0; ////Variável que guarda o valor do RPM no enc_right


// Inicialização dos encoders
void encoders_init(void)
{
	// PC3 e PC4 como entradas
	DDRC &= ~((1 << PIN_ENC_LEFT) |
	(1 << PIN_ENC_RIGHT));

	// Pull-ups internos habilitados
	PORTC |= (1 << PIN_ENC_LEFT) |
	(1 << PIN_ENC_RIGHT);
	
	// Habilita grupo PCINT1 -> Grupo que ativa interrupções na variação de estado dos pinos aos quais os Encoders pertecem
	PCICR |= (1 << PCIE1);
	
	// Garante que o estado inicial dos pinos dos encoders sejam lidos corretamente
	estado_anterior = PINC & ((1 << PIN_ENC_LEFT) | (1 << PIN_ENC_RIGHT)); 
	
	// Habilita PCINT11 e PCINT12 -> Habilitando que ocorra interrupção quando ocorrer variação de estado dos pinos/encoders
	PCMSK1 |= (1 << PCINT11) |
	(1 << PCINT12);

	// Limpa flag pendente
	PCIFR = (1 << PCIF1);
	
}


// Interrupção dos dois encoders
ISR(PCINT1_vect)
{
	uint8_t estado_atual = PINC  & ((1 << PIN_ENC_LEFT) | (1 << PIN_ENC_RIGHT));	//Verificação/Leitura do estado atual de todos os pinos do PORTC;

	uint8_t alteracoes =
	estado_atual ^ estado_anterior;	//Se ocorrer uma variação nos pinos PC3/4, esses fica~rão com um valor lógico alto devido à utilização do XOR

	// Encoder esquerdo
	if (alteracoes & (1 << PIN_ENC_LEFT)) // Verificação se o toggle foi feito pelo PC3
	{
		pulsos_left++; //Incremento do número de pulsos detectados pelo encoder
	}

	// Encoder direito
	if (alteracoes & (1 << PIN_ENC_RIGHT)) // Verificação se o toggle foi feito pelo PC4
	{
		pulsos_right++; //Incremento do número de pulsos detectados pelo encoder
	}

	estado_anterior = estado_atual; // Com as alterações realizadas, atualiza-se o estado_anterior dos pinos como sendo o lido nessa rotina
}


// Calcula RPM a cada 20 ms -> Resolução de 75 RPM por pulso
void encoders_calcula_rpm(void)
{
	uint16_t pulsos_A;
	uint16_t pulsos_B;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) //Esta função permite com que o valor lido não seja incrementado no meio da cópia para a outra variável
	{								  //As interrupções são desativadas durante a cópia e re-start dos contadores e depois são reativadas
									  //Tende a ser utilizada com variáveis de 16 bits ou mais, pois o MCU lê de 8-8 bits, o que poderia gerar erros com interrupções.
		//cópia atômica
		pulsos_A = pulsos_left;
		pulsos_B = pulsos_right;
		
		//Re-start dos contadores
		pulsos_left = 0;
		pulsos_right = 0;
		
		
		
	}

	// RPM = (pulsos * 60) / (PPR * T)
	// Para PPR = 40 pulsos/volta e T = 20 ms = 0,02 s
	// RPM = pulsos * 75

	rpm_left = pulsos_A * 75;
	rpm_right = pulsos_B * 75;
}


uint16_t encoder_get_rpm_left(void)
{
	uint16_t valor;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) //Utilizado para não gerar imprecisões ao copiar variáveis de 2 bytes
	{
		valor = rpm_left;
	}

	return valor;
}


uint16_t encoder_get_rpm_right(void)
{
	uint16_t valor;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		valor = rpm_right;
	}

	return valor;
}
