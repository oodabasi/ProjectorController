#ifndef PROJECTOR_H
#define PROJECTOR_H
#include "Config.h"

class Projector
{
public:
    void setLedStatus(bool);
    void setLedCurrent(uint16_t);
    uint16_t readLight();
    bool checkLed();
    void setLightSensorStatus(bool);
    void setLedLight();
    void calculator(int);
    int absolute(int);
    uint16_t readLedCurrent();
    uint16_t resultCurrent;
    uint16_t total;
    int yeniYakinlik = MAX_VALUE_PROXIMITY;
    float artirma = 0;
    bool state = false;
    int tempTotal;

private:
    void send_command(uint8_t, uint8_t *, size_t);
    void write(uint8_t *, size_t);
    int readValue1[6] = {};
};

#endif