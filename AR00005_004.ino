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

long capturado=0;

const int RECV_PIN = 9;
const int led = 11;

bool flag=false;
 
IRrecv irrecv(RECV_PIN);
decode_results results;
 
void setup()
{
   irrecv.enableIRIn();
   pinMode(led, OUTPUT); 
   Serial.begin(9600);
}
 
void loop()
{  
  
  
   if (irrecv.decode(&results))
   {
    capturado=results.value;
    
      switch(results.value){
        case KEY_OFF: 
        flag=false;    
          progOff();
          
          break;
        case KEY_ON: 
        flag=false;        
         progOn();

         break;
        case KEY_1:     
        flag=true;   
         prog1();
         break;

        case KEY_2:     
        flag=true;   
         prog2();
         break;
        case KEY_3:     
        flag=true;   
         prog3();
         break;
         
      }
            
    if(!flag){
      
       irrecv.resume(); 
      }
    
      
      //Serial.println(results.value, HEX);
    
   }


   
}

void progOff()
{
 
  digitalWrite(led, LOW);
 
}

void progOn()
{

digitalWrite(led, HIGH);

}

void prog1()
{
   irrecv.resume();
   
  while(irrecv.decode(&results)==0){
  digitalWrite(led, HIGH);   // poner el Pin en HIGH
  delay(1000);                   // esperar un segundo
  digitalWrite(led, LOW);    // poner el Pin en LOW
  delay(1000); // esperar un segundo

    if (irrecv.decode(&results) && (results.value==KEY_ON or results.value==KEY_OFF or results.value==KEY_2 or results.value==KEY_3))
    {
    break;
    }
    else{
      irrecv.resume();
      }

  }

  }


  void prog2()
{
   irrecv.resume();
   
  while(irrecv.decode(&results)==0){
  digitalWrite(led, HIGH);   // poner el Pin en HIGH
  delay(500);                   // esperar un segundo
  digitalWrite(led, LOW);    // poner el Pin en LOW
  delay(500); // esperar un segundo

    if (irrecv.decode(&results) && (results.value==KEY_ON or results.value==KEY_OFF or results.value==KEY_1 or results.value==KEY_3))
    {
    break;
    }
    else{
      irrecv.resume();
      }

  }

  }

    void prog3()
{
   irrecv.resume();
   
  while(irrecv.decode(&results)==0){
  digitalWrite(led, HIGH);   // poner el Pin en HIGH
  delay(250);                   // esperar un segundo
  digitalWrite(led, LOW);    // poner el Pin en LOW
  delay(250); // esperar un segundo

    if (irrecv.decode(&results) && (results.value==KEY_ON or results.value==KEY_OFF or results.value==KEY_1 or results.value==KEY_2))
    {
    break;
    }
    else{
      irrecv.resume();
      }

  }

  }
