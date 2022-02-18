int option;
int led = 9;
 
void setup(){
  Serial.begin(9600);
  pinMode(led, OUTPUT); 
}
 
void loop(){
  //si existe datos disponibles los leemos
  if (Serial.available()>0){
    //leemos la opcion enviada
    option=Serial.read();
    if(option=='0') {
      digitalWrite(led, LOW);
      Serial.println("OFF");
    }
    else if(option=='1') {
      digitalWrite(led , HIGH);   // poner el Pin en HIGH
      Serial.println("ON");

    }
    else{
      Serial.println("Entrada incorrecta.");
      }
  }
}
