#ifndef BADGE_SENSORS_H
#define BADGE_SENSORS_H

#include <Arduino.h>
#include <Wire.h>
#include "telit_bma400.h"

class BadgeSensors {
public:
    BadgeSensors() {};
    void setup();
    void update();
    unsigned long lastActivity();
    int tap();
private:
    int8_t configureBMA400();
    int8_t configureTap();
    int8_t configureActivity();
};

#endif