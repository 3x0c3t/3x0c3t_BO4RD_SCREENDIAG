#ifndef DRAWING_TEST_H
#define DRAWING_TEST_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

// ========================================
// DRAWING CONFIGURATION
// ========================================

const int16_t DRAW_HEADER_HEIGHT = 42;
const int16_t DRAW_FOOTER_HEIGHT = 48;

const int16_t DRAW_BUTTON_PEN  = 80;
const int16_t DRAW_BUTTON_SAVE = 80;
const int16_t DRAW_BUTTON_EXIT = 80;

// ========================================
// DRAW AREA
// ========================================

void drawDrawingUI(
  TFT_eSPI &tft
) {

  int16_t width =
    tft.width();

  int16_t height =
    tft.height();

  int16_t footerY =
    height - DRAW_FOOTER_HEIGHT;

  // ======================================
  // BACKGROUND
  // ======================================

  tft.fillScreen(
    TFT_BLACK
  );

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

  tft.setTextDatum(
    MC_DATUM
  );

  tft.setTextColor(
    TFT_CYAN,
    TFT_DARKGREY
  );

  tft.setTextSize(2);

  tft.drawString(
    "DRAW APPLICATION",
    width / 2,
    DRAW_HEADER_HEIGHT / 2
  );

  // ======================================
  // DRAW AREA BORDER
  // ======================================

  tft.drawRect(
    0,
    DRAW_HEADER_HEIGHT,
    width,
    height -
      DRAW_HEADER_HEIGHT -
      DRAW_FOOTER_HEIGHT,
    TFT_DARKGREY
  );

  // ======================================
  // CLEAR BUTTON
  // ======================================

  tft.fillRoundRect(
    width - 58,
    5,
    52,
    30,
    5,
    TFT_BLACK
  );

  tft.drawRoundRect(
    width - 58,
    5,
    52,
    30,
    5,
    TFT_RED
  );

  tft.setTextColor(
    TFT_RED,
    TFT_BLACK
  );

  tft.setTextSize(1);

  tft.drawString(
    "CLEAR",
    width - 32,
    20
  );

  // ======================================
  // FOOTER
  // ======================================

  tft.fillRect(
    0,
    footerY,
    width,
    DRAW_FOOTER_HEIGHT,
    TFT_DARKGREY
  );

  // ======================================
  // SEPARATORS
  // ======================================

  tft.drawLine(
    DRAW_BUTTON_PEN,
    footerY,
    DRAW_BUTTON_PEN,
    height,
    TFT_BLACK
  );

  tft.drawLine(
    DRAW_BUTTON_PEN +
      DRAW_BUTTON_SAVE,
    footerY,
    DRAW_BUTTON_PEN +
      DRAW_BUTTON_SAVE,
    height,
    TFT_BLACK
  );

  // ======================================
  // PEN
  // ======================================

  tft.setTextColor(
    TFT_GREEN,
    TFT_DARKGREY
  );

  tft.setTextSize(2);

  tft.drawString(
    "PEN",
    DRAW_BUTTON_PEN / 2,
    footerY + 24
  );

  // ======================================
  // SAVE
  // ======================================

  tft.setTextColor(
    TFT_YELLOW,
    TFT_DARKGREY
  );

  tft.setTextSize(1);

  tft.drawString(
    "SAUVEGARDER",
    DRAW_BUTTON_PEN +
      DRAW_BUTTON_SAVE / 2,
    footerY + 24
  );

  // ======================================
  // EXIT
  // ======================================

  tft.setTextColor(
    TFT_RED,
    TFT_DARKGREY
  );

  tft.setTextSize(2);

  tft.drawString(
    "EXIT",
    DRAW_BUTTON_PEN +
      DRAW_BUTTON_SAVE +
      DRAW_BUTTON_EXIT / 2,
    footerY + 24
  );

  tft.setTextDatum(
    TL_DATUM
  );
}

// ========================================
// DRAW PIXEL
// ========================================

