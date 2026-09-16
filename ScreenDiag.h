#ifndef SCREEN_DIAG_H
#define SCREEN_DIAG_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

// ============================================================
// STRUCTURE CALIBRATION
// ============================================================

struct TouchCalibration {
  int16_t rawLeft;
  int16_t rawRight;
  int16_t rawTop;
  int16_t rawBottom;
};

// ============================================================
// INFORMATIONS ECRAN
// ============================================================

void printScreenInfo(TFT_eSPI &tft) {

  Serial.println();
  Serial.println("--------------------------------");
  Serial.println("TFT INFORMATION");
  Serial.println("--------------------------------");

  Serial.print("Rotation : ");
  Serial.println(TFT_ROTATION);

  Serial.print("Width    : ");
  Serial.println(tft.width());

  Serial.print("Height   : ");
  Serial.println(tft.height());

  Serial.println("--------------------------------");
}


// ============================================================
// TEST ECRAN
// ============================================================

void testScreen(TFT_eSPI &tft) {

  int16_t w = tft.width();
  int16_t h = tft.height();

  Serial.println();
  Serial.println("TEST COULEURS");

  tft.fillScreen(TFT_BLACK);
  delay(400);

  tft.fillScreen(TFT_RED);
  delay(400);

  tft.fillScreen(TFT_GREEN);
  delay(400);

  tft.fillScreen(TFT_BLUE);
  delay(400);

  tft.fillScreen(TFT_WHITE);
  delay(400);

  // ----------------------------------------------------------
  // GRILLE
  // ----------------------------------------------------------

  tft.fillScreen(TFT_BLACK);

  for (int16_t x = 0; x < w; x += 10) {
    tft.drawFastVLine(
      x,
      0,
      h,
      TFT_DARKGREY
    );
  }

  for (int16_t y = 0; y < h; y += 10) {
    tft.drawFastHLine(
      0,
      y,
      w,
      TFT_DARKGREY
    );
  }

  // ----------------------------------------------------------
  // BORDURE
  // ----------------------------------------------------------

  tft.drawRect(
    0,
    0,
    w,
    h,
    TFT_CYAN
  );

  // ----------------------------------------------------------
  // CROIX CENTRALE
  // ----------------------------------------------------------

  tft.drawFastVLine(
    w / 2,
    0,
    h,
    TFT_RED
  );

  tft.drawFastHLine(
    0,
    h / 2,
    w,
    TFT_RED
  );

  // ----------------------------------------------------------
  // COINS
  // ----------------------------------------------------------

  tft.fillCircle(10, 10, 5, TFT_RED);
  tft.fillCircle(w - 10, 10, 5, TFT_GREEN);
  tft.fillCircle(10, h - 10, 5, TFT_BLUE);
  tft.fillCircle(w - 10, h - 10, 5, TFT_YELLOW);

  // ----------------------------------------------------------
  // TEXTE
  // ----------------------------------------------------------

  tft.setTextDatum(MC_DATUM);

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.setTextSize(2);

  tft.drawString(
    "SCREEN DIAGNOSTIC",
    w / 2,
    h / 2 - 25
  );

  tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
  );

  tft.drawString(
    String(w) + " x " + String(h),
    w / 2,
    h / 2 + 5
  );

  tft.setTextColor(
    TFT_GREEN,
    TFT_BLACK
  );

  tft.drawString(
    "ROTATION " + String(TFT_ROTATION),
    w / 2,
    h / 2 + 35
  );

  tft.setTextDatum(TL_DATUM);
}


// ============================================================
// BARRES COULEURS
// ============================================================

void testColorBars(TFT_eSPI &tft) {

  int16_t w = tft.width();
  int16_t h = tft.height();

  int16_t barHeight = h / 8;

  uint16_t colors[] = {
    TFT_RED,
    TFT_GREEN,
    TFT_BLUE,
    TFT_YELLOW,
    TFT_CYAN,
    TFT_MAGENTA,
    TFT_WHITE,
    TFT_BLACK
  };

  Serial.println("TEST BARRES COULEURS");

  for (uint8_t i = 0; i < 8; i++) {

    tft.fillRect(
      0,
      i * barHeight,
      w,
      barHeight,
      colors[i]
    );
  }

  delay(1200);
}


