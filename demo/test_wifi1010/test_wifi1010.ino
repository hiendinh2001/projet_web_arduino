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

void setup() {
  delay(1000);
  Serial.begin(9600);
  pinMode(9, OUTPUT);      // set the LED pin mode

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
            String temperature, humidite, presence, distance, getData, Link;
            // getData = "Température = " + temperature + "&Humidité = " + humidite + "&Présence = " + presence + "&Distance = " + distance ;  //Note "?" added at front
            getData = "Température=" + String(random(30, 40)) + "&Humidité=" + String(random(30, 40)) + "&Présence=" + String(random(30, 40)) + "&Distance=" + String(random(30, 40));
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