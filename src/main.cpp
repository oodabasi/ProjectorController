#include <Arduino.h>
#include <Wire.h>
#include "Projector.h"

Projector projector;

void setup()
{
  Serial.begin(9600);
  Serial.println("Started");
  delay(1000);
  Wire.begin();
  projector.setLedCurrent(600);
  projector.setLightSensorStatus(true);
  delay(1000);
}

void loop()
{
  projector.setLedStatus(true);
  delay(1000);
  projector.setLedLight();
  delay(1000);
  projector.setLedStatus(false);
  Serial.println("INFO: Projector : closeLed");
  projector.setLedCurrent(600);
  delay(3000);

}