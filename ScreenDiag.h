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

void printScreenInfo(
  TFT_eSPI &tft
) {

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

void testScreen(
  TFT_eSPI &tft
) {

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

  Serial.println(
    "Screen diagnostic complete"
  );

  Serial.println();
}

// ========================================
// COLOR BARS
// ========================================

void testColorBars(
  TFT_eSPI &tft
) {

  Serial.println("TEST COULEURS");

  int16_t width =
    tft.width();

  int16_t height =
    tft.height();

  int16_t barHeight =
    height / 6;

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

void testGeometry(
  TFT_eSPI &tft
) {

  Serial.println("TEST GEOMETRIE");

  int16_t width =
    tft.width();

  int16_t height =
    tft.height();

  tft.fillScreen(
    TFT_BLACK
  );

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

  tft.setTextDatum(
    MC_DATUM
  );

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

  tft.setTextDatum(
    TL_DATUM
  );

  delay(1500);

  tft.fillScreen(
    TFT_BLACK
  );
}

// ========================================
// CALIBRATION TARGET
// ========================================

void drawCalibrationTarget(
  TFT_eSPI &tft,
  int16_t x,
  int16_t y,
  uint8_t pointNumber
) {

  int16_t width =
    tft.width();

  int16_t height =
    tft.height();

  tft.fillScreen(
    TFT_BLACK
  );

  // ======================================
  // TITLE
  // ======================================

  tft.setTextDatum(
    TC_DATUM
  );

  tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
  );

  tft.setTextSize(2);

  tft.drawString(
    "TOUCH 4 POINTS",
    width / 2,
    8
  );

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.drawString(
    String(pointNumber) + " / 4",
    width / 2,
    34
  );

  // ======================================
  // TARGET
  // ======================================

  tft.drawLine(
    x - 15,
    y,
    x + 15,
    y,
    TFT_WHITE
  );

  tft.drawLine(
    x,
    y - 15,
    x,
    y + 15,
    TFT_WHITE
  );

  tft.drawCircle(
    x,
    y,
    8,
    TFT_RED
  );

  tft.fillCircle(
    x,
    y,
    3,
    TFT_YELLOW
  );

  // ======================================
  // REQUESTED COORDINATES
  // ======================================

  tft.setTextColor(
    TFT_YELLOW,
    TFT_BLACK
  );

  tft.drawString(
    "DEMANDE",
    width / 2,
    height / 2 - 40
  );

  tft.drawString(
    "X: " + String(x),
    width / 2,
    height / 2 - 15
  );

  tft.drawString(
    "Y: " + String(y),
    width / 2,
    height / 2 + 10
  );

  tft.setTextDatum(
    TL_DATUM
  );
}

// ========================================
// VALIDATION RAW XPT2046
// ========================================

bool isValidRawTouch(
  const TS_Point &p
) {

  // XPT2046 nominal raw range
  if (
    p.x < 200 ||
    p.x > 3900
  ) {
    return false;
  }

  // XPT2046 nominal raw range
  if (
    p.y < 200 ||
    p.y > 3900
  ) {
    return false;
  }

  // Reject invalid / floating pressure
  if (
    p.z <= 0 ||
    p.z > 2000
  ) {
    return false;
  }

  return true;
}

// ========================================
// WAIT FOR TOUCH
// ========================================

bool waitForTouch(
  XPT2046_Touchscreen &touch,
  int16_t &rawX,
  int16_t &rawY,
  int16_t &pressure
) {

  unsigned long startTime =
    millis();

  while (
    millis() - startTime < 15000
  ) {

    if (
      touch.touched()
    ) {

      TS_Point p =
        touch.getPoint();

      // ==================================
      // ALWAYS DISPLAY RAW VALUE
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

      Serial.println(
        p.z
      );

      // ==================================
      // REJECT INVALID TOUCH
      // ==================================

      if (
        !isValidRawTouch(p)
      ) {

        Serial.println(
          "INVALID RAW TOUCH"
        );

        delay(20);

        continue;
      }

      // ==================================
      // VALID TOUCH ONLY
      // ==================================

      rawX =
        p.x;

      rawY =
        p.y;

      pressure =
        p.z;

      Serial.println(
        "VALID RAW TOUCH"
      );

      delay(300);

      while (
        touch.touched()
      ) {

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
// TOUCH CONVERSION
// ========================================

void convertTouch(
  TFT_eSPI &tft,
  TouchCalibration &cal,
  int16_t rawX,
  int16_t rawY,
  int16_t &screenX,
  int16_t &screenY
) {

  if (
    cal.rawRight !=
    cal.rawLeft
  ) {

    screenX =
      map(
        rawX,
        cal.rawLeft,
        cal.rawRight,
        0,
        tft.width() - 1
      );

  } else {

    screenX =
      tft.width() / 2;
  }

  if (
    cal.rawBottom !=
    cal.rawTop
  ) {

    screenY =
      map(
        rawY,
        cal.rawTop,
        cal.rawBottom,
        0,
        tft.height() - 1
      );

  } else {

    screenY =
      tft.height() / 2;
  }

  screenX =
    constrain(
      screenX,
      0,
      tft.width() - 1
    );

  screenY =
    constrain(
      screenY,
      0,
      tft.height() - 1
    );
}

// ========================================
// TOUCH CALIBRATION
// ========================================

bool calibrateTouch(
  TFT_eSPI &tft,
  XPT2046_Touchscreen &touch,
  TouchCalibration &cal
) {

  int16_t width =
    tft.width();

  int16_t height =
    tft.height();

  const int16_t margin = 25;

  int16_t targetX[4] = {
    margin,
    width - margin,
    width - margin,
    margin
  };

  int16_t targetY[4] = {
    margin,
    margin,
    height - margin,
    height - margin
  };

  int16_t rawX[4];
  int16_t rawY[4];
  int16_t rawZ[4];

  Serial.println();
  Serial.println(
    "================================"
  );

  Serial.println(
    "        TOUCH 4 POINTS"
  );

  Serial.println(
    "================================"
  );

  Serial.print(
    "Rotation TFT   : "
  );

  Serial.println(
    TFT_ROTATION
  );

  Serial.print(
    "Rotation TOUCH : "
  );

  Serial.println(
    TFT_ROTATION
  );

  Serial.println();

  for (
    uint8_t i = 0;
    i < 4;
    i++
  ) {

    Serial.println(
      "--------------------------------"
    );

    Serial.print(
      "POINT "
    );

    Serial.print(
      i + 1
    );

    Serial.println(
      " / 4"
    );

    Serial.print(
      "COORDONNEE DEMANDEE : X="
    );

    Serial.print(
      targetX[i]
    );

    Serial.print(
      " Y="
    );

    Serial.println(
      targetY[i]
    );

    Serial.println(
      "Touchez la cible."
    );

    drawCalibrationTarget(
      tft,
      targetX[i],
      targetY[i],
      i + 1
    );

    if (
      !waitForTouch(
        touch,
        rawX[i],
        rawY[i],
        rawZ[i]
      )
    ) {

      Serial.println();
      Serial.println(
        "TIMEOUT CALIBRATION"
      );

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
        "CALIBRATION TIMEOUT",
        width / 2,
        height / 2
      );

      tft.setTextDatum(
        TL_DATUM
      );

      return false;
    }

    Serial.print(
      "COORDONNEE REELLE RAW : X="
    );

    Serial.print(
      rawX[i]
    );

    Serial.print(
      " Y="
    );

    Serial.println(
      rawY[i]
    );

    Serial.print(
      "PRESSION : "
    );

    Serial.println(
      rawZ[i]
    );

    delay(300);
  }

  // ======================================
  // RAW CALIBRATION VALUES
  // ======================================

  cal.rawLeft =
    (
      (int32_t)rawX[0] +
      rawX[3]
    ) / 2;

  cal.rawRight =
    (
      (int32_t)rawX[1] +
      rawX[2]
    ) / 2;

  cal.rawTop =
    (
      (int32_t)rawY[0] +
      rawY[1]
    ) / 2;

  cal.rawBottom =
    (
      (int32_t)rawY[2] +
      rawY[3]
    ) / 2;

  Serial.println();
  Serial.println(
    "================================"
  );

  Serial.println(
    "CALIBRATION RAW VALUES"
  );

  Serial.println(
    "================================"
  );

  Serial.print(
    "rawLeft   : "
  );

  Serial.println(
    cal.rawLeft
  );

  Serial.print(
    "rawRight  : "
  );

  Serial.println(
    cal.rawRight
  );

  Serial.print(
    "rawTop    : "
  );

  Serial.println(
    cal.rawTop
  );

  Serial.print(
    "rawBottom : "
  );

  Serial.println(
    cal.rawBottom
  );

  // ======================================
  // PRECISION
  // ======================================

  float precision[4];
  float totalPrecision = 0.0;

  float maxDistance =
    sqrt(
      (
        (float)(width - 1) *
        (float)(width - 1)
      )
      +
      (
        (float)(height - 1) *
        (float)(height - 1)
      )
    );

  int16_t measuredX[4];
  int16_t measuredY[4];

  float distance[4];

  for (
    uint8_t i = 0;
    i < 4;
    i++
  ) {

    convertTouch(
      tft,
      cal,
      rawX[i],
      rawY[i],
      measuredX[i],
      measuredY[i]
    );

    float dx =
      (float)measuredX[i] -
      (float)targetX[i];

    float dy =
      (float)measuredY[i] -
      (float)targetY[i];

    distance[i] =
      sqrt(
        (dx * dx) +
        (dy * dy)
      );

    precision[i] =
      100.0 -
      (
        distance[i] /
        maxDistance
      ) *
      100.0;

    precision[i] =
      constrain(
        precision[i],
        0.0,
        100.0
      );

    totalPrecision +=
      precision[i];
  }

  float finalPrecision =
    totalPrecision / 4.0;

  // ======================================
  // SERIAL REPORT
  // ======================================

  Serial.println();
  Serial.println(
    "================================"
  );

  Serial.println(
    "       BILAN TOUCH 4 POINTS"
  );

  Serial.println(
    "================================"
  );

  for (
    uint8_t i = 0;
    i < 4;
    i++
  ) {

    Serial.println();

    Serial.print(
      "POINT "
    );

    Serial.println(
      i + 1
    );

    Serial.print(
      " Demande : X="
    );

    Serial.print(
      targetX[i]
    );

    Serial.print(
      " Y="
    );

    Serial.println(
      targetY[i]
    );

    Serial.print(
      " RAW     : X="
    );

    Serial.print(
      rawX[i]
    );

    Serial.print(
      " Y="
    );

    Serial.println(
      rawY[i]
    );

    Serial.print(
      " Reel    : X="
    );

    Serial.print(
      measuredX[i]
    );

    Serial.print(
      " Y="
    );

    Serial.println(
      measuredY[i]
    );

    Serial.print(
      " Erreur  : "
    );

    Serial.print(
      distance[i],
      1
    );

    Serial.println(
      " px"
    );

    Serial.print(
      " Precision : "
    );

    Serial.print(
      precision[i],
      1
    );

    Serial.println(
      " %"
    );
  }

  Serial.println();
  Serial.println(
    "--------------------------------"
  );

  Serial.print(
    "PRECISION MOYENNE : "
  );

  Serial.print(
    finalPrecision,
    1
  );

  Serial.println(
    " %"
  );

  Serial.print(
    "BILAN : "
  );

  if (
    finalPrecision >= 95.0
  ) {

    Serial.println(
      "EXCELLENT"
    );

  } else if (
    finalPrecision >= 90.0
  ) {

    Serial.println(
      "TRES BON"
    );

  } else if (
    finalPrecision >= 80.0
  ) {

    Serial.println(
      "BON"
    );

  } else if (
    finalPrecision >= 65.0
  ) {

    Serial.println(
      "MOYEN"
    );

  } else {

    Serial.println(
      "A REVOIR"
    );
  }

  Serial.println(
    "================================"
  );

  // ======================================
  // RESULT SCREEN
  // ======================================

  tft.fillScreen(
    TFT_BLACK
  );

  tft.setTextDatum(
    TC_DATUM
  );

  tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
  );

  tft.setTextSize(2);

  tft.drawString(
    "TOUCH 4 POINTS",
    width / 2,
    8
  );

  tft.setTextSize(1);

  for (
    uint8_t i = 0;
    i < 4;
    i++
  ) {

    int16_t y =
      48 + (i * 42);

    tft.setTextColor(
      TFT_YELLOW,
      TFT_BLACK
    );

    tft.drawString(
      "P" +
      String(i + 1) +
      " D:" +
      String(targetX[i]) +
      "," +
      String(targetY[i]),
      5,
      y
    );

    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.drawString(
      "R:" +
      String(measuredX[i]) +
      "," +
      String(measuredY[i]),
      85,
      y
    );

    tft.setTextColor(
      TFT_GREEN,
      TFT_BLACK
    );

    tft.drawString(
      String(
        precision[i],
        1
      ) +
      "%",
      180,
      y
    );
  }

  tft.setTextSize(2);

  tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
  );

  tft.drawString(
    "PRECISION",
    width / 2,
    225
  );

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.drawString(
    String(
      finalPrecision,
      1
    ) +
    " %",
    width / 2,
    252
  );

  if (
    finalPrecision >= 95.0
  ) {

    tft.setTextColor(
      TFT_GREEN,
      TFT_BLACK
    );

    tft.drawString(
      "EXCELLENT",
      width / 2,
      286
    );

  } else if (
    finalPrecision >= 90.0
  ) {

    tft.setTextColor(
      TFT_GREEN,
      TFT_BLACK
    );

    tft.drawString(
      "TRES BON",
      width / 2,
      286
    );

  } else if (
    finalPrecision >= 80.0
  ) {

    tft.setTextColor(
      TFT_YELLOW,
      TFT_BLACK
    );

    tft.drawString(
      "BON",
      width / 2,
      286
    );

  } else if (
    finalPrecision >= 65.0
  ) {

    tft.setTextColor(
      TFT_ORANGE,
      TFT_BLACK
    );

    tft.drawString(
      "MOYEN",
      width / 2,
      286
    );

  } else {

    tft.setTextColor(
      TFT_RED,
      TFT_BLACK
    );

    tft.drawString(
      "A REVOIR",
      width / 2,
      286
    );
  }

  tft.setTextDatum(
    TL_DATUM
  );

  delay(2500);

  tft.fillScreen(
    TFT_BLACK
  );

  return true;
}

// ========================================
// DRAW MODE BUTTON
// ========================================

const int16_t TOUCH_TEST_BUTTON_HEIGHT =
  52;

bool isDrawButtonPressed(
  TFT_eSPI &tft,
  int16_t x,
  int16_t y
) {

  int16_t buttonY =
    tft.height() -
    TOUCH_TEST_BUTTON_HEIGHT -
    10;

  return (
    x >= 20 &&
    x <= tft.width() - 20 &&
    y >= buttonY &&
    y <=
      buttonY +
      TOUCH_TEST_BUTTON_HEIGHT
  );
}

// ========================================
// TOUCH TEST UI
// ========================================

void drawTouchTestUI(
  TFT_eSPI &tft,
  int16_t screenX,
  int16_t screenY,
  bool hasTouch
) {

  int16_t width =
    tft.width();

  int16_t height =
    tft.height();

  int16_t buttonY =
    height -
    TOUCH_TEST_BUTTON_HEIGHT -
    10;

  tft.setTextDatum(
    TC_DATUM
  );

  tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
  );

  tft.setTextSize(2);

  tft.drawString(
    "TOUCH TEST",
    width / 2,
    8
  );

  tft.fillRect(
    0,
    38,
    width,
    55,
    TFT_BLACK
  );

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  if (
    hasTouch
  ) {

    tft.drawString(
      "X: " + String(screenX),
      width / 2,
      42
    );

    tft.drawString(
      "Y: " + String(screenY),
      width / 2,
      68
    );

  } else {

    tft.drawString(
      "X: ---",
      width / 2,
      42
    );

    tft.drawString(
      "Y: ---",
      width / 2,
      68
    );
  }

  tft.fillRoundRect(
    20,
    buttonY,
    width - 40,
    TOUCH_TEST_BUTTON_HEIGHT,
    8,
    TFT_DARKGREY
  );

  tft.drawRoundRect(
    20,
    buttonY,
    width - 40,
    TOUCH_TEST_BUTTON_HEIGHT,
    8,
    TFT_CYAN
  );

  tft.setTextColor(
    TFT_CYAN,
    TFT_DARKGREY
  );

  tft.setTextSize(2);

  tft.drawString(
    "DRAW MODE",
    width / 2,
    buttonY + 26
  );

  tft.setTextDatum(
    TL_DATUM
  );
}

// ========================================
// TOUCH TEST
// ========================================

bool testTouch(
  TFT_eSPI &tft,
  XPT2046_Touchscreen &touch,
  TouchCalibration &cal
) {

  Serial.println();
  Serial.println(
    "=============================="
  );

  Serial.println(
    "TACTILE TEST"
  );

  Serial.println(
    "=============================="
  );

  Serial.println(
    "Touchez l'ecran."
  );

  Serial.println(
    "Bouton DRAW MODE pour continuer."
  );

  Serial.println();

  tft.fillScreen(
    TFT_BLACK
  );

  drawTouchTestUI(
    tft,
    0,
    0,
    false
  );

  int16_t lastX = -1;
  int16_t lastY = -1;

  while (
    true
  ) {

    if (
      touch.touched()
    ) {

      TS_Point p =
        touch.getPoint();

      // ==================================
      // RAW VALIDATION
      // ==================================

      if (
        !isValidRawTouch(p)
      ) {

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

        Serial.println(
          " -> INVALID RAW TOUCH"
        );

        delay(20);

        continue;
      }

      int16_t screenX;
      int16_t screenY;

      convertTouch(
        tft,
        cal,
        p.x,
        p.y,
        screenX,
        screenY
      );

      if (
        isDrawButtonPressed(
          tft,
          screenX,
          screenY
        )
      ) {

        Serial.println();
        Serial.println(
          "DRAW MODE SELECTED"
        );

        delay(150);

        while (
          touch.touched()
        ) {

          delay(10);
        }

        delay(150);

        tft.fillScreen(
          TFT_BLACK
        );

        return true;
      }

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

      drawTouchTestUI(
        tft,
        screenX,
        screenY,
        true
      );

      if (
        lastX >= 0 &&
        lastY >= 0
      ) {

        tft.drawLine(
          lastX,
          lastY,
          screenX,
          screenY,
          TFT_RED
        );

      } else {

        tft.fillCircle(
          screenX,
          screenY,
          5,
          TFT_RED
        );
      }

      lastX =
        screenX;

      lastY =
        screenY;

      delay(20);

    } else {

      lastX = -1;
      lastY = -1;
    }

    delay(5);
  }

  return false;
}

#endif