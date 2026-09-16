# 3x0c3t BO4RD SCREEN DIAG

Banc de diagnostic pour :

* ESP8266 NodeMCU
* TFT ILI9341 2.8"
* résolution 240 × 320
* tactile résistif XPT2046
* SPI
* `TFT_eSPI`
* `XPT2046_Touchscreen`

Le programme permet de tester l'écran, le tactile, la calibration et une interface de dessin.

---

## Matériel

```text
ESP8266 NodeMCU
      │
      ├── SPI ──────── TFT ILI9341
      │
      └── SPI ──────── XPT2046
```

### GPIO

| Fonction  |   GPIO | NodeMCU |
| --------- | -----: | ------- |
| SPI SCK   | GPIO14 | D5      |
| SPI MISO  | GPIO12 | D6      |
| SPI MOSI  | GPIO13 | D7      |
| TFT CS    | GPIO15 | D8      |
| TFT DC    |  GPIO0 | D3      |
| TFT RST   |  GPIO2 | D4      |
| Touch CS  |  GPIO4 | D2      |
| Touch IRQ |  GPIO5 | D1      |

### Configuration

```cpp
#define TFT_ROTATION 2

#define SCREEN_DIAG_TOUCH_CS  4
#define SCREEN_DIAG_TOUCH_IRQ 5
```

---

# Structure

```text
SCREENDIAG/
│
├── SCREENDIAG.ino
├── TFT_Config.h
├── SplashScreen.h
├── ScreenDiag.h
├── DrawingTest.h
└── README.md
```

---

# Fonctionnement

Le programme suit cette séquence :

```text
┌─────────────────────┐
│       BOOT          │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│   INITIALISATION    │
│   TFT + XPT2046     │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│    SPLASH SCREEN    │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│    TEST ÉCRAN       │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│   TEST COULEURS     │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│  TEST GÉOMÉTRIE     │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│ CALIBRATION TACTILE │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│     TOUCH TEST      │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│  DRAW APPLICATION   │
└─────────────────────┘
```

---

# ÉCRANS

## 01 · Splash Screen

Écran affiché au démarrage.

```text
┌────────────────────────┐
│                        │
│                        │
│        -3xØc3t-        │
│                        │
│          BO4RD         │
│       SCREEN DIAG      │
│                        │
│                        │
│   ┌────────────────┐   │
│   │████████████████│   │
│   └────────────────┘   │
│                        │
└────────────────────────┘
          240 × 320
```

---

# 02 · Test écran

Test rapide des couleurs principales.

```text
┌────────────────────────┐
│                        │
│          RED           │
│                        │
├────────────────────────┤
│                        │
│         GREEN          │
│                        │
├────────────────────────┤
│                        │
│          BLUE          │
│                        │
└────────────────────────┘
```

Puis :

```text
RED
GREEN
BLUE
CYAN
MAGENTA
YELLOW
```

Objectif :

* vérifier l'affichage ;
* vérifier les couleurs ;
* vérifier la communication SPI ;
* vérifier la rotation.

---

# 03 · Test géométrie

```text
┌────────────────────────┐
│╲                      ╱│
│ ╲                    ╱ │
│  ╲       ○          ╱  │
│   ╲     GEOMETRY   ╱   │
│    ╲              ╱    │
│     ╲            ╱     │
│      ╲          ╱      │
│       ╲        ╱       │
│        ╲      ╱        │
│         ╲    ╱         │
│          ╲  ╱          │
│           ╲╱           │
└────────────────────────┘
```

Objectif :

* vérifier les dimensions ;
* vérifier la rotation ;
* vérifier les coordonnées ;
* vérifier les diagonales ;
* vérifier le centre de l'écran.

---

# 04 · Calibration tactile

Calibration en quatre points.

```text
┌────────────────────────┐
│                        │
│   +                +   │
│                        │
│                        │
│                        │
│                        │
│                        │
│                        │
│                        │
│                        │
│   +                +   │
│                        │
└────────────────────────┘
```

Coordonnées utilisées :

```text
P1 = (25, 25)
P2 = (215, 25)
P3 = (215, 295)
P4 = (25, 295)
```

---

## Écran de calibration

Pour chaque point :

