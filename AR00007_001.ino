/* ENFRIADOR DE LÍQUIDOS*/
// Include the library:
#include <TM1637Display.h>
#include <IRremote.h>
#include <OneWire.h>                
#include <DallasTemperature.h>

// Define the connections pins:
#define CLK 8
#define DIO 7
#define CON_PUNTOS 0B10000000

const int pinReciever = 2;
const int pinRele = 3;
const int pinBuzzer = 5;
const int pinProbe = 6;

int maxT_prog = 31;
int minT_prog = 20;
int maxT_reg = 0;
int minT_reg = 0;
int secondsT = 5;
int secondsCold = 15;

enum mode {probe,maxProg,minProg,maxReg,minReg,seco}; 
mode modo;

bool screen = true;
//bool tapStatus = false;

IRrecv irrecv(pinReciever);
 
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
const uint8_t all[] = {0xff, 0xff, 0xff, 0xff};

// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};


const uint8_t inicio[]{
  SEG_G , SEG_G , SEG_G , SEG_G  // ----
};

const uint8_t tempProbe[] = {
  SEG_D | SEG_E | SEG_F | SEG_G,           // t
  0x00,                                    // max
  0x00,                                    // empty
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G    // S
};

const uint8_t tempMaxReg[] = {
  SEG_D | SEG_E | SEG_F | SEG_G,  // t
  SEG_A,                          // max
  0x00,                           // empty
  SEG_A | SEG_E | SEG_F           // r
};

const uint8_t tempMinReg[] = {
  SEG_D | SEG_E | SEG_F | SEG_G,  // t
  SEG_D,                          // min
  0x00,                           // empty
  SEG_A | SEG_E | SEG_F           // r
};

const uint8_t tempMaxProg[] = {
  SEG_D | SEG_E | SEG_F | SEG_G,                    // t
  SEG_A,                                            // max
0x00,                                               // empty
  SEG_A | SEG_B | SEG_E | SEG_F    | SEG_G          // P
};

const uint8_t tempMinProg[] = {
  SEG_D | SEG_E | SEG_F | SEG_G,                    // t
  SEG_D,                                            // min
  0x00,                                             // empty
  SEG_A | SEG_B | SEG_E | SEG_F    | SEG_G          // P
};

const uint8_t sec[] = {
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,            // S
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,            // E
  SEG_A | SEG_D | SEG_E | SEG_F,                    // C
    0x00, 
};

const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};

const uint8_t c[] = {
  0x00,0x00,0x00,
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};

// You can set the individual segments per digit to spell words or create other symbols:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

OneWire ourWire(pinProbe);                //Se establece el pin del bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

void setup() {
  // Clear the display:
  display.clear();
  screenOn();
  display.setSegments(inicio);
  
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(pinRele , OUTPUT);   
  sensors.begin();   //Se inicia el sensor de la sonda de temperatura.

  modo = probe;
}

void loop(){

    escucha();
  }

