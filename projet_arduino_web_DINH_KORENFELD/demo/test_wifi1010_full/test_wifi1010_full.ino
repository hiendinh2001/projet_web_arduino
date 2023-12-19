#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiSSLClient.h>
#include <ArduinoHttpClient.h>

#include <DHT.h>
#include <Servo.h>
#include "SR04.h"
#include "Ultrasonic.h"

#define SECRET_SSID "linksys"
#define SECRET_PASS ""

/* Set these to your desired credentials. */
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;

int status = WL_IDLE_STATUS;
IPAddress ip(192,168,1,101);
WiFiServer server(80);
WiFiClient client;

// Initialisation des broches Trig et Echo du Sonar
#define TRIG_PIN 12
#define ECHO_PIN 11

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

  if (client.connect(ip, 80)) {
    Serial.println("connected");
 
    String getData = "?temperature=" + temperature + "&humidite=" + humidite + "&presence=" + presence + "&distance=" + distanceString;
    String req = "GET /demo/getdemo.php" + getData + " HTTP/1.0";

    Serial.println(req);

    client.println(req);

    client.println();

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