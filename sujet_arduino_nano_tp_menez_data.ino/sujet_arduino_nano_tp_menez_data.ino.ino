// Import required libraries
#include <WiFi.h>

//les parametres -------------- WiFi parameters--------------------//

const char* ssid     = "Livebox-DBC2";
const char* password = "krP3hrdkAnFsTiHWKW";


//----------------declaration des variables -----------------------//

const int led_temp = 12;
const int led_sens = 18;
const int cap_sens = 25;
const int led_pin = 22;
const int led_obscure = 23;
const int lumiere_pin = 33;
const int temperature_pin = 32;
const int light_buzzer= 15;
const int temp_buzzer = 27;
const int sens_buzzer = 2;




 
//-----------------------definition de Host-------------------------//

const char* host = "dweet.io";

void setup() {
  
//--------------------------------bonnes------------------------//
  pinMode(led_pin,OUTPUT);
  pinMode(led_obscure,OUTPUT);
  pinMode(led_temp,OUTPUT);
  pinMode(lumiere_pin, INPUT);
  pinMode(temperature_pin, INPUT);
  pinMode(light_buzzer,OUTPUT);
  pinMode(temp_buzzer,OUTPUT);
  pinMode (sens_buzzer,OUTPUT);
  pinMode(led_sens,OUTPUT);
  pinMode(cap_sens,INPUT);
   // Start Serial
  Serial.begin(115200);
  delay(10);

  
//-----------------------------connexion wifi----------------------//
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

//------------------------------connexion à l Host------------------//
  Serial.print("Connecting to ");
  Serial.println(host);
  
//-----Utilisation de la classe WiFiClient pour creer la connexion TCP---//
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


//--------------------------------------bonnes ----------------------//

  float temperature_status = analogRead(temperature_pin)/100;

    if(temperature_status >=15){
      digitalWrite(temp_buzzer,HIGH);
      digitalWrite(led_temp, HIGH);
      delay(500);     
      digitalWrite(led_temp, LOW);
      delay(500);
     }
     else
     {
      digitalWrite(temp_buzzer,LOW);
       digitalWrite(led_temp, LOW);
     }

    Serial.print("Temperature: ");
    Serial.print(temperature_status);
    Serial.println(" C");

  
  float lumiere_status = analogRead(lumiere_pin)/10;

   if(lumiere_status <= 10){
    digitalWrite(light_buzzer,HIGH);
    //digitalWrite(led_pin, HIGH);
    delay(500); 
    digitalWrite(led_obscure, HIGH); 
    }
      else
    {
      digitalWrite(light_buzzer,LOW);
      //digitalWrite(led_pin, LOW);  
      digitalWrite(led_obscure, LOW);   
    }

    Serial.print("Luminosite: ");
    Serial.print(lumiere_status);
    Serial.println(" %");


   float sensor_status = digitalRead(cap_sens);
   if(sensor_status == 0){
    digitalWrite(led_sens, HIGH); 
    digitalWrite(sens_buzzer,HIGH);
    }
      else
    {
      digitalWrite(led_sens, LOW);
      digitalWrite(sens_buzzer,LOW);  
    }

    Serial.print("Sensoriel: ");
    Serial.print(sensor_status);
    Serial.println(" %");

  
  
  //-----Envoie de la requete au server Dweet---------------------------//
  
  client.print(String("GET /dweet/for/bddarduino?temperature=") + String(temperature_status) + "&luminosite=" + String(lumiere_status) +"&sensoriel=" + String(sensor_status) + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  
  // Repeat every 1 seconds
  delay(1000);
 
}
