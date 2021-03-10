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

/*  GPIO D13 & GPIO D15 are used by WiFi.h Library 
*   Connect Analog pin A0 of MQ6 to GPIO D34 pin
*   GPIO pin D34 is input only pin (also known as ADC1 CH6)
*/

#define SENSOR_MQ6 34 // MQ6 Sensor analog pin A0 at GPIO pin 34
#define LED_GREEN 13  // LED GREEN output pin at GPIO pin 13
#define LED_RED 12    // LED RED output pin at GPIO pin 12
#define BUILT_LED 2   // BUILTIN LED output at GPIO pin 2

int sensorValue;   // For storing the analog input value from sensor to ESP32( max 4095 )
float sensorVolts; // For storing the voltage input value from sensor to ESP32 ( max 5.0 )

void connectionToWiFi()
{
  Serial.print("\n\nConnecting to WiFi ");
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
    Serial.println("\nFailed to Connect WiFi !"); // it prints the fail message on serial interface
  }
  else
  {
    Serial.print("\n\nConnected to WiFi ! IP add. : "); // it prints the success message on serial
    Serial.print(WiFi.localIP());                       // it prints the IP address of ESP32 on serial
  }
}

void readSensor()
{

  // read analog input from GPIO 34 of ESP32 ( ADC1 CH6 == GPIO 34 )
  for (int i = 0; i < 100; i++)
  {
    // this loop reads the value 100 times then stores it
    sensorValue = sensorValue + analogRead(SENSOR_MQ6);
  }

  // ESP32 ADC max value 4095 and Voltage we used 5.0
  sensorValue = sensorValue / 100;            // get average reading
  sensorVolts = sensorValue * (5.0 / 4095.0); //convert to voltage

  // MQ6 sends 3.4V or above till max 5.0V to ESP32
  if (sensorVolts > 3.4)
  {
    Serial.println("\n\nGas detected !");
    Serial.printf("\nSensor Value = %.2f", (float)sensorValue);
    Serial.printf("\nSensor Volts = %.5f", (float)sensorVolts);

    digitalWrite(BUILT_LED, HIGH);
    delay(100);
    digitalWrite(BUILT_LED, LOW);
    delay(100);
  }
  else
  {
    Serial.println("\n\nGas not detected !");
    Serial.printf("\nSensor Value = %.2f", (float)sensorValue);
    Serial.printf("\nSensor Volts = %.5f", (float)sensorVolts);
    delay(200);
  }
  delay(100);
}

void setup()
{
  // put your setup code here, to run once:

  pinMode(BUILT_LED, OUTPUT);
  pinMode(SENSOR_MQ6, INPUT);

  Serial.begin(9600);
  connectionToWiFi();
}

void loop()
{
  // put your main code here, to run repeatedly:
  readSensor();
}