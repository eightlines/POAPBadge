#ifndef BADGE_BUTTONS_H
#define BADGE BUTTONS_H

#include <Arduino.h>
#include "badge_pins.h"

class BadgeButtons {
public:
    BadgeButtons() {};
    void setup();
    int check();
};

#endif