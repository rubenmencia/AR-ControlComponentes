#include <IRremote.h>
 
const int RECV_PIN = 9;
const long RED_KEY = 0xFF22DD;
 
IRrecv irrecv(RECV_PIN);
decode_results results;
 
void setup()
{
   Serial.begin(9600);
   irrecv.enableIRIn();
}
 
void loop()
{  
   if (irrecv.decode(&results))
   {
      Serial.println(results.value, HEX);    
      irrecv.resume();
   }
}
