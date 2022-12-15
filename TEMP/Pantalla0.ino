#include "TM1637.h"
#define CLK 3    
#define DIO 2

TM1637 Display1(CLK,DIO);
int8_t Digits[] = {1,2,3,4};

void setup()
   {  
       Display1.set();
       Display1.init() ;
   }

void loop()
   {
        Display1.display(Digits);
   }
