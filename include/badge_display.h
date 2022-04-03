#ifndef BADGE_DISPLAY_H
#define BADGE_DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Arduino_GFX.h>
#include <databus/Arduino_ESP32SPI.h>
#include <display/Arduino_GC9A01.h>
#include <gfx_2d_print.h>
#include <gfx_util.h>

#include "FS.h"
#include "SPIFFS.h"
#include "pngle.h"

#include "badge_pins.h"

class BadgeDisplay {
public:
    BadgeDisplay() {};
    void setup();
    void loadPNG(const char *path);
};

#endif