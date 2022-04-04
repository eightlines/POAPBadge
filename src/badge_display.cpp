#include <badge_display.h>

Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO, VSPI /* spi_num */);
Arduino_GC9A01 *tft = new Arduino_GC9A01(bus, TFT_RST, 0 /* rotation */, true /* IPS */);

#define LINE_BUF_SIZE 64  // pixel = 524, 16 = 406, 32 = 386, 64 = 375, 128 = 368, 240 = 367, no draw = 324 (51ms v 200ms)
int16_t px = 0, sx = 0;
int16_t py = 0, sy = 0;
uint8_t pc = 0;
uint16_t lbuf[LINE_BUF_SIZE];
int16_t png_dx = 0, png_dy = 0;

void BadgeDisplay::setup() {
    Serial.println("POAP Badge Setup Display");

    if (!SPIFFS.begin()) {
        Serial.println("SPIFFS FS Failed to mount");
        return;
    }

    tft->begin();
    tft->fillScreen(BLACK);
    tft->setCursor(80, 115);
    tft->setTextColor(RED);
    tft->println("INIT");
}

static void onDraw(pngle_t *pngle, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t rgba[4]) {
  uint16_t color = (rgba[0] << 8 & 0xf800) | (rgba[1] << 3 & 0x07e0) | (rgba[2] >> 3 & 0x001f);
  tft->drawPixel(x, y, color);
}

void BadgeDisplay::loadPNG(const char *path) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.printf("%s failed to open", path);
    return;
  }

  tft->fillScreen(0);
  
  pngle_t *pngle = pngle_new();
  pngle_set_draw_callback(pngle, onDraw);

  uint8_t buf[1024];
  int remain = 0;
  int len;

  while ((len = file.read(buf + remain, sizeof(buf) - remain)) > 0) {
    int fed = pngle_feed(pngle, buf, remain + len);
    if (fed < 0) Serial.printf("Error: %s", pngle_error(pngle));

    remain = remain + len - fed;
    if (remain > 0) memmove(buf, buf + fed, remain);
  }

  pngle_destroy(pngle);
  file.close();
}

void BadgeDisplay::turnOff() {
  tft->displayOff();
}

void BadgeDisplay::turnOn() {
  tft->displayOn();
}