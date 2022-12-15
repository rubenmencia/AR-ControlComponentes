/* Example code for TM1637 4 digit 7 segment display with Arduino. More info: www.makerguides.com */
// Include the library:
#include <TM1637Display.h>
#include <IRremote.h>

// Define the connections pins:
#define CLK 3
#define DIO 2

const int RECV_PIN = 9;
const int ledPIN = 5;
 
IRrecv irrecv(RECV_PIN);

 
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

int cont = 0;

decode_results results;

// Create display object of type TM1637Display:
TM1637Display display = TM1637Display(CLK, DIO);
// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
// You can set the individual segments per digit to spell words or create other symbols:
const uint8_t hola[] = {
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,           // H
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_D | SEG_E | SEG_F,                           // L
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G    // A
};
const uint8_t minute[] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F
};
// Create degree Celsius symbol:
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};

void setup() {
  // Clear the display:
  display.clear();
  delay(1000);

  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(ledPIN , OUTPUT);   
}

void loop(){

     if (irrecv.decode(&results))
   {
      switch (results.value)
      {
      case KEY_ON:
         Serial.println("KEY_ON");
         cont = 0;
         display.setBrightness(7);
         display.showNumberDec(cont);
         break;
      case KEY_OFF:
         Serial.println("KEY_OFF");
         digitalWrite(ledPIN , LOW); 
         display.clear();
         break;
      case KEY_RED:
         Serial.println("KEY_RED");
         if(cont>0){
         timer();
         }
         break;
      case KEY_GREEN:
         Serial.println("KEY_GREEN");
         digitalWrite(ledPIN , LOW); 
         display.setBrightness(7);
         display.showNumberDec(cont);
         break;
      case KEY_DARKBLUE:
         Serial.println("KEY_DARKBLUE");
         digitalWrite(ledPIN , HIGH); 
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
         digitalWrite(ledPIN , LOW); 
         cont++;
         display.setBrightness(7);
         display.showNumberDec(cont);
         break;
      case KEY_DOWN:
         Serial.println("KEY_DOWN");
         if(cont > 0){
          digitalWrite(ledPIN , LOW); 
         cont--;
         display.setBrightness(7);
         display.showNumberDec(cont);
         }
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

void proc() {
  // Set the brightness:
  display.setBrightness(7);
  // All segments on:
  display.setSegments(data);
  delay(1000);
  display.clear();
  delay(1000);
  
  // Show timer:
  int i;
  for (i = 10; i >= 0; i--) {
    display.showNumberDec(i);
    delay(1000);
  }
  delay(1000);
  display.clear();
  delay(1000);
  
  // Print number in different locations, loops 2 times:
  int j;
  for (j = 0; j < 2; j++) {
    for (i = 0; i < 4; i++) {
      display.showNumberDec(i, false, 1, i);
      delay(500);
      display.clear();
    }
  }
  
  delay(1000);
  display.clear();
  delay(1000);
  // Set brightness (0-7):
  int k;
  for (k = 0; k < 8; k++) {
    display.setBrightness(k);
    display.setSegments(data);
    delay(500);
  }
  delay(1000);
  display.clear();
  delay(1000);
  // Print 1234 with the center colon:
  display.showNumberDecEx(1234, 0b11100000, false, 4, 0);
  delay(1000);
  display.clear();
  delay(1000);
  int temperature = 24;
  display.showNumberDec(temperature, false, 2, 0);
  display.setSegments(celsius, 2, 2);
  delay(1000);
  display.clear();
  delay(1000);
  display.setSegments(hola);
  delay(1000);
//  while(1);
}

void timer(){
  
  int i;
  display.clear();
  digitalWrite(ledPIN , HIGH); 
  for (i = cont; i > 0; i--) {
    display.showNumberDec(i);
    delay(1000);
  }
  display.showNumberDec(0);
  digitalWrite(ledPIN , LOW); 
  delay(1000);
  display.clear();
 
  }
