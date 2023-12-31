/*
 * HTTP Client GET Request
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * https://circuits4you.com 
 * Connects to WiFi HotSpot. */

// #include <ESP8266WiFi.h>
// #include <WiFiClient.h> 
// #include <ESP8266WebServer.h>
// #include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiSSLClient.h>
#include <ArduinoHttpClient.h>

#include <DHT.h>
#include <Servo.h>
#include "SR04.h"

#define SECRET_SSID ""
#define SECRET_PASS ""

/* Set these to your desired credentials. */
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;
int keyIndex = 0;                 // your network key index number (needed only for WEP)

//Web/Server address to read/write from 
char host = "10.10.39.222";   //https://circuits4you.com website or IP address of server

//=======================================================================
//                    Power on setup
//=======================================================================
int status = WL_IDLE_STATUS;
WiFiServer server(80);
// WiFiServer server(8080);

// Initialisation des broches Trig et Echo du Sonar
#define TRIG_PIN 10
#define ECHO_PIN 12

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);

// Initialisation de l'objet Servo pour le servomoteur
Servo monServo;

// Définition des broches
#define DHTPIN 2 // Broche à laquelle est connecté le capteur DHT
#define DHTTYPE DHT11 // Type de capteur DHT utilisé
#define ledVerte 4 // Broche de la LED Verte (Relais 2)
#define ledRouge 6// Broche de la LED Rouge (Relais 1)
#define ledOrange 3 // Broche de la LED Orange (LED 3)
#define ledBleu 7
#define CapteurPIR 8 // Broche à laquelle est connecté le capteur de mouvement (PIR)

// Création d'une instance de l'objet DHT
DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillisTemp = 0;
unsigned long previousMillisMotion = 0;
unsigned long previousMillisDistance = 0;

const long intervalTemp = 5000;     // Interval de 5 secondes pour la température
const long intervalMotion = 5000;   // Interval de 5 secondes pour le capteur PIR
const long intervalDistance = 5000; // Interval de 5 secondes pour la distance

// Définir une constante pour la durée pendant laquelle la LED Orange est allumée
const int orangeLEDDuration = 5000;  // 5 secondes

unsigned long orangeLEDStartTime = 0;  // Variable pour enregistrer le moment où la LED Orange a été allumée

