#include <Arduino.h>

#include "startAnimation.h"
#include "logo.h"
#include "battery.h"
#include "wifi.h"
#include "charging.h"

#include <SPI.h>
#include <TFT_eSPI.h>
#include <PNGdec.h>

#define GFXFF 1
#define FF18 &FreeSans12pt7b
#define CF_OL24 &Orbitron_Light_24

TFT_eSPI tft = TFT_eSPI();
PNG png;

#define MAX_IMAGE_WDITH 320
int16_t xpos;
int16_t ypos;

void pngDraw(PNGDRAW *pDraw)
{
  uint16_t lineBuffer[MAX_IMAGE_WDITH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}

void battery_disp(void)
{
  xpos = 10;
  ypos = 6;
  int16_t rc = png.openFLASH((uint8_t *)battery, sizeof(battery), pngDraw);
  if (rc == PNG_SUCCESS)
  {
    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
}

void charging_disp(void)
{
  xpos = 10;
  ypos = 0;
  int16_t rc = png.openFLASH((uint8_t *)charge, sizeof(charge), pngDraw);
  if (rc == PNG_SUCCESS)
  {
    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
}

void wifi_disp(void)
{
  xpos = 290;
  ypos = 2;
  int16_t rc = png.openFLASH((uint8_t *)wifi, sizeof(wifi), pngDraw);
  if (rc == PNG_SUCCESS)
  {
    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
}

void home_page(void)
{
  xpos = 26;
  ypos = 30;
  tft.fillScreen(TFT_WHITE);
  tft.drawCentreString("ID: diablo's", 160, 2, GFXFF);
  int16_t rc = png.openFLASH((uint8_t *)logo, sizeof(logo), pngDraw);
  if (rc == PNG_SUCCESS)
  {
    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
  battery_disp();
  wifi_disp();
}

void start_screen(void)
{
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_WHITE);
  size_t count = 3;
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setFreeFont(CF_OL24); 
  tft.drawCentreString("S t a r t i n g", 160, 180, GFXFF);
  for (size_t i = 0; i < count; i++)
  {
    for (int i = 0; i < frames; i++)
    {
      delay(40);
      tft.pushImage(110, 70, animation_width, animation_height, start[i]);
    }
  }
  tft.setSwapBytes(false);
  xpos = 26;
  ypos = 70;
  int16_t rc = png.openFLASH((uint8_t *)logo, sizeof(logo), pngDraw);
  if (rc == PNG_SUCCESS)
  {
    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
  delay(3000);
}

void setup()
{
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  start_screen();
  home_page();
}

void loop()
{
  battery_disp();
  delay(1000);
  charging_disp();
  delay(1000);
  tft.fillRect(0, 180, 320, 26, TFT_WHITE);
  tft.drawCentreString("Payment is sucessfull", 160, 180, GFXFF);
  delay(1000);
  tft.fillRect(0, 180, 320, 26, TFT_WHITE);
  tft.drawCentreString("Rechharge sucessfull", 160, 180, GFXFF);
  delay(1000);
  tft.fillRect(0, 180, 320, 26, TFT_WHITE);
  tft.drawCentreString("User not found !!!", 160, 180, GFXFF);
  delay(1000);
  tft.fillRect(0, 180, 320, 26, TFT_WHITE);
  tft.drawCentreString("Server not found !!!", 160, 180, GFXFF);
  delay(1000);
  tft.fillRect(0, 180, 320, 26, TFT_WHITE);
  tft.drawCentreString("Insufficent balance !!!", 160, 180, GFXFF);
  delay(1000);
  
}
