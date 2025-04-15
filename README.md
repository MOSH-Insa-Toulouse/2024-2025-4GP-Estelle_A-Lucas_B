# 2024-2025-4GP-Estelle AUBRY-Lucas BOURDARIE
Projet capteur 2024 - 2025 | Estelle AUBRY et Lucas BOURDARIE | 4ème année, 59ème promotion

# Présentation du projet 
 
Ce projet a été mené dans le cadre de l'UF  "Du capteur au banc de test" . L'objectif est de réaliser un capteur de déformation à base de graphite. Pour ce faire, il suffit simplement de déposer du crayon à papier sur un bout de feuille. La tension ou la compression du papier engendre une variation de résistance qui est proportionnelle à la déformation appliquée. Les principes physiques qui se cachent derrière ce phénomène sont expliqués [ici](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd/blob/main/README.md#i---un-capteur-%C3%A0-base-de-graphite-cest-possible-). Le projet s'inscrit donc dans une démarche low-tech car le capteur nécessite peu de ressources et sa réalisation est accessible à tous !

De plus, le capteur graphite réalisé sera testé de manière à comparer ses performances avec un capteur de déformation commercial. Nous souhaitons dégager les forces et les limites du capteur graphite par rapport à un capteur commercial. Finalement, nous établirons une conclusion quant à la possible industrialisation de ce type de capteur. 

<div align="justify"> </div>


 ## Livrables
À la fin de ce projet, plusieurs livrables sont attendus:
- Un **PCB** sur lequel seront connectés tous les éléments cités dans la partie [Matériel utilisé](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd/blob/main/README.md#mat%C3%A9riel-utilis%C3%A9)
- Un **banc de test** pour étudier la déformation du capteur graphite et du capteur commercial
- Un **code Arduino** qui permette de contrôler le banc de test et d'afficher les mesures de résistances
- Une **datasheet** qui énonce toutes les caractéristiques du capteur graphite
- Une **application Android** (.apk) pour visualiser les relevés de mesures en direct

## Matériel utilisé 
Pour le **montage**, voici tout le matériel requis:
- Une carte Arduino UNO
- Un écran OLED (I2C) 
- Un module Bluetooth HC-05
- Un potentiomètre numérique MCP41050
- Un encoder rotatif
- Un capteur de déformation commercial (FlexSensor) pour effectuer une comparaison
- Des crayons à papiers différents pour les tests
- Un servo moteur
- Des header de différentes tailles pour fixer les composants sur le PCB
- Une résistance de 33k

Pour réaliser **l'amplificateur transimpédance**, la liste de matériel est la suivante:
- Un amplificateur opérationnel LTC1050
- Deux condensateurs de 100nF
- Un condensateur de 1uF
- Deux résistances de 100k
- Deux résistances de 1k
- Une résistance de 10k

# I - Un capteur à base de graphite, c'est possible ?

# II - Simulation sous LTSpice

## A) Montage avec l'amplificateur transimpédance

## B) Résultats de la simulation

# III - Réalisation du PCB avec KiCAD

Ensuite, nous avons designé un PCB simple face à l'aide du logiciel KiCAD. Pour ce faire, nous avons suivi ces étapes:

**1)** **Dessiner** les composants tels que l'OLED, l'encoder rotatif, le module Bluetooth, le capteur commercial et le capteur graphite

**2)** Réaliser les **empreintes** de ces composants

**3)** Sélectionner les résistances, les condensateurs et l'AOP pour **réaliser l'amplificateur transimpédance** dans l'éditeur de Schématique

**4)** Établir les **points de connexion** entre la carte Arduino et tous les composants

**5)** **Positioner** les composants sur la PCB

**6)** Importer les **modèles 3D** pour les composants non-présents par défaut dans les librairies

**7)** Faire **le routage** dans l'éditeur de PCB en évitant au maximum les masses flottantes et les vias

**N.B**: Le servo moteur n'appairaît pas ici car il sera relié à la carte Arduino par le biais d'un header.

<p align="center">Vue depuis l'éditeur de Schématique [INSÉRER IMG] </p>
<p align="center">Vue depuis l'éditeur de PCB [INSÉRER IMG] </p>
<p align="center">Vue 3D [INSÉRER IMG] </p>

# IV - Le banc de test automatisé

<div align="justify"> Afin d'optimiser notre relevé de mesures, nous avons mis au point un banc de test qui courbe automatiquement le capteur de déformation. De cette manière, nous minimisons les risques de dégradation du capteur graphite lors des relevés de mesure car nous ne touchons pas le capteur dès lors qu'il est positionné sur le banc de test. Le banc de test a été réalisé sous Fusions360 puis imprimé en 3D. Ce dernier permet des relevés entièrement personnalisables par l'utilisateur grâce au code Arduino développé. Avec ce banc de test, il est possible de réaliser des mesures sur le capteur graphite et le capteur commercial. Les mesures en tension se sont révélées être les plus faciles à mettre en place tandis que les mesures en compression sont plus délicates.</div>

## A) La glissière pilotée par le servo moteur
 [INSÉRER IMAGE]
<div align="justify">  Pour courber le capteur de déformation, nous avons utilisé un système de glissière qui se déplace sous l'action du servo moteur. En effet, nous avons conçu un engrenage qui se fixe sur le servo moteur et dont la rotation entraîne une glissière   écrantée. Le bout de cette glissière est designé en forme d'encoche pour maintenir le capteur. Pour éviter que le capteur ne sorte de l'encoche au cours des mesures, nous avons également imprimé des petites cales qui assurent que le capteur reste bien 
positionné. Enfin, nous avons imprimé deux glissières différentes pour le capteur commercial et pour le capteur graphite car le capteur commercial était beaucoup plus long que le capteur graphite. La glissière du capteur commercial possède une petite fente au centre de l'encoche pour le maintenir correctement en place et permettre une déformation qui épouse mieux les rayons de courbure.</div>

## B) Les rayons de courbure interchangeables
[INSÉRER IMAGE]

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
