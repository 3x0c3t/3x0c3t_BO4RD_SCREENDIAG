#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#include "TFT_Config.h"
#include "SplashScreen.h"
#include "ScreenDiag.h"
#include "DrawingTest.h"

// ========================================
// TFT
// ========================================

TFT_eSPI tft = TFT_eSPI();

// ========================================
// XPT2046
// ========================================

XPT2046_Touchscreen touch(
  SCREEN_DIAG_TOUCH_CS,
  SCREEN_DIAG_TOUCH_IRQ
);

// ========================================
// CALIBRATION
// ========================================

TouchCalibration touchCalibration;

// ========================================
// SETUP
// ========================================

void setup() {

  Serial.begin(115200);

  delay(100);

  Serial.println();
  Serial.println();

  Serial.println("================================");
  Serial.println("  3x0c3t BO4RD SCREEN DIAG");
  Serial.println("================================");

  // ======================================
  // TFT
  // ======================================

  Serial.println("[1] TFT init");

  tft.init();

  Serial.println("[2] TFT init OK");

  tft.setRotation(
    TFT_ROTATION
  );

  Serial.println("[3] TFT rotation OK");

  tft.fillScreen(
    TFT_BLACK
  );

  Serial.println("[4] TFT screen clear OK");

  Serial.println();
  Serial.println("TFT initialized");

  printScreenInfo(
    tft
  );

  // ======================================
  // XPT2046
  // ======================================

  Serial.println("Initializing XPT2046...");

  Serial.println("[5] Before touch.begin()");

  bool touchOK = touch.begin();

  Serial.println("[6] After touch.begin()");

  if (touchOK) {

    Serial.println(
      "XPT2046 initialized"
    );

  } else {

    Serial.println(
      "ERROR: XPT2046 initialization failed"
    );
  }

  Serial.println("[7] Before touch.setRotation()");

  touch.setRotation(
    TFT_ROTATION
  );

  Serial.println("[8] After touch.setRotation()");

  Serial.print("Touch CS GPIO : ");
  Serial.println(
    SCREEN_DIAG_TOUCH_CS
  );

  Serial.println("[9] CS printed");

  Serial.print("Touch IRQ GPIO : ");
  Serial.println(
    SCREEN_DIAG_TOUCH_IRQ
  );

  Serial.println("[10] IRQ printed");

  Serial.print("Touch rotation : ");
  Serial.println(
    TFT_ROTATION
  );

  Serial.println("[11] Touch configuration complete");

  // ======================================
  // SPLASH
  // ======================================

  Serial.println("[12] Before splash");

  drawSplashScreen(
    tft
  );

  Serial.println("[13] Splash complete");

  // ======================================
  // SCREEN TEST
  // ======================================

  Serial.println("[14] Before screen test");

  testScreen(
    tft
  );

  Serial.println("[15] Screen test complete");

  testColorBars(
    tft
  );

  Serial.println("[16] Color test complete");

  testGeometry(
    tft
  );

  Serial.println("[17] Geometry test complete");

  // ======================================
  // CALIBRATION
  // ======================================

  Serial.println("[18] Before calibration");

  bool calibrationOK =
    calibrateTouch(
      tft,
      touch,
      touchCalibration
    );

  Serial.println("[19] Calibration returned");

  // ======================================
  // TOUCH TEST
  // ======================================

  if (calibrationOK) {

    Serial.println();
    Serial.println("================================");
    Serial.println("CALIBRATION OK");
    Serial.println("================================");

    Serial.println("[20] Before touch test");

    testTouch(
      tft,
      touch,
      touchCalibration
    );

    Serial.println("[21] Touch test complete");

    delay(1000);

    // ====================================
    // DRAW TEST
    // ====================================

    Serial.println("[22] Before drawing test");

    testDrawing(
      tft,
      touch,
      touchCalibration
    );

    Serial.println("[23] Drawing test returned");

  } else {

    Serial.println();
    Serial.println("================================");
    Serial.println("CALIBRATION FAILED");
    Serial.println("================================");

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
      "TOUCH ERROR",
      tft.width() / 2,
      tft.height() / 2
    );

    tft.setTextDatum(
      TL_DATUM
    );
  }
}

// ========================================
// LOOP
// ========================================

void loop() {

  delay(1000);
}