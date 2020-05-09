#include <IRremote.h>
 
const long KEY_ON = 0xFFA25D;
const long KEY_OFF = 0xFFE21D;
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
