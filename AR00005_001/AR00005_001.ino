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
      switch (results.value)
      {
      case KEY_ON:
         Serial.println("KEY_ON");
         break;
      case KEY_OFF:
         Serial.println("KEY_OFF");
         break;
      case KEY_RED:
         Serial.println("KEY_RED");
         break;
      case KEY_GREEN:
         Serial.println("KEY_GREEN");
         break;
      case KEY_DARKBLUE:
         Serial.println("KEY_DARKBLUE");
         break;
      case KEY_YELLOW:
         Serial.println("KEY_YELLOW");
         break;
      case KEY_PURPLE:
         Serial.println("KEY_PURPLE");
         break;
      case KEY_BLUE:
         Serial.println("KEY_BLUE");
         break;
      case KEY_WHITE:
         Serial.println("KEY_WHITE");
         break;
      case KEY_UP:
         Serial.println("KEY_UP");
         break;
      case KEY_DOWN:
         Serial.println("KEY_DOWN");
         break;
      case KEY_1:
         Serial.println("KEY_1");
         break;
      case KEY_2:
         Serial.println("KEY_2");
         break;
      case KEY_3:
         Serial.println("KEY_3");
         break;
      case KEY_4:
         Serial.println("KEY_4");
         break;
      case KEY_5:
         Serial.println("KEY_5");
         break;
      case KEY_6:
         Serial.println("KEY_6");
         break;
      case KEY_7:
         Serial.println("KEY_7");
         break;
      case KEY_8:
         Serial.println("KEY_8");
         break;
      case KEY_9:
         Serial.println("KEY_9");
         break;
      case KEY_REPEAT:
         //Serial.println("KEY_REPEAT"); //Comentada para evitar salida en pulsaciones largas
         break;
      }
      irrecv.resume();
   }
}