// ============================================================
// TEST GEOMETRIE
// ============================================================

void testGeometry(TFT_eSPI &tft) {

  int16_t w = tft.width();
  int16_t h = tft.height();

  Serial.println("TEST GEOMETRIE");

  tft.fillScreen(TFT_BLACK);

  tft.drawRect(
    0,
    0,
    w,
    h,
    TFT_WHITE
  );

  tft.drawLine(
    0,
    0,
    w - 1,
    h - 1,
    TFT_RED
  );

  tft.drawLine(
    w - 1,
    0,
    0,
    h - 1,
    TFT_GREEN
  );

  tft.drawCircle(
    w / 2,
    h / 2,
    50,
    TFT_CYAN
  );

  tft.drawRect(
    w / 2 - 60,
    h / 2 - 40,
    120,
    80,
    TFT_YELLOW
  );

  delay(1200);
}


// ============================================================
// POINT CALIBRATION
// ============================================================

void drawCalibrationPoint(
  TFT_eSPI &tft,
  int16_t x,
  int16_t y
) {

  tft.fillScreen(TFT_BLACK);

  // Croix blanche
  tft.drawFastHLine(
    x - 15,
    y,
    30,
    TFT_WHITE
  );

  tft.drawFastVLine(
    x,
    y - 15,
    30,
    TFT_WHITE
  );

  // Cercle rouge
  tft.drawCircle(
    x,
    y,
    8,
    TFT_RED
  );

  // Centre jaune
  tft.fillCircle(
    x,
    y,
    2,
    TFT_YELLOW
  );

  tft.setTextDatum(MC_DATUM);

  tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
  );

  tft.setTextSize(1);

  tft.drawString(
    "TOUCH THE CROSS",
    tft.width() / 2,
    tft.height() / 2
  );

  tft.setTextDatum(TL_DATUM);
}


// ============================================================
// ATTENTE TOUCH
// ============================================================

bool waitForTouch(
  XPT2046_Touchscreen &touch,
  int16_t &rawX,
  int16_t &rawY
) {

  unsigned long startTime = millis();

  while (millis() - startTime < 15000UL) {

    if (touch.touched()) {

      TS_Point point = touch.getPoint();

      rawX = point.x;
      rawY = point.y;

      Serial.print("RAW X = ");
      Serial.println(rawX);

      Serial.print("RAW Y = ");
      Serial.println(rawY);

      // Attendre relâchement
      while (touch.touched()) {
        delay(10);
      }

      delay(250);

      return true;
    }

    delay(10);
  }

  return false;
}


// ============================================================
// CALIBRATION
// ============================================================

