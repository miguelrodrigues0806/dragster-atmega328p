/*
 * CNY70.h
 *
 * Created: 17/11/2026 18:13:38
 *  Author: migue
 */ 


#ifndef CNY70_H_
#define CNY70_H_

#include <stdint.h>

// Estrutura para guardar os valores lidos dos 3 sensores (0 a 1023)
typedef struct {
	uint16_t left;
	uint16_t center;
	uint16_t right;
} cny70_data_t;

void cny70_init(void);
uint16_t adc_read(uint8_t channel);
void cny70_read_all(cny70_data_t *sensors);



#endif /* CNY70_H_ */