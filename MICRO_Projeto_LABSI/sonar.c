#include <avr/io.h>
#include "pinout.h"
#include "sonar.h"

void timer1_sonar_inic(void){
   TCCR1A = 0;
   TCCR1B = 0;
   TCNT1 = 0;
   TIMSK1 = 0;
   TCCR1B = (1<<CS11); // Prescaler 8
}

void sonar_init(void){

   DDRD|= (1<<PIN_SONAR_TRIG);
   DDRD&=~(1<<PIN_SONAR_ECHO);
   timer1_sonar_inic();
}
