#ifndef BADGE_SENSORS_H
#define BADGE_SENSORS_H

#include <Arduino.h>
#include <Wire.h>
#include "badge_pins.h"
#include "telit_bma400.h"

class BadgeSensors {
public:
    BadgeSensors() {};
    void setup();
};

#endif