# 2024-2025-4GP-Estelle AUBRY-Lucas BOURDARIE
Projet capteur 2024 - 2025 | Estelle AUBRY et Lucas BOURDARIE | 4ème année, 59ème promotion

# Présentation du projet 
 
Ce projet a été mené dans le cadre de l'UF  "Du capteur au banc de test" . L'objectif est de réaliser un capteur de déformation à base de graphite. Pour ce faire, il suffit simplement de déposer du crayon à papier sur un bout de feuille. La tension ou la compression du papier engendre une variation de résistance qui est proportionnelle à la déformation appliquée. Les principes physiques qui se cachent derrière ce phénomène sont expliqués [ici](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd/blob/main/README.md#i---un-capteur-%C3%A0-base-de-graphite-cest-possible-). Le projet s'inscrit donc dans une démarche low-tech car le capteur nécessite peu de ressources et sa réalisation est accessible à tous !

De plus, le capteur graphite réalisé sera testé de manière à comparer ses performances avec un capteur de déformation commercial. Nous souhaitons dégager les forces et les limites du capteur graphite par rapport à un capteur commercial. Finalement, nous établirons une conclusion quant à la possible industrialisation de ce type de capteur. 

<div align="justify"> </div>
  
## Matériel utilisé 
Pour effectuer des tests, voici tout le matériel requis:
- Une carte Arduino UNO
- Un écran OLED (I2C) 
- Un module Bluetooth HC-05
- Un potentiomètre numérique MCP41050
- Un encoder rotatif
- Un capteur de déformation commercial (FlexSensor) pour effectuer une comparaison
- Des crayons à papiers différents pour les tests
- Un servo moteur
- Une résistance de 33k

Pour réaliser l'amplificateur transimpédance, la liste de matériel est la suivante:
- Un amplificateur opérationnel LTC1050
- Deux condensateurs de 100nF
- Un condensateur de 1uF
- Deux résistances de 100k
- Deux résistances de 1k
- Une résistance de 10k
  
 ## Livrables

# I - Un capteur à base de graphite, c'est possible ?

# II - Simulation sous LTSpice

## A) Montage avec l'amplificateur transinpédance

## B) Résultats de simulation

# III - Réalisation du PCB avec KiCAD

# IV - Le banc de test automatisé

## A) La glissière pilotée par le servo moteur

## B) Les rayons de courbure interchangeables

# V - Le code Arduino pour piloter le projet

## A) Description générale 

## B) Les différentes fonctionalités

### 1 - Le menu "CONFIGURATION"
### 2 - Le menu "CALIBRATION"
### 3 - Le menu "VITESSE"
### 4 - Le menu "BORNE"
### 5 - Le menu "MODE de MESURE"
### 6 - Le menu "DÉMARRAGE"
### 7 - Le menu "LiveVIEW"

# VI - L'application Android avec Mit App Inventor

## A) L'écran de démarrage

## B) L'interface principale et ses fonctionalités

# Conclusion
## A) Les mesures obtenues

## B) Comparaison avec un capteur commercial: qui sera le meilleur ?
