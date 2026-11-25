#include <avr/io.h>
#include "pinout.h"
#include "sonar.h"

void sonar_init(void){

   DDRD|= (1<<PIN_SONAR_TRIG);
   DDRD&=~(1<<PIN_SONAR_ECHO);
   // FALTA INICIALIZAÇÃO DO TIMER-1
}
