
#ifndef ENCODERS_H
#define ENCODERS_H

#include <stdint.h>

void encoders_init(void);

void encoders_calcula_rpm(void);

uint16_t encoder_get_rpm_left(void);
uint16_t encoder_get_rpm_right(void);

#endif
