
// Pins
const int alarm_pin = 4;
const int light_buzzer= 7;
const int led_pin = 9;
const int ampoule_pin = 3;
// const int infra_pin = 2;
const int lumiere_pin = A0;
const int temperature_pin = A1;


void setup()
{
  // Set pins to output
  pinMode(led_pin,OUTPUT);
  pinMode(light_buzzer,OUTPUT);
  // pinMode(ampoule_pin,OUTPUT);
  pinMode(alarm_pin,OUTPUT);
  // pinMode(infra_pin, INPUT);
  pinMode(lumiere_pin, INPUT);
  pinMode(temperature_pin, INPUT);
  Serial.begin(9600);
  
  // Wait before starting the alarm
}


void loop()
{

   //DETECTION DE TEMPERATURE
  int temperature_status = analogRead(temperature_pin);
  if(temperature_status >=1000){
    tone(alarm_pin, 200);
    digitalWrite(led_pin, HIGH);
    delay(500);
    
    noTone(alarm_pin);
    digitalWrite(led_pin, LOW);
    delay(500);
      
    
  }else{
  
    noTone(alarm_pin);
    digitalWrite(led_pin, LOW);
      
  }
    Serial.print("Temperature: ");
    Serial.print(temperature_status);
    Serial.println(" C");
  
  
  
   //DETECTION DE LUMIERE
  int lumiere_status = analogRead(lumiere_pin);
  if(lumiere_status <= 1){
    tone(light_buzzer, 1000);
    digitalWrite(ampoule_pin, HIGH);
    delay(500);
    
    noTone(light_buzzer);
    //digitalWrite(ampoule_pin, LOW);
    
  }else{
  
    noTone(light_buzzer);
    digitalWrite(ampoule_pin, LOW);    
  
  }

    Serial.print("Luminosite: ");
    Serial.print(lumiere_status);
    Serial.println(" %");
  
    
   //DETECTEUR INFRAROUGE
/*int infra_status = digitalRead(infra_pin);
  if(infra_status >=1){
    digitalWrite(ampoule_pin, HIGH);    
  }else{
    digitalWrite(ampoule_pin, LOW);    
  }

    Serial.print("Presence: ");
    Serial.print(infra_status);
    Serial.println(" "); */
  
  
 delay(500);
}  
