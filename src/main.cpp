#include <Arduino.h>

#include "badge_pins.h"
#include "badge_buttons.h"
#include "badge_display.h"
#include "badge_sensors.h"

BadgeButtons buttons;
BadgeDisplay display;
BadgeSensors sensors;

#define INACIVITY_TIMEOUT 10000

void setup() {
  Serial.begin(115200);
  Serial.println("POAP Badge Init");

  buttons.setup();
  display.setup();
  sensors.setup();

  display.loadPNG("/poap01.png");
}

void loop() {
  sensors.update();
  // unsigned long lastActive = sensors.lastActivity();
  // int tapResult = sensors.tap();
  // Serial.println(lastActive);
  // if (millis() - lastActive > INACIVITY_TIMEOUT) {
  //   Serial.println("Display Off");
  //   display.turnOff();
  // } else {
  //   display.turnOn();
  // }

  int buttonVal = buttons.check();
  String path = "";
  if (buttonVal != -1) {
    switch (buttonVal) {
      case 0: path = "/poap01.png"; break;
      case 1: path = "/poap02.png"; break;
      case 2: path = "/poap01.png"; break;
      default: path = "/poap01.png"; break;
    }

    Serial.printf("Load POAP for Button %d", buttonVal);
    Serial.println();

    display.loadPNG(path.c_str());
  }
}