# POAPBadge
Smart Badge for displaying and trading POAPs. Based on the [Open Smart Watch](https://open-smartwatch.github.io/watches/light-edition/) ESP32 Pico + GC9A01 TFT Display.

# Requirements
* [OSW Light Edition](https://a.aliexpress.com/_mKoyMox)
* [Round 450mA LiPo](https://a.aliexpress.com/_mrvOz8P)
* [PlatformIO](https://platformio.org/) + ESP Pico Kit
* WCH IC CH341 Drivers [WIN](http://www.wch-ic.com/downloads/CH341SER_ZIP.html) / [MAC OS](http://www.wch-ic.com/downloads/CH341SER_MAC_ZIP.html)
* [Arduino_GFX](https://registry.platformio.org/libraries/adafruit/Adafruit%20GFX%20Library)
* [Pngle](https://github.com/kikuchan/pngle)

# Uploading Firmware
* Connect the OSW to USB
* Hold down BTN1 FLASH
* Momentarily Press EN RESET while continuing to hold down BTN1 FLASH
* Once PlatformIO begins to upload (% indicator) you may release BTN1 FLASH
* Following a valid upload, press EN RESET to begin the App (Serial Monitor may be started at this point)

# Building & Uploading Filesystem Image
* 240x240px PNG files need to be added to the /data folder
* Click on the PlatformIO menu item (Left hand column, bottom icon)
* Serial Monitor tasks must be ended (Ctrl-C)
* Project Tasks > pico32 > Platform > Build Filesystem Image
* Project Tasks > pico32 > Platform > Upload Filesystem Image (Using same process from Uploading Firmware button presses)

# 3D Printed Files
* [3D Model](https://a360.co/3DznrJ3)
* [STLs & 3MF Files](https://github.com/eightlines/POAPBadge/tree/main/models)
    * Print 1 Top, 1 Bottom, 4 Buttons
* Model has not been printed yet and may contain incorrect measurements