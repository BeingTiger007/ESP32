#include <Arduino.h>
#include "WiFi.h"

#define WIFI_NETWORK "ASLAM SHAIKH 2"
#define WIFI_PASSWORD "8855954049ert"
#define WIFI_TIMEOUT_MS 60000

void connectionToWiFi()
{
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS)
  {
    Serial.print(".");
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Failed to Connect WiFi");
  }
  else
  {
    Serial.print("Connected to WiFi");
    Serial.println(WiFi.localIP());
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