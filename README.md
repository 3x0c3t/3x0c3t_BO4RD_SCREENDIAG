# 3x0c3t BO4RD SCREEN DIAG

Diagnostic complet d'un écran tactile **TFT SPI ILI9341 2.8" 240×320** associé à un **ESP8266 NodeMCU** et à un contrôleur tactile résistif **XPT2046**.

Le projet a pour objectif de fournir un outil autonome permettant de vérifier le fonctionnement matériel et logiciel de l'écran TFT, du bus SPI, du contrôleur tactile, de la conversion des coordonnées tactiles et de l'interaction avec l'écran.

---

## Sommaire

* [Présentation](#présentation)
* [Objectifs](#objectifs)
* [Matériel](#matériel)
* [Architecture](#architecture)
* [Câblage](#câblage)
* [Configuration TFT_eSPI](#configuration-tft_espi)
* [Logiciels et bibliothèques](#logiciels-et-bibliothèques)
* [Structure du projet](#structure-du-projet)
* [Fonctionnement](#fonctionnement)
* [Séquence de démarrage](#séquence-de-démarrage)
* [Diagnostic écran](#diagnostic-écran)
* [Diagnostic tactile](#diagnostic-tactile)
* [Calibration tactile](#calibration-tactile)
* [Calcul de précision](#calcul-de-précision)
* [Application de dessin](#application-de-dessin)
* [Commandes de l'application de dessin](#commandes-de-lapplication-de-dessin)
* [Moniteur Série](#moniteur-série)
* [Compilation](#compilation)
* [Téléversement](#téléversement)
* [Dépannage](#dépannage)
* [Problèmes connus](#problèmes-connus)
* [Évolutions prévues](#évolutions-prévues)
* [Historique](#historique)
* [Auteur](#auteur)

---

# Présentation

`3x0c3t_BO4RD_SCREENDIAG` est un projet de diagnostic matériel destiné à une carte **ESP8266 NodeMCU** équipée d'un écran tactile TFT SPI.

Le projet teste successivement :

1. l'initialisation de l'ESP8266 ;
2. l'initialisation du TFT ;
3. la rotation de l'affichage ;
4. la résolution effective de l'écran ;
5. les couleurs ;
6. la géométrie et les limites de l'affichage ;
7. l'initialisation du contrôleur tactile XPT2046 ;
8. la lecture des coordonnées brutes du tactile ;
9. la calibration du tactile ;
10. la conversion des coordonnées RAW vers les coordonnées écran ;
11. la précision de la calibration ;
12. l'interaction tactile ;
13. le dessin tactile en temps réel.

Le projet sert donc à la fois de **programme de test**, de **banc de diagnostic** et de **base logicielle** pour les futurs projets utilisant cet écran.

---

# Objectifs

## Objectifs principaux

* Vérifier le fonctionnement du TFT.
* Vérifier le bus SPI.
* Vérifier le contrôleur tactile XPT2046.
* Identifier les erreurs de câblage.
* Vérifier les GPIO réellement utilisés.
* Mesurer les coordonnées RAW du tactile.
* Calibrer les coordonnées tactiles.
* Convertir les coordonnées RAW en coordonnées écran.
* Visualiser les erreurs de positionnement.
* Tester le tactile sur toute la surface.
* Tester une application interactive simple.

## Objectifs secondaires

Le projet sert également de base pour développer d'autres interfaces graphiques utilisant :

* ESP8266 ;
* TFT_eSPI ;
* ILI9341 ;
* XPT2046 ;
* interfaces tactiles ;
* applications graphiques embarquées.

---

# Matériel

## Microcontrôleur

### ESP8266 NodeMCU

Carte de développement basée sur l'ESP8266.

Le projet utilise notamment les GPIO suivants :

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

---

# Écran

## TFT ILI9341

Écran TFT SPI 2.8 pouces.

Caractéristiques utilisées par le projet :

* contrôleur : ILI9341 ;
* interface : SPI ;
* résolution : 240 × 320 pixels ;
* orientation utilisée : rotation `2` ;
* afficha
