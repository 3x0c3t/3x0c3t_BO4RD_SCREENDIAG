#ifndef DRAWING_TEST_H
#define DRAWING_TEST_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#include "TFT_Config.h"
#include "ScreenDiag.h"

// ========================================
// DRAW TEST
// ========================================

void testDrawing(
  TFT_eSPI &tft,
  XPT2046_Touchscreen &touch,
  TouchCalibration &cal
) {

  Serial.println();
  Serial.println("==============================");
  Serial.println("DRAW TEST");
  Serial.println("==============================");

  Serial.println("Touchez l'ecran et dessinez.");
  Serial.println("Le dessin reste affiche.");
  Serial.println();

  tft.fillScreen(TFT_BLACK);

  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextSize(2);

  tft.drawString(
    "DRAW TEST",
    tft.width() / 2,
    8
  );

  tft.setTextDatum(TL_DATUM);

  int16_t lastX = -1;
  int16_t lastY = -1;

  while (true) {

    if (touch.touched()) {

      TS_Point p = touch.getPoint();

      int32_t screenX;
      int32_t screenY;

      // ==================================
      // RAW X -> SCREEN X
      // ==================================

      if (cal.rawRight != cal.rawLeft) {

        screenX = map(
          p.x,
          cal.rawLeft,
          cal.rawRight,
          0,
          tft.width() - 1
        );

      } else {

        screenX = tft.width() / 2;
      }

      // ==================================
      // RAW Y -> SCREEN Y
      // ==================================

      if (cal.rawBottom != cal.rawTop) {

        screenY = map(
          p.y,
          cal.rawTop,
          cal.rawBottom,
          0,
          tft.height() - 1
        );

      } else {

        screenY = tft.height() / 2;
      }

      // ==================================
      // LIMIT SCREEN
      // ==================================

      screenX = constrain(
        screenX,
        0,
        tft.width() - 1
      );

      screenY = constrain(
        screenY,
        0,
        tft.height() - 1
      );

      // ==================================
      // SERIAL
      // ==================================

      Serial.print("RAW X=");
      Serial.print(p.x);

      Serial.print(" RAW Y=");
      Serial.print(p.y);

      Serial.print(" Z=");
      Serial.print(p.z);

      Serial.print(" -> SCREEN X=");
      Serial.print(screenX);

      Serial.print(" Y=");
      Serial.println(screenY);

      // ==================================
      // DRAW
      // ==================================

      if (
        lastX >= 0 &&
        lastY >= 0
      ) {

        tft.drawLine(
          lastX,
          lastY,
          screenX,
          screenY,
          TFT_GREEN
        );

      } else {

        tft.fillCircle(
          screenX,
          screenY,
          2,
          TFT_GREEN
        );
      }

      lastX = screenX;
      lastY = screenY;

      delay(10);

    } else {

      // New stroke
      lastX = -1;
      lastY = -1;
    }

    delay(5);
  }
}

#endif