#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <TFT_eSPI.h>

void drawSplashScreen(TFT_eSPI &tft) {

  int16_t width = tft.width();
  int16_t height = tft.height();

  tft.fillScreen(TFT_BLACK);

  tft.setTextDatum(MC_DATUM);

  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextSize(3);

  tft.drawString(
    "-3x0c3t-",
    width / 2,
    height / 2 - 35
  );

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(2);

  tft.drawString(
    "BO4RD",
    width / 2,
    height / 2 + 5
  );

  tft.drawString(
    "SCREEN DIAG",
    width / 2,
    height / 2 + 30
  );

  int16_t barWidth = width - 60;
  int16_t barHeight = 8;
  int16_t barX = 30;
  int16_t barY = height - 35;

  tft.drawRect(
    barX,
    barY,
    barWidth,
    barHeight,
    TFT_DARKGREY
  );

  for (int16_t i = 0; i <= barWidth - 4; i += 4) {

    tft.fillRect(
      barX + 2,
      barY + 2,
      i,
      barHeight - 4,
      TFT_CYAN
    );

    delay(8);
  }

  delay(500);

  tft.setTextDatum(TL_DATUM);
}

#endif