void drawPixel(
  TFT_eSPI &tft,
  int16_t x,
  int16_t y
) {

  if (
    x < 0 ||
    y < DRAW_HEADER_HEIGHT ||
    x >= tft.width() ||
    y >=
      tft.height() -
      DRAW_FOOTER_HEIGHT
  ) {

    return;
  }

  tft.fillCircle(
    x,
    y,
    2,
    TFT_CYAN
  );
}

// ========================================
// CLEAR DRAW AREA
// ========================================

void clearDrawingArea(
  TFT_eSPI &tft
) {

  int16_t width =
    tft.width();

  int16_t height =
    tft.height();

  tft.fillRect(
    1,
    DRAW_HEADER_HEIGHT + 1,
    width - 2,
    height -
      DRAW_HEADER_HEIGHT -
      DRAW_FOOTER_HEIGHT -
      2,
    TFT_BLACK
  );

  // Restore border

  tft.drawRect(
    0,
    DRAW_HEADER_HEIGHT,
    width,
    height -
      DRAW_HEADER_HEIGHT -
      DRAW_FOOTER_HEIGHT,
    TFT_DARKGREY
  );
}

// ========================================
// PEN BUTTON
// ========================================

bool isPenButton(
  TFT_eSPI &tft,
  int16_t x,
  int16_t y
) {

  int16_t footerY =
    tft.height() -
    DRAW_FOOTER_HEIGHT;

  return (
    x >= 0 &&
    x < DRAW_BUTTON_PEN &&
    y >= footerY &&
    y < tft.height()
  );
}

// ========================================
// SAVE BUTTON
// ========================================