void escucha(){
  
   if (irrecv.decode(&results))
   {
      switch (results.value)
      {
      case KEY_ON:
         Serial.println("KEY_ON");
         screenOn();
         break;
      case KEY_OFF:
         Serial.println("KEY_OFF");
         screenOff();
         break;
      case KEY_RED:
         Serial.println("KEY_RED");
         if(cont>0){
         timer();
         }
         break;
      case KEY_GREEN:
         Serial.println("KEY_GREEN");
         digitalWrite(pinRele , LOW); 
         display.setBrightness(7);
         display.showNumberDec(cont);
         break;
      case KEY_DARKBLUE:
         Serial.println("KEY_DARKBLUE"); 

         openWater(secondsCold);
         break;
      case KEY_YELLOW:
         Serial.println("KEY_YELLOW");  

         switch(modo){
            case probe:
              getTemp_probe(secondsT);
              break;
            case maxReg:
              getMaxT_reg();
              break;    
            case minReg:
              getMinT_reg();
              break;                        
            case maxProg:
              getMaxT_prog();
              break;
            case minProg:
              getMinT_prog();
              break;
            case seco:
              getSecondsCold();
              break;            
          }
         break;
         
      case KEY_PURPLE:
         Serial.println("KEY_PURPLE");
         openWater(secondsCold);
         break;
      case KEY_BLUE:
         Serial.println("KEY_BLUE"); 
         openWater(secondsCold);       
         break;
      case KEY_WHITE:
         Serial.println("KEY_WHITE");
                
         switch(modo){
            case probe:
              display.setSegments(tempMaxReg);
              modo = maxReg;
              break;
            case maxReg:
              display.setSegments(tempMinReg);
              modo = minReg;
              break;    
            case minReg:
              display.setSegments(tempMaxProg);
              modo = maxProg;
              break;                        
            case maxProg:
              display.setSegments(tempMinProg);
              modo = minProg;
              break;
            case minProg:
              display.setSegments(sec);
              modo = seco;
              break; 
            case seco:
              display.setSegments(tempProbe);
              modo = probe;
              break;                        
          }
         
         break;
      case KEY_UP:
         Serial.println("KEY_UP");

         switch(modo){
            case probe:
              
              break;
            case maxReg:
             
              break;    
            case minReg:
             
              break;                        
            case maxProg:
               maxT_prog++;
               display.setBrightness(7);
               display.showNumberDec(maxT_prog,false,4,0);
              break;
            case minProg:
              minT_prog++;
              display.setBrightness(7);
              display.showNumberDec(minT_prog,false,4,0);
              break;
            case seco:
              secondsCold++;
              display.setBrightness(7);
              display.showNumberDec(secondsCold,false,4,0);
              break;            
          }
         break;
        
      case KEY_DOWN:
         Serial.println("KEY_DOWN");

          switch(modo){
            case probe:
              
              break;
            case maxReg:
             
              break;    
            case minReg:
             
              break;                        
            case maxProg:
               if(maxT_prog > 9){ 
                 maxT_prog--;
                 display.setBrightness(7);
                 display.showNumberDec(maxT_prog,false,4,0);
               }
              break;
            case minProg:
               if(minT_prog > 9){ 
                 minT_prog--;
                 display.setBrightness(7);
                 display.showNumberDec(minT_prog,false,4,0);
               }
              break;
            case seco:
              if(secondsCold > 0){ 
                secondsCold--;
                display.setBrightness(7);
                display.showNumberDec(secondsCold,false,4,0);
              }
              break;            
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
         example();
         break;
      case KEY_REPEAT:
         //Serial.println("KEY_REPEAT"); //Comentada para evitar salida en pulsaciones largas
         break;
      }
      irrecv.resume();
   }
  }

void example() {
  // Set the brightness:
  display.setBrightness(7);
  // All segments on:
  display.setSegments(all);
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
    display.setSegments(all);
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
  display.setSegments(done);
  delay(1000);
//  while(1);
  }

void timer(){
  
  int i;
  display.clear();
  digitalWrite(pinRele , HIGH); 
  for (i = cont; i > 0; i--) {
    display.showNumberDec(i);
    delay(1000);
  }
  display.showNumberDec(0);
  digitalWrite(pinRele , LOW); 
  delay(1000);
  display.clear();
  }

void screenOn(){

  screen = true;
  display.setBrightness(7);
  }

void screenOff(){

  screen = false;
  display.clear();
  display.setSegments(blank);
  }

void getTemp_probe(int retardo){
 
    sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
    float temp = sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

    maxT_reg = temp;
    minT_reg = temp;

    Serial.print("Temperatura= ");
    Serial.print(temp);
    Serial.println(" C");    

    if (screen){

      decimal2screen(temp);
      }
            
    while(1){

      if(millis() % (secondsT * 1000) == 0){
          sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
          temp = sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

          if(temp > maxT_reg){
            
              maxT_reg = temp;
            }

          if(temp < minT_reg){
            
              minT_reg = temp;
            }
      
          if (screen){

            decimal2screen(temp);
            }
      
        Serial.print("Temperatura= ");
        Serial.print(temp);
        Serial.println(" C");

        if(temp >= maxT_prog){

          openWater(secondsCold);
          }
      }
      
        if (irrecv.decode(&results))
        {
          switch (results.value)
          {
           case KEY_ON:
             Serial.println("KEY_ON");
             screenOn();
             decimal2screen(temp);
             break;
           case KEY_OFF:
             Serial.println("KEY_OFF");
             screenOff();
             break;
           case KEY_WHITE:          
              Serial.println("KEY_WHITE");
              screenOn();
              return;
            break;
            }
        irrecv.resume();
        }     
    }
  }
  
void getMaxT_prog(){

  display.clear();
  display.showNumberDec(maxT_prog,false,4,0);
  }

void getMinT_prog(){

  display.clear();
  display.showNumberDec(minT_prog,false,4,0);
  }

void getMaxT_reg(){

  display.clear();
  display.showNumberDec(maxT_reg);
  }

void getMinT_reg(){

  display.clear();
  display.showNumberDec(minT_reg);
  }

void getSecondsCold(){

  display.clear();
  display.showNumberDec(secondsCold,false,4,0);
  }

void openWater(int sec){

    int i;
    display.clear();
    digitalWrite(pinRele , HIGH); 
    for (i = sec; i > 0; i--) {
      display.showNumberDec(i);
      delay(1000);
    }
    display.showNumberDec(0);
    digitalWrite(pinRele , LOW); 
    delay(1000);
    display.clear();

    if(modo = probe){
      
      getTemp_probe(secondsT);
      }

  }

void decimal2screen(float j){

    j = j *10;
    int i = (int) j;

    display.clear();

    if (i/10 >= 9){
      display.showNumberDec(i/100,false,1,0);
      display.showNumberDec((i/10)%10,false,1,1);
      display.showNumberDec(i%10,false,1,2);
      }
    else{

      display.showNumberDec(i/10,false,1,0);
      display.showNumberDec(i % 10,false,1,1);
      }

    //display.showNumberDecEx(temp*100, 0b11100000, false, 2, 0);
  }
  

  
