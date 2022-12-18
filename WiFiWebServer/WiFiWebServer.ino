/*
  WiFi Web Server

 A simple web server that shows the value of the analog input pins.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 Circuit:
 * Analog inputs attached to pins A0 through A5 (optional)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 modified 18 Dec 2022
 by Halldor Stefansson
 */

#include <string.h>
#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

int servoPin = 2;
int driverPinA = 6;
int driverPinB = 7;

int status = WL_IDLE_STATUS;

WiFiServer server(80);

Servo servoSteering;

const char *webpage = 
#include "controlPage.h"
;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  pinMode(driverPinA, OUTPUT);
  pinMode(driverPinB, OUTPUT);  
  servoSteering.attach(servoPin);
  servoSteering.write(90);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  /*
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }*/

  enable_WiFi();

  connect_WiFi();

  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();

  // turn on the LED once we've connected to the Wi-Fi
  digitalWrite(LED_BUILTIN, HIGH);
}

void enable_WiFi() {
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
}

void connect_WiFi() {
  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
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

  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("new client");
    String currentLine = "";
    // an HTTP request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the HTTP request has ended,
        // so you can send a reply        
        if (c == '\n' && currentLine.length() == 0) {
          // send a standard HTTP response header
          server.print(webpage);
          break;
        }
        
        if (c == '\n') {
          // you're starting a new line
          currentLine = "";
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLine += c;
          if (currentLine.endsWith("GET /left")) {
            servoSteering.write(45);     
          }
          if (currentLine.endsWith("GET /forward")) {
            digitalWrite(driverPinA,LOW);
            digitalWrite(driverPinB,HIGH);  
          }
          if (currentLine.endsWith("GET /right")) {
            servoSteering.write(120);     
          }
          if (currentLine.endsWith("GET /back")) {
            digitalWrite(driverPinA,HIGH);
            digitalWrite(driverPinB,LOW);   
          }
          if (currentLine.endsWith("GET /straight")) {
            servoSteering.write(90);    
          }
          if (currentLine.endsWith("GET /stop")) {
            digitalWrite(driverPinA,LOW);
            digitalWrite(driverPinB,LOW); 
          }
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