```text
┌────────────────────────┐
│    TOUCH 4 POINTS      │
│                        │
│          1 / 4         │
│                        │
│                        │
│       DEMANDE          │
│                        │
│         X: 25          │
│         Y: 25          │
│                        │
│          ⊕             │
│                        │
└────────────────────────┘
```

L'utilisateur touche la cible.

Le programme récupère :

```text
RAW X
RAW Y
RAW Z
```

---

# 05 · Rapport calibration

Après les quatre points :

```text
┌────────────────────────┐
│    TOUCH 4 POINTS      │
│                        │
│ P1 D:25,25 R:25,24 99% │
│ P2 D:215,25 R:214,25  │
│ P3 D:215,295 R:215,294│
│ P4 D:25,295 R:26,295  │
│                        │
│      PRECISION         │
│        99.4 %          │
│                        │
│       EXCELLENT        │
└────────────────────────┘
```

Le rapport indique :

```text
D = coordonnées demandées
R = coordonnées réellement obtenues
```

et la précision calculée pour chaque point.

---

# 06 · Touch Test

Test libre du tactile.

```text
┌────────────────────────┐
│      TOUCH TEST        │
│                        │
│       X: 132           │
│       Y: 228           │
│                        │
│                        │
│          ●             │
│                        │
│                        │
│                        │
│                        │
│                        │
│   ┌────────────────┐   │
│   │   DRAW MODE    │   │
│   └────────────────┘   │
└────────────────────────┘
```

Le contact est également envoyé au Moniteur Série.

Exemple :

```text
RAW X=2909 RAW Y=2145 Z=1687
-> SCREEN X=44 Y=148
```

---

# 07 · Draw Application

Application de dessin tactile.

```text
┌────────────────────────┐
│    DRAW APPLICATION    │
│                   CLEAR│
├────────────────────────┤
│                        │
│                        │
│                        │
│       ZONE DESSIN      │
│                        │
│          ╲             │
│           ╲            │
│            ●           │
│                        │
│                        │
├────────┬───────┬───────┤
│  PEN   │ SAUVE-│ EXIT  │
│        │ GARDER│       │
└────────┴───────┴───────┘
```

---

## Commandes

### PEN

Active le dessin tactile.

```text
PEN
```

Les déplacements du doigt/stylet sont tracés en cyan.

### SAUVEGARDER

Affiche :

```text
┌────────────────────────┐
│                        │
│      SAUVEGARDE        │
│                        │
│   DESSIN EN MEMOIRE    │
│                        │
└────────────────────────┘
```

La sauvegarde persistante n'est pas encore implémentée.

### CLEAR

Efface la zone de dessin.

### EXIT

Quitte l'application de dessin.

---

# Zone tactile

Le footer de l'application est divisé en trois zones :

```text
0              80             160             240
│──────────────│──────────────│──────────────│
│     PEN      │ SAUVEGARDER  │     EXIT     │
│──────────────│──────────────│──────────────│
```

Cela évite le chevauchement entre les boutons.

---

# Moniteur Série

Vitesse :

```text
115200 bauds
```

Exemple :

```text
================================
  3x0c3t BO4RD SCREEN DIAG
================================

Initializing TFT...
TFT initialized
TFT rotation OK

Rotation : 2
Width    : 240
Height   : 320

Initializing XPT2046...
XPT2046 initialized

Touch CS GPIO : 4
Touch IRQ GPIO : 5
Touch rotation : 2
```

---

# Compilation

```bash
cd ~/Arduino/0_PROJETS/Ecran\ TFT\ SPI\ 240x320/3x0c3t_BO4RD/SCREENDIAG
```

```bash
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 .
```

---

# Téléversement

```bash
arduino-cli upload \
  -p /dev/ttyUSB0 \
  --fqbn esp8266:esp8266:nodemcuv2 .
```

---

# Dépendances

* ESP8266 core
* TFT_eSPI
* XPT2046_Touchscreen

---

# Version

```text
v1.0
```

## Projet

**3x0c3t BO4RD SCREEN DIAG**

## Auteur

**3x0c3t**

GitHub :

https://github.com/3x0c3t/3x0c3t_BO4RD_SCREENDIAG
