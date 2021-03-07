#include <Arduino.h>
#include "WiFi.h"

/* Author : Aslam Shaikh
*  Date : 07-03-2021
*  IDE : VS Code 1.54.1
*  Board : DOIT ESP32 DEVKIT V1 
*/

#define WIFI_NETWORK "ASLAM SHAIKH 1" // defined constant value wifi ssid
#define WIFI_PASSWORD "8855954049vbn" // defined constant value wifi pass
#define WIFI_TIMEOUT_MS 60000         // defined constant value 60 seconds

void connectionToWiFi()
{
  Serial.print("Connecting to WiFi ");
  WiFi.mode(WIFI_STA);                     // sets ESP32 operating mode as station/client
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD); // passed ssid and pass and started connection

  unsigned long startAttemptTime = millis(); // millis() assings starting time of ESP 32

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS)
  {
    Serial.print(" . "); // prints the " . " after every 100 milliseconds
    delay(100);          // this loop ends when ESP32 connects to the wifi
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Failed to Connect WiFi "); // it prints the fail message on serial interface
  }
  else
  {
    Serial.println("Connected to WiFi "); // it prints the success message on serial
    Serial.println(WiFi.localIP());       // it prints the IP address of ESP32 on serial
  }
}

void setup()
{
  // put your setup code here, to run once:

  pinMode(2, OUTPUT);
  Serial.begin(9600);
  connectionToWiFi();
}

void loop()
{
  // put your main code here, to run repeatedly:

  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  delay(100);
}