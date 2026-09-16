#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#include "TFT_Config.h"
#include "SplashScreen.h"
#include "ScreenDiag.h"

// ============================================================
// TFT
// ============================================================

TFT_eSPI tft = TFT_eSPI();

// ============================================================
// TOUCH XPT2046
// ============================================================

XPT2046_Touchscreen touch(
  SCREEN_DIAG_TOUCH_CS,
  SCREEN_DIAG_TOUCH_IRQ
);

// ============================================================
// CALIBRATION
// ============================================================

TouchCalibration touchCalibration;

// ============================================================
// SETUP
// ============================================================

void setup() {

  Serial.begin(115200);

  delay(100);

  Serial.println();
  Serial.println();
  Serial.println("================================");
  Serial.println("  3x0c3t BO4RD SCREEN DIAG");
  Serial.println("================================");

  // ----------------------------------------------------------
  // TFT
  // ----------------------------------------------------------

  tft.init();

  tft.setRotation(TFT_ROTATION);

  tft.fillScreen(TFT_BLACK);

  Serial.println();
  Serial.println("TFT initialized");

  // ----------------------------------------------------------
  // INFORMATIONS
  // ----------------------------------------------------------

  printScreenInfo(tft);

  // ----------------------------------------------------------
  // TOUCH
  // ----------------------------------------------------------

  Serial.println("Initializing XPT2046...");

  if (touch.begin()) {

    Serial.println("XPT2046 initialized");

  } else {

    Serial.println("ERROR: XPT2046 initialization failed");
  }

  touch.setRotation(TFT_ROTATION);

  Serial.print("Touch CS  : D3");
  Serial.println();

  Serial.print("Touch IRQ : D1");
  Serial.println();

  Serial.print("Touch rotation : ");
  Serial.println(TFT_ROTATION);

  // ----------------------------------------------------------
  // SPLASH
  // ----------------------------------------------------------

  drawSplashScreen(tft);

  // ----------------------------------------------------------
  // TEST ECRAN
  // ----------------------------------------------------------

  testScreen(tft);

  // ----------------------------------------------------------
  // BARRES
  // ----------------------------------------------------------

  testColorBars(tft);

  // ----------------------------------------------------------
  // GEOMETRIE
  // ----------------------------------------------------------

  testGeometry(tft);

  // ----------------------------------------------------------
  // CALIBRATION
  // ----------------------------------------------------------

  bool calibrationOK = calibrateTouch(
    tft,
    touch,
    touchCalibration
  );

  // ----------------------------------------------------------
  // RESULTAT
  // ----------------------------------------------------------

  if (calibrationOK) {

    Serial.println();
    Serial.println("================================");
    Serial.println("CALIBRATION OK");
    Serial.println("================================");

    testTouch(
      tft,
      touch,
      touchCalibration
    );

  } else {

    Serial.println();
    Serial.println("================================");
    Serial.println("CALIBRATION FAILED");
    Serial.println("================================");

    tft.fillScreen(TFT_BLACK);

    tft.setTextDatum(MC_DATUM);

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

    tft.setTextDatum(TL_DATUM);
  }
}


// ============================================================
// LOOP
// ============================================================

void loop() {

  delay(1000);
}