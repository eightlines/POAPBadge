# POAPBadge
Smart Badge for displaying and trading POAPs. Based on the [Open Smart Watch](https://open-smartwatch.github.io/watches/light-edition/) ESP32 Pico + GC9A01 TFT Display.

# Requirements
* [OSW Light Edition](https://a.aliexpress.com/_mKoyMox)
* [Round 450mA LiPo](https://a.aliexpress.com/_mrvOz8P)
* PlatformIO + ESP Pico Kit
* WCH IC CH341 Drivers [WIN](http://www.wch-ic.com/downloads/CH341SER_ZIP.html) / [MAC OS](http://www.wch-ic.com/downloads/CH341SER_MAC_ZIP.html)
* Arduino_GFX
* Pngle

# Uploading Firmware
* Connect the OSW to USB
* Hold down BTN1 FLASH
* Momentarily Press EN RESET while continuing to hold down BTN1 FLASH
* Once PlatformIO begins to upload (% indicator) you may release BTN1 FLASH
* Following a valid upload, press EN RESET to begin the App (Serial Monitor may be started at this point)
