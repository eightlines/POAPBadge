#include <badge_buttons.h>

#define NUM_BUTTONS 3
#define MS_DURATION 500

uint8_t buttonPins[] = {BTN_1, BTN_2, BTN_3};
uint8_t buttonClickStates[] = {LOW, HIGH, HIGH};
unsigned int lastExecTime = 0;

void BadgeButtons::setup() {
    Serial.println("POAP Badge Setup Buttons");
    pinMode(BTN_1, INPUT);
    pinMode(BTN_2, INPUT);
    pinMode(BTN_3, INPUT);
}

int BadgeButtons::check() {
    int result = -1;

    for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
        int val = digitalRead(buttonPins[i]);

        if (millis() - lastExecTime > MS_DURATION) {
            if (val == buttonClickStates[i]) {
                lastExecTime = millis();
                result = i;
            }            
        }
    }

    return result;
}
