const int pinBuzzer = 9;
const int EchoPin = 5;
const int TriggerPin = 6;
 
void setup() {
   Serial.begin(9600);
   pinMode(TriggerPin, OUTPUT);
   pinMode(EchoPin, INPUT);
}
 
void loop() {
   int cm = ping(TriggerPin, EchoPin);
   

    Serial.print("Distancia: ");
    Serial.print(cm);
    Serial.println(" cm");

   
   if(cm<100){
    
        //generar tono de 440Hz durante 1000 ms
        tone(pinBuzzer, 440);
        delay(1000);
       
        //detener tono durante 500ms  
        noTone(pinBuzzer);
        delay(500);
       
        //generar tono de 523Hz durante 500ms, y detenerlo durante 500ms.
        tone(pinBuzzer, 523, 300);
        //delay(500);
   
    }

   delay(1000);
}
 
int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}
