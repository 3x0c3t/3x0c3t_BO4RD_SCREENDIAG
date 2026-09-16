#ifndef SCREEN_DIAG_H
#define SCREEN_DIAG_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

// ========================================
// TOUCH CALIBRATION
// ========================================

struct TouchCalibration {

  int16_t rawLeft;
  int16_t rawRight;
  int16_t rawTop;
  int16_t rawBottom;

};

// ========================================
// SCREEN INFORMATION
// ========================================

void printScreenInfo(TFT_eSPI &tft) {

  Serial.println();

  Serial.print("Rotation : ");
  Serial.println(TFT_ROTATION);

  Serial.print("Width    : ");
  Serial.println(tft.width());

  Serial.print("Height   : ");
  Serial.println(tft.height());

  Serial.println();
}

// ========================================
// BASIC SCREEN TEST
// ========================================

void testScreen(TFT_eSPI &tft) {

  Serial.println("TEST ECRAN");

  tft.fillScreen(TFT_BLACK);
  delay(500);

  tft.fillScreen(TFT_RED);
  delay(500);

  tft.fillScreen(TFT_GREEN);
  delay(500);

  tft.fillScreen(TFT_BLUE);
  delay(500);

  tft.fillScreen(TFT_BLACK);

  Serial.println("Screen diagnostic complete");
  Serial.println();
}

// ========================================
// COLOR BARS
// ========================================

void testColorBars(TFT_eSPI &tft) {

  Serial.println("TEST COULEURS");

  int16_t width = tft.width();
  int16_t height = tft.height();

  int16_t barHeight = height / 6;

  tft.fillRect(
    0,
    0,
    width,
    barHeight,
    TFT_RED
  );

  tft.fillRect(
    0,
    barHeight,
    width,
    barHeight,
    TFT_GREEN
  );

  tft.fillRect(
    0,
    barHeight * 2,
    width,
    barHeight,
    TFT_BLUE
  );

  tft.fillRect(
    0,
    barHeight * 3,
    width,
    barHeight,
    TFT_CYAN
  );

  tft.fillRect(
    0,
    barHeight * 4,
    width,
    barHeight,
    TFT_MAGENTA
  );

  tft.fillRect(
    0,
    barHeight * 5,
    width,
    height - (barHeight * 5),
    TFT_YELLOW
  );

  delay(1500);

  tft.fillScreen(TFT_BLACK);
}

// ========================================
// GEOMETRY TEST
// ========================================

void testGeometry(TFT_eSPI &tft) {

  Serial.println("TEST GEOMETRIE");

  int16_t width = tft.width();
  int16_t height = tft.height();

  tft.fillScreen(TFT_BLACK);

  tft.drawRect(
    0,
    0,
    width,
    height,
    TFT_WHITE
  );

  tft.drawLine(
    0,
    0,
    width - 1,
    height - 1,
    TFT_RED
  );

  tft.drawLine(
    width - 1,
    0,
    0,
    height - 1,
    TFT_GREEN
  );

  tft.drawCircle(
    width / 2,
    height / 2,
    min(width, height) / 4,
    TFT_CYAN
  );

  tft.setTextDatum(MC_DATUM);

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.setTextSize(2);

  tft.drawString(
    "GEOMETRY",
    width / 2,
    height / 2
  );

  tft.setTextDatum(TL_DATUM);

  delay(1500);

  tft.fillScreen(TFT_BLACK);
}

// ========================================
// CALIBRATION POINT
// ========================================

void drawCalibrationPoint(
  TFT_eSPI &tft,
  int16_t x,
  int16_t y
) {

  tft.fillScreen(TFT_BLACK);

  tft.drawLine(
    x - 12,
    y,
    x + 12,
    y,
    TFT_WHITE
  );

  tft.drawLine(
    x,
    y - 12,
    x,
    y + 12,
    TFT_WHITE
  );

  tft.drawCircle(
    x,
    y,
    6,
    TFT_RED
  );

  tft.fillCircle(
    x,
    y,
    2,
    TFT_YELLOW
  );
}

// ========================================
// WAIT FOR TOUCH
// ========================================

bool waitForTouch(
  XPT2046_Touchscreen &touch,
  int16_t &rawX,
  int16_t &rawY
) {

  unsigned long startTime = millis();

  while (millis() - startTime < 15000) {

    if (touch.touched()) {

      TS_Point p = touch.getPoint();

      rawX = p.x;
      rawY = p.y;

      Serial.print("RAW X=");
      Serial.print(rawX);

      Serial.print(" RAW Y=");
      Serial.print(rawY);

      Serial.print(" Z=");
      Serial.println(p.z);

      delay(300);

      while (touch.touched()) {
        delay(20);
      }

      delay(300);

      return true;
    }

    delay(10);
  }

  return false;
}

// ========================================
// TOUCH CALIBRATION
// ========================================

