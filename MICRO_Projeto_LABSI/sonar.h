/*
 * sonar.h
 *
 * Created: 17/11/2026 18:15:51
 *  Author: migue
 */ 


#ifndef SONAR_H_
#define SONAR_H_

#include <stdint.h>

void sonar_init(void);
void sonar_trigger(void);
uint16_t sonar_get_distance_cm(void);



#endif /* SONAR_H_ */