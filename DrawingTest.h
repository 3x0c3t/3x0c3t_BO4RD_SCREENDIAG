#ifndef DRAWING_TEST_H
#define DRAWING_TEST_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#include "TFT_Config.h"
#include "ScreenDiag.h"

// ========================================
// DRAW APP CONSTANTS
// ========================================

const int16_t DRAW_HEADER_HEIGHT = 42;
const int16_t DRAW_FOOTER_HEIGHT = 48;

const int16_t DRAW_BUTTON_CLEAR = 70;
const int16_t DRAW_BUTTON_EXIT = 70;

// ========================================
// DRAW APP UI
// ========================================

void drawDrawingUI(
  TFT_eSPI &tft
) {

  int16_t width = tft.width();
  int16_t height = tft.height();

  int16_t drawTop =
    DRAW_HEADER_HEIGHT;

  int16_t drawBottom =
    height -
    DRAW_FOOTER_HEIGHT;

  // ======================================
  // BACKGROUND
  // ======================================

  tft.fillScreen(TFT_BLACK);

  // ======================================
  // HEADER
  // ======================================

  tft.fillRect(
    0,
    0,
    width,
    DRAW_HEADER_HEIGHT,
    TFT_DARKGREY
  );

  tft.drawLine(
    0,
    DRAW_HEADER_HEIGHT - 1,
    width,
    DRAW_HEADER_HEIGHT - 1,
    TFT_CYAN
  );

  tft.setTextDatum(TL_DATUM);

  tft.setTextColor(
    TFT_CYAN,
    TFT_DARKGREY
  );

  tft.setTextSize(2);

  tft.drawString(
    "DRAW",
    10,
    12
  );

  // ======================================
  // CLEAR BUTTON
  // ======================================

  tft.drawRect(
    width - DRAW_BUTTON_CLEAR - 5,
    5,
    DRAW_BUTTON_CLEAR,
    32,
    TFT_YELLOW
  );

  tft.setTextDatum(MC_DATUM);

  tft.setTextColor(
    TFT_YELLOW,
    TFT_DARKGREY
  );

  tft.drawString(
    "CLEAR",
    width - (DRAW_BUTTON_CLEAR / 2) - 5,
    21
  );

  // ======================================
  // DRAW AREA BORDER
  // ======================================

  tft.drawRect(
    0,
    drawTop,
    width,
    drawBottom - drawTop,
    TFT_DARKGREY
  );

  // ======================================
  // FOOTER
  // ======================================

  tft.fillRect(
    0,
    height - DRAW_FOOTER_HEIGHT,
    width,
    DRAW_FOOTER_HEIGHT,
    TFT_DARKGREY
  );

  tft.drawLine(
    0,
    height - DRAW_FOOTER_HEIGHT,
    width,
    height - DRAW_FOOTER_HEIGHT,
    TFT_CYAN
  );

  // ======================================
  // PEN
  // ======================================

  tft.setTextColor(
    TFT_GREEN,
    TFT_DARKGREY
  );

  tft.drawString(
    "PEN",
    45,
    height - 24
  );

  // ======================================
  // EXIT
  // ======================================

  tft.setTextColor(
    TFT_RED,
    TFT_DARKGREY
  );

  tft.drawString(
    "EXIT",
    width - 45,
    height - 24
  );

  tft.setTextDatum(TL_DATUM);
}

// ========================================
// CLEAR DRAW AREA
// ========================================

void clearDrawingArea(
  TFT_eSPI &tft
) {

  int16_t width = tft.width();

  int16_t top =
    DRAW_HEADER_HEIGHT + 1;

  int16_t height =
    tft.height() -
    DRAW_HEADER_HEIGHT -
    DRAW_FOOTER_HEIGHT -
    2;

  tft.fillRect(
    1,
    top,
    width - 2,
    height,
    TFT_BLACK
  );

  tft.drawRect(
    0,
    DRAW_HEADER_HEIGHT,
    width,
    tft.height() -
      DRAW_HEADER_HEIGHT -
      DRAW_FOOTER_HEIGHT,
    TFT_DARKGREY
  );
}

// ========================================
// DRAW AREA TEST
// ========================================

bool isDrawingArea(
  TFT_eSPI &tft,
  int16_t x,
  int16_t y
) {

  return (
    x >= 1 &&
    x < tft.width() - 1 &&
    y > DRAW_HEADER_HEIGHT &&
    y < tft.height() - DRAW_FOOTER_HEIGHT
  );
}

// ========================================
// CLEAR BUTTON
// ========================================

bool isClearButton(
  TFT_eSPI &tft,
  int16_t x,
  int16_t y
) {

  return (
    x >= tft.width() - DRAW_BUTTON_CLEAR - 5 &&
    x < tft.width() - 5 &&
    y >= 5 &&
    y < 37
  );
}

// ========================================
// EXIT BUTTON
// ========================================

bool isExitButton(
  TFT_eSPI &tft,
  int16_t x,
  int16_t y
) {

  return (
    x >= tft.width() - 90 &&
    x <= tft.width() &&
    y >= tft.height() - DRAW_FOOTER_HEIGHT &&
    y <= tft.height()
  );
}

// ========================================
// DRAW APP
// ========================================

void testDrawing(
  TFT_eSPI &tft,
  XPT2046_Touchscreen &touch,
  TouchCalibration &cal
) {

  Serial.println();
  Serial.println("==============================");
  Serial.println("DRAW APPLICATION");
  Serial.println("==============================");

  Serial.println("Zone de dessin active.");
  Serial.println("CLEAR pour effacer.");
  Serial.println("EXIT pour revenir au TOUCH TEST.");
  Serial.println();

  drawDrawingUI(tft);

  int16_t lastX = -1;
  int16_t lastY = -1;

  while (true) {

    if (touch.touched()) {

      TS_Point p = touch.getPoint();

      int16_t screenX;
      int16_t screenY;

      convertTouch(
        tft,
        cal,
        p,
        screenX,
        screenY
      );

      // ====================================
      // EXIT
      // ====================================

      if (
        isExitButton(
          tft,
          screenX,
          screenY
        )
      ) {

        Serial.println("EXIT DRAW");

        while (touch.touched()) {
          delay(10);
        }

        delay(150);

        return;
      }

      // ====================================
      // CLEAR
      // ====================================

      if (
        isClearButton(
          tft,
          screenX,
          screenY
        )
      ) {

        Serial.println("CLEAR DRAW");

        clearDrawingArea(tft);

        lastX = -1;
        lastY = -1;

        while (touch.touched()) {
          delay(10);
        }

        delay(100);

        continue;
      }

      // ====================================
      // DRAW
      // ====================================

      if (
        isDrawingArea(
          tft,
          screenX,
          screenY
        )
      ) {

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

      } else {

        lastX = -1;
        lastY = -1;
      }

      delay(8);

    } else {

      lastX = -1;
      lastY = -1;
    }

    delay(2);
  }
}

#endif