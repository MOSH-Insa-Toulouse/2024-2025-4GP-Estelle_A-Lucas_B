# 2024-2025-4GP-Estelle AUBRY-Lucas BOURDARIE
Projet capteur 2024 - 2025 | Estelle AUBRY et Lucas BOURDARIE | 4ème année, 59ème promotion

# Table des matières

[Présentation du projet](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd?tab=readme-ov-file#pr%C3%A9sentation-du-projet)

[I - Un capteur à base de graphite, c'est possible ?](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd?tab=readme-ov-file#i---un-capteur-%C3%A0-base-de-graphite-cest-possible-)

[II - Simulation sous LTSpice](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd?tab=readme-ov-file#ii---simulation-sous-ltspice)

[III - Réalisation du PCB avec KiCAD](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd?tab=readme-ov-file#iii---r%C3%A9alisation-du-pcb-avec-kicad)

[IV - Le banc de test automatisé](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd?tab=readme-ov-file#iv---le-banc-de-test-automatis%C3%A9)

[V - Le code Arduino pour piloter le projet](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd/tree/main?tab=readme-ov-file#v---le-code-arduino-pour-piloter-le-projet)

[VI - L'application Android avec Mit App Inventor](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd/blob/main/README.md#vi---lapplication-android-avec-mit-app-inventor)

[Conclusion](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd/blob/main/README.md#conclusion)

# Présentation du projet 
 
Ce projet a été mené dans le cadre de l'UF  "Du capteur au banc de test" . L'objectif est de réaliser un capteur de déformation à base de graphite. Pour ce faire, il suffit simplement de déposer du crayon à papier sur un bout de feuille. La tension ou la compression du papier engendre une variation de résistance qui est proportionnelle à la déformation appliquée. Les principes physiques qui se cachent derrière ce phénomène sont expliqués [ici](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd/blob/main/README.md#i---un-capteur-%C3%A0-base-de-graphite-cest-possible-). Le projet s'inscrit donc dans une démarche low-tech car le capteur nécessite peu de ressources et sa réalisation est accessible à tous !

De plus, le capteur graphite réalisé sera testé de manière à comparer ses performances avec un capteur de déformation commercial. Nous souhaitons dégager les forces et les limites du capteur graphite par rapport à un capteur commercial. Finalement, nous établirons une conclusion quant à la possible industrialisation de ce type de capteur. 

[INSÉRER IMAGE PROJET FINI]

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

Ensuite, nous avons designé un PCB simple face à l'aide du logiciel KiCAD. Il est à noter que l'entrée du capteur graphite est reliée à l'amplificateur transimpédance. Le conditionneur utilisé pour le capteur commercial est un pont diviseur de tension avec une résistance de 33k. De plus, nous avons ajouté un condensateur pour faire du débouncing sur l'encoder rotatif. Nous avons suivi ces étapes:

**1)** **Dessiner** les composants tels que l'OLED, l'encoder rotatif, le module Bluetooth, le capteur commercial et le capteur graphite

**2)** Réaliser les **empreintes** de ces composants

**3)** Sélectionner les résistances, les condensateurs et l'AOP pour **réaliser l'amplificateur transimpédance** dans l'éditeur de Schématique

**4)** Établir les **points de connexion** entre la carte Arduino et tous les composants

**5)** **Positioner** les composants sur la PCB

**6)** Importer les **modèles 3D** pour les composants non-présents par défaut dans les librairies

**7)** Faire **le routage** dans l'éditeur de PCB en évitant au maximum les masses flottantes et les vias

**N.B**: Le servo moteur n'apparaît pas ici car il sera relié à la carte Arduino par le biais d'un header.

<p align="center">Vue depuis l'éditeur de Schématique [INSÉRER IMG] </p>
<p align="center">Vue depuis l'éditeur de PCB [INSÉRER IMG] </p>
<p align="center">Vue 3D [INSÉRER IMG] </p>

# IV - Le banc de test automatisé
[INSÉRER IMAGE]

<div align="justify"> Afin d'optimiser notre relevé de mesures, nous avons mis au point un banc de test qui courbe automatiquement le capteur de déformation. De cette manière, nous minimisons les risques de dégradation du capteur graphite lors des relevés de mesure car nous ne touchons pas le capteur dès lors qu'il est positionné sur le banc de test. Le banc de test a été réalisé sous Fusions360 puis imprimé en 3D. Ce dernier permet des relevés entièrement personnalisables par l'utilisateur grâce au code Arduino développé. Avec ce banc de test, il est possible de réaliser des mesures sur le capteur graphite et le capteur commercial. Les mesures en tension se sont révélées être les plus faciles à mettre en place tandis que les mesures en compression sont plus délicates.</div>

## A) La glissière pilotée par le servo moteur
 [INSÉRER IMAGE]
 
<div align="justify">  Pour courber le capteur de déformation, nous avons utilisé un système de glissière qui se déplace sous l'action du servo moteur. En effet, nous avons conçu un engrenage qui se fixe sur le servo moteur et dont la rotation entraîne une glissière écrantée. Le bout de cette glissière est faite en forme d'encoche pour maintenir le capteur. Pour éviter que le capteur ne sorte de l'encoche au cours des mesures, nous avons également imprimé des petites cales qui assurent que le capteur reste bien  positionné. Enfin, nous avons imprimé deux glissières différentes, une pour le capteur commercial et une pour le capteur graphite car le capteur commercial était beaucoup plus long que le capteur graphite. La glissière du capteur commercial possède une petite fente au centre de l'encoche pour le maintenir correctement en place et permettre une déformation qui épouse mieux les rayons de courbure.</div>

## B) Les rayons de courbure interchangeables
[INSÉRER IMAGE]

<div align="justify"> Pour tester les capteurs, nous avons imprimé huit supports en 3D avec différents rayons de courbure. Ces supports s'imbriquent sur le banc de test comme nous pouvons le voir sur la photo [INSÉRER n°figure]. Les numéros qui figurent sur les supports correspondent à l'angle entre le bord jaune et le bord rouge. 
</div>

# V - Le code Arduino pour piloter le projet

## A) Description générale 

Le code développé permet à l'utilisateur de gérer facilement et intuitivement le banc de test pour effectuer les mesures. L'affichage se fait sur l'écran OLED sur lequel apparaissent [les différentes fonctionnalités](https://github.com/MOSH-Insa-Toulouse/2024-2025-4GP-Haistelle-Lucbourd/tree/main?tab=readme-ov-file#b-les-diff%C3%A9rentes-fonctionalit%C3%A9s). L'utilisateur peut parcourir les différents menus en tournant l'encoder rotatif dans le sens horaire ou anti-horaire. Pour "rentrer" dans un menu, il suffit d'appuyer sur l'encoder et l'interface se met à jour. Chaque menu possède sa propre fonctionalité que l'utilisateur peut librement régler. En principe, l'ordre des menus correspond à l'ordre dans lequel l'utilisateur doit effectuer les réglages avant de lancer la mesure via le menu "Démarrage" à la fin. Il est préférable de ne pas placer le capteur sur le banc de test avant le menu "Borne" pour ne pas l'abîmer lors des précédents réglages.

## B) Les différentes fonctionalités
### 1 - Le menu "BIENVENUE"
[INSÉRER IMAGE]
Ce menu souhaite la bienvenue à l'utilisateur. Il ne possède pas le fonctionalité particulière.

### 2 - Le menu "CONFIGURATION"
[INSÉRER IMAGE]
<div align="justify"> Ce menu permet à l'utilisateur de définir quel type de capteur il utilise entre le capteur graphite et le capteur commercial. Une fois le type de capteur sélectonné (fond bleu et écriture noire), il suffit d'appuyer sur l'encoder rotatif pour enregistrer le choix. </div>

### 3 - Le menu "CALIBRATION"
 [INSÉRER IMAGE]
<div align="justify"> Dans ce menu, l'utilisateur peut régler la valeur prise par le potentiomètre numérique de manière à ne pas saturer l'amplificateur opérationnel. Attention, ce menu n'est utile que lorsque le type de capteur choisi est le graphite car le potentiomètre numérique est utilisé dans l'amplificateur transimpédance. L'interface affiche à la fois la valeur de résistance prise par le potentiomètre numérique et le signal lu par l'entrée analogique du capteur graphite. Il s'agit donc d'une valeur comprise entre 0 et 1023. Lors des mesures, il faut également anticiper la variation de résistance engendrée par la déformation du capteur graphite. En effet, en compression, la résistance lue diminue donc le signal augmente et peut, si le potentiomètre n'est pas correctement réglé, saturer l'AOP. </div>

### 4 - Le menu "VITESSE"
 [INSÉRER IMAGE]
<div align="justify"> Dans le menu "Vitesse", l'utilisateur peut régler la vitesse à laquelle il souhaite effectuer les mesures, c'est-à-dire, la vitesse à laquelle la glissère reliée au servo moteur va se déplacer. L'écran affiche un pourcentage qui correspond à la vitesse du servo moteur. 0% correspond à la vitesse minimale et 100% la vitesse maximale. Pour augmenter la vitesse, il est nécessaire de tourner l'encodeur rotatoire dans le sens anti-horaire car il s'agit en réalité de "diminuer" un délai. De plus, lorsque la vitesse change (= l'encoder change de position), le servo moteur effectue un aller-retour au cours duquel il est possible faire varier la vitesse du servo à l'aide de l'encoder jusqu'à obtenir la vitesse désirée. L'affichage en % de la vitesse s'effectue <ins> à la fin </ins> de l'aller-retour. Il n'y a donc pas d'affichage en direct de la vitesse mais seulement après que le servo moteur ait fait un aller-retour. </div>
 [INSÉRER ALGORIGRAMME]

### 5 - Le menu "BORNE"
 [INSÉRER IMAGE]
<div align="justify"> À partir de cette étape, il faut placer le capteur sur le banc de test. Le menu "Borne" permet à l'utilisateur de régler la position maximale du servo moteur et par conséquent, celle de l'encoche qui maintient le capteur. De cette manière, l'utilisateur peut s'assurer que le capteur épouse correctement la forme du rayon de courbure. Pour augmenter ou diminuer la position maximale, il faut tourner l'encoder rotatif dans le sens hoaire ou anti-horaire. </div>
 
### 6 - Le menu "MODE de MESURE"
 [INSÉRER IMAGE]
<div align="justify"> À l'intérieur de ce menu, l'utilisateur définit le nombre de mesures qu'il souhaite faire. En effet, nous avons pensé que comme les valeurs de résistances lues en direct peuvent parfois varier beaucoup, il pourrait être intéressant de permettre à l'utilisateur de faire une moyenne sur un nombre de mesures qu'il définit lui-même. De ce fait, lorsque la valeur choisie est "5" par exemple, le code effectuera 5 relevés de résistances pour un même rayon de courbure. Le servo fera donc un aller, une mesure puis un retour, le tout 5 fois. La valeur finale affichée correspondra à une moyenne de la résistance sur les 5 mesures. Le nombre de mesure réalisable est compris entre 1 et 20. </div>


### 7 - Le menu "DÉMARRAGE"
 [INSÉRER IMAGE]
Le menu démarrage permet de lancer l'acquisition de mesure. Il prend en compte tous les paramètres précedemment définis par l'utilisateur. Par exemple pour des paramètres tels que:
- **Vitesse**: 52%
- **Borne**: 150
- **Mode de mesure**: 5
Le servo moteur effectuera 5 aller-retours jusqu'à la position 150 du servo à une vitesse de 52% de la vitessse maximale. 

 [INSÉRER ALGORIGRAMME]
### 8 - Le menu "LiveVIEW"
 [INSÉRER IMAGE]
<div align="justify"> Ce menu permet un affichage en direct de la valeur de résistance lue par l'entrée analogique. Il faut se placer à l'intérieur de ce menu pour utiliser l'application Android car les données sont envoyées au téléphone via le module Bluetooth HC-05. </div>

# VI - L'application Android avec Mit App Inventor

<div align="justify"> Cette application permet de recevoir les donnnées envoyées par le module Bluetooth du PCB et de les afficher sous forme de graphique. Pour ce faire, les données lues par l'entrée analogique du capteur suivent le processus suivant:

[insérer image explicative]

## A) L'écran de démarrage
[INSÉRER IMAGE]
<div align="justify"> L'écran de démarrage comporte un seul bouton "Démarrer" sur lequel il suffit de cliquer pour lancer l'application.</div>

## B) L'interface principale et ses fonctionalités
[INSÉRER IMAGE]

<div align="justify"> Sur le deuxième écran, l'utilisateur doit tout d'abord connecter son téléphone au module Bluetooth pour recevoir les données. Lorsque la connexion est établie, le bouton "Bluetooth connexion" s'affiche en vert. Ensuite, un switch permet de définir quel capteur est utilisé. Si l'on utilise le capteur graphite, il faut renseigner la valeur du potentiomètre numérique dans la case rose pour afficher la bonne valeur de résistance dans la case bleue claire. Un graphique en dessous permet d'afficher en direct les bytes reçus par le module Bluetooth. Les butes reçus sont également affichés dans la case jaune en dessous du graphique. </div>

# Conclusion
## A) Les mesures obtenues

## B) Comparaison avec un capteur commercial: qui sera le meilleur ?