bool calibrateTouch(
  TFT_eSPI &tft,
  XPT2046_Touchscreen &touch,
  TouchCalibration &cal
) {

  Serial.println();
  Serial.println("==============================");
  Serial.println("TACTILE CALIBRATION");
  Serial.println("==============================");

  Serial.print("Rotation TFT   : ");
  Serial.println(TFT_ROTATION);

  Serial.print("Rotation TOUCH : ");
  Serial.println(TFT_ROTATION);

  Serial.println();
  Serial.println("Calibration en 4 points.");
  Serial.println();

  int16_t width = tft.width();
  int16_t height = tft.height();

  const int16_t margin = 20;

  int16_t pointsX[4] = {
    margin,
    width - margin,
    width - margin,
    margin
  };

  int16_t pointsY[4] = {
    margin,
    margin,
    height - margin,
    height - margin
  };

  int16_t rawX[4];
  int16_t rawY[4];

  for (uint8_t i = 0; i < 4; i++) {

    Serial.print("Point ");
    Serial.print(i + 1);
    Serial.println("/4");

    drawCalibrationPoint(
      tft,
      pointsX[i],
      pointsY[i]
    );

    Serial.print("Touchez le point : ");
    Serial.print(pointsX[i]);
    Serial.print(" , ");
    Serial.println(pointsY[i]);

    if (!waitForTouch(
      touch,
      rawX[i],
      rawY[i]
    )) {

      Serial.println();
      Serial.println("Timeout calibration.");

      return false;
    }

    Serial.println();
  }

  cal.rawLeft =
    ((int32_t)rawX[0] + rawX[3]) / 2;

  cal.rawRight =
    ((int32_t)rawX[1] + rawX[2]) / 2;

  cal.rawTop =
    ((int32_t)rawY[0] + rawY[1]) / 2;

  cal.rawBottom =
    ((int32_t)rawY[2] + rawY[3]) / 2;

  Serial.println();
  Serial.println("CALIBRATION RAW VALUES");

  Serial.print("rawLeft   : ");
  Serial.println(cal.rawLeft);

  Serial.print("rawRight  : ");
  Serial.println(cal.rawRight);

  Serial.print("rawTop    : ");
  Serial.println(cal.rawTop);

  Serial.print("rawBottom : ");
  Serial.println(cal.rawBottom);

  Serial.println();

  tft.fillScreen(TFT_BLACK);

  return true;
}

// ========================================
// TOUCH TEST
// ========================================

void testTouch(
  TFT_eSPI &tft,
  XPT2046_Touchscreen &touch,
  TouchCalibration &cal
) {

  Serial.println();
  Serial.println("==============================");
  Serial.println("TACTILE TEST");
  Serial.println("==============================");

  Serial.println("Touchez l'ecran.");
  Serial.println("Ctrl+C / reset pour terminer.");
  Serial.println();

  tft.fillScreen(TFT_BLACK);

  // ======================================
  // TITLE
  // ======================================

  tft.setTextDatum(TC_DATUM);

  tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
  );

  tft.setTextSize(2);

  tft.drawString(
    "TOUCH TEST",
    tft.width() / 2,
    8
  );

  // ======================================
  // INITIAL COORDINATES
  // ======================================

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.drawString(
    "X: ---",
    tft.width() / 2,
    42
  );

  tft.drawString(
    "Y: ---",
    tft.width() / 2,
    68
  );

  tft.setTextDatum(TL_DATUM);

  // ======================================
  // TOUCH LOOP
  // ======================================

  while (true) {

    if (touch.touched()) {

      TS_Point p = touch.getPoint();

      int32_t screenX;
      int32_t screenY;

      // ====================================
      // CONVERT X
      // ====================================

      if (cal.rawRight != cal.rawLeft) {

        screenX = map(
          p.x,
          cal.rawLeft,
          cal.rawRight,
          0,
          tft.width() - 1
        );

      } else {

        screenX =
          tft.width() / 2;
      }

      // ====================================
      // CONVERT Y
      // ====================================

      if (cal.rawBottom != cal.rawTop) {

        screenY = map(
          p.y,
          cal.rawTop,
          cal.rawBottom,
          0,
          tft.height() - 1
        );

      } else {

        screenY =
          tft.height() / 2;
      }

      // ====================================
      // LIMIT
      // ====================================

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

      // ====================================
      // SERIAL
      // ====================================

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

      // ====================================
      // DISPLAY X
      // ====================================

      tft.setTextDatum(TC_DATUM);

      tft.fillRect(
        0,
        38,
        tft.width(),
        25,
        TFT_BLACK
      );

      tft.setTextColor(
        TFT_WHITE,
        TFT_BLACK
      );

      tft.drawString(
        "X: " + String(screenX),
        tft.width() / 2,
        42
      );

      // ====================================
      // DISPLAY Y
      // ====================================

      tft.fillRect(
        0,
        64,
        tft.width(),
        25,
        TFT_BLACK
      );

      tft.drawString(
        "Y: " + String(screenY),
        tft.width() / 2,
        68
      );

      tft.setTextDatum(TL_DATUM);

      // ====================================
      // TOUCH POINT
      // ====================================

      tft.fillCircle(
        screenX,
        screenY,
        5,
        TFT_RED
      );

      delay(100);
    }

    delay(10);
  }
}

#endif