bool calibrateTouch(
  TFT_eSPI &tft,
  XPT2046_Touchscreen &touch,
  TouchCalibration &cal
) {

  Serial.println();
  Serial.println("================================");
  Serial.println("TACTILE CALIBRATION");
  Serial.println("================================");

  Serial.print("Rotation TFT   : ");
  Serial.println(TFT_ROTATION);

  Serial.print("Rotation TOUCH : ");
  Serial.println(TFT_ROTATION);

  Serial.println();
  Serial.println("Calibration en 4 points.");

  const int16_t marginX = 20;
  const int16_t marginY = 20;

  const int16_t pointX[4] = {
    marginX,
    tft.width() - marginX,
    tft.width() - marginX,
    marginX
  };

  const int16_t pointY[4] = {
    marginY,
    marginY,
    tft.height() - marginY,
    tft.height() - marginY
  };

  int16_t rawX[4];
  int16_t rawY[4];

  const char *names[4] = {
    "TOP LEFT",
    "TOP RIGHT",
    "BOTTOM RIGHT",
    "BOTTOM LEFT"
  };

  for (uint8_t i = 0; i < 4; i++) {

    Serial.println();
    Serial.print("POINT ");
    Serial.print(i + 1);
    Serial.print(" : ");
    Serial.println(names[i]);

    drawCalibrationPoint(
      tft,
      pointX[i],
      pointY[i]
    );

    Serial.println("Touch the cross...");

    if (!waitForTouch(
      touch,
      rawX[i],
      rawY[i]
    )) {

      Serial.println("TIMEOUT");

      return false;
    }

    delay(400);
  }

  // ----------------------------------------------------------
  // CALCUL
  // ----------------------------------------------------------

  cal.rawLeft =
    (rawX[0] + rawX[3]) / 2;

  cal.rawRight =
    (rawX[1] + rawX[2]) / 2;

  cal.rawTop =
    (rawY[0] + rawY[1]) / 2;

  cal.rawBottom =
    (rawY[2] + rawY[3]) / 2;

  // ----------------------------------------------------------
  // RESULTATS
  // ----------------------------------------------------------

  Serial.println();
  Serial.println("--------------------------------");
  Serial.println("CALIBRATION RESULTS");
  Serial.println("--------------------------------");

  Serial.print("Raw Left   : ");
  Serial.println(cal.rawLeft);

  Serial.print("Raw Right  : ");
  Serial.println(cal.rawRight);

  Serial.print("Raw Top    : ");
  Serial.println(cal.rawTop);

  Serial.print("Raw Bottom : ");
  Serial.println(cal.rawBottom);

  Serial.println("--------------------------------");

  if (abs(cal.rawRight - cal.rawLeft) < 100) {
    Serial.println("WARNING: X RANGE TOO SMALL");
  }

  if (abs(cal.rawBottom - cal.rawTop) < 100) {
    Serial.println("WARNING: Y RANGE TOO SMALL");
  }

  Serial.println("Calibration complete.");

  return true;
}


// ============================================================
// TEST TACTILE
// ============================================================

void testTouch(
  TFT_eSPI &tft,
  XPT2046_Touchscreen &touch,
  TouchCalibration &cal
) {

  Serial.println();
  Serial.println("================================");
  Serial.println("TACTILE TEST");
  Serial.println("================================");

  Serial.println("Touch the screen.");
  Serial.println("Press RESET to restart.");

  tft.fillScreen(TFT_BLACK);

  tft.setTextDatum(MC_DATUM);

  tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
  );

  tft.setTextSize(2);

  tft.drawString(
    "TOUCH TEST",
    tft.width() / 2,
    25
  );

  tft.setTextSize(1);

  tft.drawString(
    "Touch anywhere",
    tft.width() / 2,
    45
  );

  tft.setTextDatum(TL_DATUM);

  while (true) {

    if (touch.touched()) {

      TS_Point point = touch.getPoint();

      int16_t rawX = point.x;
      int16_t rawY = point.y;

      int32_t screenX = map(
        rawX,
        cal.rawLeft,
        cal.rawRight,
        0,
        tft.width() - 1
      );

      int32_t screenY = map(
        rawY,
        cal.rawTop,
        cal.rawBottom,
        0,
        tft.height() - 1
      );

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

      // ------------------------------------------------------
      // SERIAL
      // ------------------------------------------------------

      Serial.print("RAW X=");
      Serial.print(rawX);

      Serial.print(" RAW Y=");
      Serial.print(rawY);

      Serial.print(" -> SCREEN X=");
      Serial.print(screenX);

      Serial.print(" Y=");
      Serial.println(screenY);

      // ------------------------------------------------------
      // ECRAN
      // ------------------------------------------------------

      tft.fillScreen(TFT_BLACK);

      tft.drawCircle(
        screenX,
        screenY,
        12,
        TFT_CYAN
      );

      tft.fillCircle(
        screenX,
        screenY,
        4,
        TFT_RED
      );

      tft.setTextDatum(MC_DATUM);

      tft.setTextColor(
        TFT_WHITE,
        TFT_BLACK
      );

      tft.setTextSize(2);

      tft.drawString(
        "X: " + String(screenX),
        tft.width() / 2,
        tft.height() / 2 - 25
      );

      tft.drawString(
        "Y: " + String(screenY),
        tft.width() / 2,
        tft.height() / 2 + 5
      );

      tft.setTextDatum(TL_DATUM);

      while (touch.touched()) {
        delay(10);
      }

      delay(50);
    }

    delay(10);
  }
}

#endif