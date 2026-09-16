#ifndef TFT_CONFIG_H
#define TFT_CONFIG_H

// ============================================================
// 3x0c3t BO4RD - SCREEN DIAG
// Configuration générale
// ============================================================

// Rotation TFT
#define TFT_ROTATION 2

// ============================================================
// XPT2046 TOUCH
// ============================================================

// IMPORTANT :
// TFT_eSPI définit déjà TOUCH_CS dans User_Setup.h.
// Pour éviter les conflits, on utilise un nom propre au projet.

#define SCREEN_DIAG_TOUCH_CS D3
#define SCREEN_DIAG_TOUCH_IRQ D1

#endif