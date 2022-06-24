#include <Wire.h>
#include "Projector.h"
#include "Arduino.h"
#include "Config.h"


void Projector::send_command(uint8_t slave_address, uint8_t *data, size_t size)
{
    Wire.beginTransmission(slave_address);
    if (size > 1)
        Wire.write(data, size);
    else
        Wire.write(data[0]);
    Wire.endTransmission();
}

void Projector::setLightSensorStatus(bool status)
{
    uint8_t data[2];
    data[0] = PROJECTOR_OPEN_LED_SENSOR_ADDRESS;
    data[1] = status ? PROJECTOR_OPEN_LED_SENSOR_COMMAND : PROJECTOR_OPEN_CLOSE_COMMAND;
    send_command(PROJECTOR_READ_LIGHT_ADDRESS, data, sizeof(data));
}

void Projector::setLedStatus(bool status)
{
    uint8_t data[2];
    data[0] = PROJECTOR_LED_ADDRESS;
    data[1] = status ? PROJECTOR_OPEN_LED_COMMAND : PROJECTOR_OPEN_CLOSE_COMMAND;
    send_command(PROJECTOR_READ_LED_ADDRESS, data, sizeof(data));
    Serial.println("INFO: Projector::openLed");
}

void Projector::setLedCurrent(uint16_t value)
{
    uint8_t val1 = (uint8_t)(value & 0xff);
    uint8_t val2 = (uint8_t)((value >> 8) & 0xff);
    uint8_t command[] = {PROJECTOR_PWM_ADDRESS, val1, val2, val1, val2, val1, val2};
    send_command(PROJECTOR_READ_LED_ADDRESS, command, sizeof(command));
}

uint16_t Projector::readLedCurrent()
{
    uint8_t command[] = {PROJECTOR_READ_CURRENT_ADDRESS};
    send_command(PROJECTOR_READ_LED_ADDRESS, command, sizeof(command));
    Wire.requestFrom(PROJECTOR_READ_LED_ADDRESS, 6);
    while (Wire.available())
    {
        for (size_t i = 0; i < 6; i++)
        {
            readValue1[i] = Wire.read();
        }
    }

    resultCurrent = ((readValue1[5] << 8) + readValue1[4]);
    return resultCurrent;
}

bool Projector::checkLed()
{
    uint8_t command[] = {PROJECTOR_CHECK_LED_ADDRESS};
    send_command(PROJECTOR_READ_LED_ADDRESS, command, sizeof(command));

    Wire.requestFrom(PROJECTOR_READ_LED_ADDRESS, 1);
    int result = Wire.read();
    if (result == 7 || result == 4)
        return true;
    return false;
}

uint16_t Projector::readLight()
{
    uint8_t data2[] = {PROJECTOR_READ_LIGHT_COMMAND};
  
    for (int i = 0; i < 10; i++)
    {
        send_command(PROJECTOR_READ_LIGHT_ADDRESS, data2, sizeof(data2));
        Wire.requestFrom(PROJECTOR_READ_LIGHT_ADDRESS, 2);
        uint16_t result = Wire.read();
        uint16_t result2 = Wire.read();
        total = result2 << 8 | result;
        Serial.print(i+1);
        Serial.print(". Total: ");
        Serial.println(total);
        calculator(absolute(LED_SENSOR_VALUE-total));
        delay(20);      
    }
    if(state)
    {
        Serial.print("Islem sonucu: ");
        Serial.println(tempTotal);
       // Serial.println(LED_SENSOR_VALUE - yeniYakinlik);
       // return LED_SENSOR_VALUE - yeniYakinlik;
       return tempTotal;
    }
    else return 0;
}

void Projector::calculator(int yakinlik)
{   
    Serial.print("Calculator'a girdi yakinlik değeri: ");
    Serial.println(yakinlik);
    if (yakinlik<=yeniYakinlik)
    {
        yeniYakinlik = yakinlik;
        tempTotal = total;
        state = true;
        Serial.println("Yakinlik degisti!");
    }
}
 
int Projector::absolute(int value)
{
    if (value < 0)
        return -value;
    else
        return value;
}

void Projector::setLedLight()
{
    uint16_t ledCurrentValue = readLedCurrent();
    uint16_t lightSensorValue = readLight();
    if(state){
        
        Serial.print("Light Value: ");
        Serial.println(lightSensorValue);
        artirma = yeniYakinlik / 2.7;
        if(lightSensorValue<LED_SENSOR_VALUE){
            ledCurrentValue += artirma;
            Serial.print("Artirilmiş LedCurrent: ");
            Serial.println(ledCurrentValue);
            setLedCurrent(ledCurrentValue);
            delay(2000);
            uint8_t data2[] = {PROJECTOR_READ_LIGHT_COMMAND};
            send_command(PROJECTOR_READ_LIGHT_ADDRESS, data2, sizeof(data2));
            Wire.requestFrom(PROJECTOR_READ_LIGHT_ADDRESS, 2);
            uint16_t result = Wire.read();
            uint16_t result2 = Wire.read();
            total = result2 << 8 | result;
            Serial.print("Son Light Value: ");
            Serial.println(total);  
        }
        else if (lightSensorValue>LED_SENSOR_VALUE){
            ledCurrentValue -= artirma;
            Serial.print("Azaltilmiş LedCurrent: ");
            Serial.println(ledCurrentValue);
            setLedCurrent(ledCurrentValue);
            delay(1000);
            uint8_t data2[] = {PROJECTOR_READ_LIGHT_COMMAND};
            send_command(PROJECTOR_READ_LIGHT_ADDRESS, data2, sizeof(data2));
            Wire.requestFrom(PROJECTOR_READ_LIGHT_ADDRESS, 2);
            uint16_t result = Wire.read();
            uint16_t result2 = Wire.read();
            total = result2 << 8 | result;
            Serial.print("Son Light Value: ");
            Serial.println(total);

        }
    }
    yeniYakinlik = MAX_VALUE_PROXIMITY;
}

