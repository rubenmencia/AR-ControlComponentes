#include <IRremote.h>
 
const long KEY_ON = 0xFFA25D;
const long KEY_OFF = 0xFFE21D;
const long KEY_RED = 0xFF22DD;
const long KEY_GREEN = 0xFF02FD;
const long KEY_DARKBLUE = 0xFFC23D;
const long KEY_YELLOW = 0xFFE01F;
const long KEY_PURPLE = 0xFFA857;
const long KEY_BLUE = 0xFF906F;
const long KEY_WHITE = 0xFF6897;
const long KEY_UP = 0xFF9867;
const long KEY_DOWN = 0xFFB04F;
const long KEY_1 = 0xFF30CF;
const long KEY_2 = 0xFF18E7;
const long KEY_3 = 0xFF7A85;
const long KEY_4 = 0xFF10EF;
const long KEY_5 = 0xFF38C7;
const long KEY_6 = 0xFF5AA5;
const long KEY_7 = 0xFF42BD;
const long KEY_8 = 0xFF4AB5;
const long KEY_9 = 0xFF52AD;
const long KEY_REPEAT = 0xFFFFFFFF;
const int RECV_PIN = 9;
const int led = 11;
 
IRrecv irrecv(RECV_PIN);
decode_results results;
 
void setup()
{
   Serial.begin(9600);
   irrecv.enableIRIn();
   pinMode(led, OUTPUT); 
}
 
void loop()
{  
   if (irrecv.decode(&results))
   {
      switch(results.value){
        case KEY_OFF: 
        digitalWrite(led, LOW);
        break;
        case KEY_ON: 
        digitalWrite(led, HIGH);
      }
      
      //Serial.println(results.value, HEX);
      
      irrecv.resume();
   }
}
