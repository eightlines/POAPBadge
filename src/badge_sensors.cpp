#include <badge_sensors.h>

struct bma400_dev bma;
int8_t result;

void BadgeSensors::setup() {
    Serial.println("POAP Badge Setup Sensors");
    
    result = bma400_interface_init(&bma, BMA400_I2C_INTF);
    bma400_check_rslt("bma400_interface_init", result);

    result = bma400_soft_reset(&bma);
    bma400_check_rslt("bma400_soft_reset", result);

    result = bma400_init(&bma);
    bma400_check_rslt("bma400_init", result);

    if (result == BMA400_OK) {
        Serial.println("BMA400 Self Test Passed");
    }
}