void setup() {
  delay(1000);
  Serial.begin(9600);
  pinMode(9, OUTPUT);      // set the LED pin mode

  monServo.attach(11); // Broche DATA du Servomoteur

  // Configuration de la broche du capteur de mouvement en entrée
  pinMode(CapteurPIR, INPUT);

  // Configuration des broches en sortie pour les LED
  pinMode(ledVerte, OUTPUT);       
  pinMode(ledRouge, OUTPUT); 
  pinMode(ledOrange, OUTPUT);
  pinMode(ledBleu, OUTPUT);

  // Initialisation du capteur DHT  
  dht.begin(); 

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus(); 
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
// void loop() {
//   HTTPClient http;    //Declare object of class HTTPClient

//   String ADCData, station, getData, Link;
//   // int adcvalue=analogRead(A0);  //Read Analog value of LDR
//   // ADCData = String(adcvalue);   //String to interger conversion
//   // station = "B";

//   //GET Data
//   // getData = "?Température = " + temperature + "&Humidité = " + humidite + "&Présence = " + presence + "&Distance = " + distance ;  //Note "?" added at front
//   getData = "?Température = " + String(random(30,40)) + "&Humidité = " + String(random(30,40)) + "&Présence = " + String(random(30,40)) + "&Distance = " + String(random(30,40)) ;  //Note "?" added at front
//   Link = "http://10.10.39.222/demo/getdemo.php" + getData;
  
//   http.begin(Link);     //Specify request destination
//   http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
//   int httpCode = http.GET();            //Send the request
//   String payload = http.getString();    //Get the response payload

//   Serial.println(httpCode);   //Print HTTP return code
//   Serial.println(payload);    //Print request response payload

//   http.end();  //Close connection
  
//   delay(5000);  //GET Data at every 5 seconds
// }
//=======================================================================

void loop() {
  unsigned long currentMillis = millis();

  String temperature = "";   
  String humidite = "";
  String presence = "";
  String distanceString = "";

  // Lecture et affichage de la température et de l'humidité
  if (currentMillis - previousMillisTemp >= intervalTemp) {
    previousMillisTemp = currentMillis;

    Serial.println("Temperature: " + String(dht.readTemperature()) + " °C");
    Serial.println("Humidite: " + String(dht.readHumidity()) + " %");

    temperature = String(dht.readTemperature());
    humidite = String(dht.readHumidity());

    // Contrôle de la LED Rouge en fonction de la température
    if (dht.readTemperature() < 19) {
      digitalWrite(ledRouge, HIGH); // Allumage de la LED Rouge (Relais 1)
    } else {
      digitalWrite(ledRouge, LOW); // Extinction de la LED Rouge (Relais 1)
    }

    // Contrôle de la LED Verte en fonction de la température
    if (dht.readTemperature() > 26) {
      digitalWrite(ledVerte, HIGH); // Allumage de la LED Verte (Relais 2)
    } else {
      digitalWrite(ledVerte, LOW); // Extinction de la LED Verte (Relais 2)
    }

    // Contrôle de la LED Verte en fonction de le taux de l'humidité
    if (dht.readHumidity() > 60) {
      digitalWrite(ledVerte, HIGH); // Allumage de la LED Verte (Relais 2)
    } else {
      digitalWrite(ledVerte, LOW); // Extinction de la LED Verte (Relais 2)
    }
  }

  // Détection de mouvement avec le capteur PIR
  if (currentMillis - previousMillisMotion >= intervalMotion) {
    previousMillisMotion = currentMillis;
    presence = String(digitalRead(CapteurPIR));

    if (digitalRead(CapteurPIR) == HIGH) {
      Serial.println("mouvement detecte");
      digitalWrite(ledBleu, HIGH);
      presence = "OUI";
    } else {
      Serial.println("pas de mouvement detecte");
      digitalWrite(ledBleu, LOW);
      presence = "NON";
    }
  }

  if (currentMillis - previousMillisDistance >= intervalDistance) {
    previousMillisDistance = currentMillis;

    long distance = sr04.Distance(); // Mesure de la distance avec le Sonar
    Serial.print(distance);
    Serial.println(" cm");

    monServo.write(0); // Position initiale du Servomoteur

    if (distance < 250) {
      monServo.write(90); // Rotation du Servomoteur pour ouvrir le portail
      digitalWrite(ledOrange, HIGH); // Allumage de la LED Orange (LED 3) pendant 5 secondes
      
      // Enregistrer le moment où la LED Orange a été allumée
      orangeLEDStartTime = currentMillis;
    }

    // Éteindre la LED Orange après orangeLEDDuration
    if (currentMillis - orangeLEDStartTime >= orangeLEDDuration) {
      digitalWrite(ledOrange, LOW); // Extinction de la LED Orange (LED 3)
      monServo.write(0); // Retour du Servomoteur à la position initiale
    }

    distanceString = String(distance);
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("new client");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Your HTML response here

            // Your additional code here
            String getData, Link;
            getData = "Température = " + temperature + "&Humidité = " + humidite + "&Présence = " + presence + "&Distance = " + distanceString ;  //Note "?" added at front
            // getData = "Température=" + String(random(30, 40)) + "&Humidité=" + String(random(30, 40)) + "&Présence=" + String(random(30, 40)) + "&Distance=" + String(random(30, 40));
            Link = "http://10.10.39.222/demo/getdemo.php" + getData;

            // Making HTTP request
            WiFiSSLClient wifiSSLClient(client);
            HttpClient http(wifiSSLClient, "10.10.39.222", 80);
            http.get("/demo/getdemo.php" + getData); // remplacer http.begin(Link)

            delay(5000);

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}