bool isSaveButton(
  TFT_eSPI &tft,
  int16_t x,
  int16_t y
) {

  int16_t footerY =
    tft.height() -
    DRAW_FOOTER_HEIGHT;

  int16_t x1 =
    DRAW_BUTTON_PEN;

  int16_t x2 =
    DRAW_BUTTON_PEN +
    DRAW_BUTTON_SAVE;

  return (
    x >= x1 &&
    x < x2 &&
    y >= footerY &&
    y < tft.height()
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

  int16_t footerY =
    tft.height() -
    DRAW_FOOTER_HEIGHT;

  int16_t x1 =
    DRAW_BUTTON_PEN +
    DRAW_BUTTON_SAVE;

  return (
    x >= x1 &&
    x < tft.width() &&
    y >= footerY &&
    y < tft.height()
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
    x >= tft.width() - 60 &&
    x < tft.width() &&
    y >= 0 &&
    y < DRAW_HEADER_HEIGHT
  );
}

// ========================================
// SAVE FEEDBACK
// ========================================

void showSaveFeedback(
  TFT_eSPI &tft
) {

  int16_t width =
    tft.width();

  int16_t height =
    tft.height();

  int16_t boxWidth = 180;
  int16_t boxHeight = 70;

  int16_t boxX =
    (width - boxWidth) / 2;

  int16_t boxY =
    (height - boxHeight) / 2;

  tft.fillRoundRect(
    boxX,
    boxY,
    boxWidth,
    boxHeight,
    8,
    TFT_BLACK
  );

  tft.drawRoundRect(
    boxX,
    boxY,
    boxWidth,
    boxHeight,
    8,
    TFT_YELLOW
  );

  tft.setTextDatum(
    MC_DATUM
  );

  tft.setTextColor(
    TFT_YELLOW,
    TFT_BLACK
  );

  tft.setTextSize(2);

  tft.drawString(
    "SAUVEGARDE",
    width / 2,
    height / 2 - 10
  );

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.setTextSize(1);

  tft.drawString(
    "DESSIN EN MEMOIRE",
    width / 2,
    height / 2 + 15
  );

  tft.setTextDatum(
    TL_DATUM
  );

  delay(800);
}

// ========================================
// EXIT FEEDBACK
// ========================================

void showExitFeedback(
  TFT_eSPI &tft
) {

  int16_t width =
    tft.width();

  int16_t height =
    tft.height();

  tft.fillScreen(
    TFT_BLACK
  );

  tft.setTextDatum(
    MC_DATUM
  );

  tft.setTextColor(
    TFT_RED,
    TFT_BLACK
  );

  tft.setTextSize(2);

  tft.drawString(
    "EXIT",
    width / 2,
    height / 2
  );

  tft.setTextDatum(
    TL_DATUM
  );

  delay(700);
}

// ========================================
// DRAW APPLICATION
// ========================================

void testDrawing(
  TFT_eSPI &tft,
  XPT2046_Touchscreen &touch,
  TouchCalibration &cal
) {

  Serial.println();
  Serial.println(
    "================================"
  );

  Serial.println(
    "DRAW APPLICATION"
  );

  Serial.println(
    "================================"
  );

  Serial.println(
    "PEN         : dessin"
  );

  Serial.println(
    "SAUVEGARDER : sauvegarde"
  );

  Serial.println(
    "EXIT        : quitter"
  );

  Serial.println(
    "CLEAR       : effacer"
  );

  Serial.println();

  drawDrawingUI(
    tft
  );

  int16_t lastX = -1;
  int16_t lastY = -1;

  bool drawing =
    false;

  while (true) {

    if (
      touch.touched()
    ) {

      // ==================================
      // READ TOUCH
      // ==================================

      TS_Point p =
        touch.getPoint();

      int16_t screenX;
      int16_t screenY;

      // ==================================
      // CORRECTION
      //
      // convertTouch() attend:
      // rawX, rawY
      //
      // On lui transmet donc:
      // p.x, p.y
      // ==================================

      convertTouch(
        tft,
        cal,
        p.x,
        p.y,
        screenX,
        screenY
      );

      // ==================================
      // SERIAL DEBUG
      // ==================================

      Serial.print(
        "RAW X="
      );

      Serial.print(
        p.x
      );

      Serial.print(
        " RAW Y="
      );

      Serial.print(
        p.y
      );

      Serial.print(
        " Z="
      );

      Serial.print(
        p.z
      );

      Serial.print(
        " -> SCREEN X="
      );

      Serial.print(
        screenX
      );

      Serial.print(
        " Y="
      );

      Serial.println(
        screenY
      );

      // ==================================
      // CLEAR
      // ==================================

      if (
        isClearButton(
          tft,
          screenX,
          screenY
        )
      ) {

        Serial.println(
          "CLEAR DRAWING"
        );

        clearDrawingArea(
          tft
        );

        drawing =
          false;

        lastX =
          -1;

        lastY =
          -1;

        delay(150);

        while (
          touch.touched()
        ) {

          delay(10);
        }

        delay(150);

        continue;
      }

      // ==================================
      // FOOTER
      // ==================================

      if (
        screenY >=
        tft.height() -
        DRAW_FOOTER_HEIGHT
      ) {

        // ==================================
        // PEN
        // ==================================

        if (
          isPenButton(
            tft,
            screenX,
            screenY
          )
        ) {

          Serial.println(
            "PEN MODE"
          );

          drawing =
            true;

          lastX =
            -1;

          lastY =
            -1;

        }

        // ==================================
        // SAVE
        // ==================================

        else if (
          isSaveButton(
            tft,
            screenX,
            screenY
          )
        ) {

          Serial.println(
            "SAVE DRAW"
          );

          showSaveFeedback(
            tft
          );

          lastX =
            -1;

          lastY =
            -1;
        }

        // ==================================
        // EXIT
        // ==================================

        else if (
          isExitButton(
            tft,
            screenX,
            screenY
          )
        ) {

          Serial.println(
            "EXIT DRAW APPLICATION"
          );

          showExitFeedback(
            tft
          );

          return;
        }

        delay(150);

        while (
          touch.touched()
        ) {

          delay(10);
        }

        delay(150);

        continue;
      }

      // ==================================
      // DRAWING
      // ==================================

      if (
        drawing
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
            TFT_CYAN
          );

        } else {

          tft.fillCircle(
            screenX,
            screenY,
            2,
            TFT_CYAN
          );
        }

        lastX =
          screenX;

        lastY =
          screenY;
      }

      delay(10);

    } else {

      lastX =
        -1;

      lastY =
        -1;

      delay(5);
    }
  }
}

#endif