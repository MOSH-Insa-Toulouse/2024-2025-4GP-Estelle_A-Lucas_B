#include <Adafruit_SSD1306.h>            //Librairie pour l'écran OLED
#include <Fonts/FreeSerifItalic9pt7b.h>  //Librairie pour changer la police de l'écran OLED
#include <SoftwareSerial.h>              //Librairie pour la communication bluetooth
#include <SPI.h>                         //Librairie pour gérer la communication en SPI avec le potentiomètre digital
#include <Servo.h>                       //Librairie pour gérer la rotation du servo moteur

//Bluetooth
#define rxPin 8
#define txPin 9

//Flex sensor
#define flexPin A1

//Graphite sensor
#define graphite A0

//Encoder
#define encoder0PinA 2
#define encoder0PinB 4
#define Switch 5

//OLED
#define nombreDePixelsEnLargeur 128
#define nombreDePixelsEnHauteur 64
#define brocheResetOLED -1
#define adresseI2CecranOLED 0x3C
Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);

//Encoder
volatile int encoder_pos = 0;
int buttonState;
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 80;
int previous_reading = 1;
bool in_menu = false;
bool utiliser_graphite = 1;
int nmbre_repet = 1;


//Servo
int pos_servo = 90;
Servo myservo;
int valeur_borne = 180;
int val_vit = 40;

//Bluetooth
SoftwareSerial mySerial(rxPin, txPin);

//Flex
const float VCC = 5.0;
const float R = 33000.0;
const float flatR = 30900;
const float bendR = 63000;
int Valeur_flex;
float V_value_flex;
byte Valeur_flex_send;
float V_value;
float R_value;
float angle;

//Potentiometer digital
const byte csPin = 10;
const int maxPositions = 256;
const long rAB = 48000;
const byte rWiper = 125;
const byte pot0 = 0x11;
const byte pot0Shutdown = 0x21;
float res_pot = 0;
int R2_pos = 0;

//Graphite sensor
int Valeur_graphite;
byte Valeur_graphite_send;
float V_value_graph;
float resistance;
const float R1 = 100000.0;
const float R3 = 100000.0;
const float R5 = 10000.0;

//Permet de mettre à jour la valeur de la position de l'encoder lorsque celui-ci est tourné
void doEncoder() {
  if (digitalRead(encoder0PinA) == HIGH && digitalRead(encoder0PinB) == HIGH) {
    encoder_pos--;
  } else if (digitalRead(encoder0PinA) == HIGH && digitalRead(encoder0PinB) == LOW) {
    encoder_pos++;
  }
}

//Règle le potentiomètre digital à la position voulue et renvoi la valeur de résistance correspondante
float setPotWiper(int addr, int pos) {
  pos = constrain(pos, 0, 255);
  digitalWrite(csPin, LOW);
  SPI.transfer(addr);
  SPI.transfer(pos);
  digitalWrite(csPin, HIGH);

  return ((rAB * pos) / maxPositions) + rWiper;
}

//Permet d'afficher du texte sur l'écran OLED en précisant sa taille et sa position
void affichage_texte_OLED(String txt, int size, int c1, int c2) {
  ecranOLED.setTextSize(size);
  ecranOLED.setCursor(c1, c2);
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.print(txt);
}

//Permet d'afficher un entier sur l'écran OLED en précisant sa taille et sa position
void affichage_int_OLED(int value, int size, int c1, int c2) {
  ecranOLED.setTextSize(size);
  ecranOLED.setCursor(c1, c2);
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.print(value);
}

//Gère l'écran de bienvenue du banc de test
void welcome() {
  ecranOLED.clearDisplay();
  affichage_texte_OLED("BIENVENUE!", 2, 8, 26);
  ecranOLED.display();
  in_menu = false;
}

//Permet de configurer le mode d'utilisation du banc de test : flex sensor ou capteur graphite
void configuration() {
  if (in_menu) {
    encoder_pos = utiliser_graphite;
    while (in_menu) {
      menu();
      ecranOLED.clearDisplay();
      ecranOLED.setTextSize(2);
      ecranOLED.setCursor(0, 0);
      if (utiliser_graphite == 1) {
        ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        ecranOLED.println("Graphite");
        ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
        ecranOLED.print("Flexsensor");
      } else {
        ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
        ecranOLED.println("Graphite");
        ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        ecranOLED.print("Flexsensor");
      }
      ecranOLED.display();
      if (encoder_pos < 0) {
        encoder_pos = 0;
      } else if (encoder_pos > 1) {
        encoder_pos = 1;
      }
      utiliser_graphite = encoder_pos;
    }
    encoder_pos = 1;

  } else {
    ecranOLED.clearDisplay();
    affichage_texte_OLED("CONFIGURER", 2, 4, 26);
    ecranOLED.display();
  }
}

//Permet de calibrer le potentiomètre digital pour optimiser le signal si le capteur graphite est utilisé
void calibration() {

  if (in_menu) {
    for (int pos = pos_servo; pos > 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    encoder_pos = R2_pos;

    while (in_menu) {
      menu();
      ecranOLED.clearDisplay();
      ecranOLED.setTextSize(2);
      ecranOLED.setCursor(0, 0);
      ecranOLED.setTextColor(SSD1306_WHITE);
      ecranOLED.print("VALEUR R2:");
      ecranOLED.println(res_pot);
      //ecranOLED.println(" ohms");
      ecranOLED.println("GRAPHITE:");
      ecranOLED.println(analogRead(graphite));
      ecranOLED.display();

      if ((encoder_pos > 0) && (encoder_pos <= 255)) {
        res_pot = setPotWiper(pot0, encoder_pos);
      } else if (encoder_pos > 255) {
        encoder_pos = 255;
      } else {
        encoder_pos = 0;
      }
      delay(100);
    }
    for (int pos = 0; pos < pos_servo; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
    R2_pos = encoder_pos;
    encoder_pos = 2;
  } else {
    ecranOLED.clearDisplay();
    affichage_texte_OLED("CALIBRER", 2, 20, 26);
    ecranOLED.display();
  }
}

//Permet de régler la vitesse de fonctionnement du servo moteur durant les tests
void vitesse() {
  if (in_menu) {
    encoder_pos = val_vit;
    for (int pos = pos_servo; pos < 180; pos += 1) {
      myservo.write(pos);
      delay(val_vit);
    }

    while (in_menu) {
      menu();
      ecranOLED.clearDisplay();
      ecranOLED.setTextSize(2);
      ecranOLED.setCursor(0, 0);
      ecranOLED.setTextColor(SSD1306_WHITE);
      ecranOLED.println("Vitesse:");
      ecranOLED.print(round(val_vit * (-2.84) + 114.3));
      ecranOLED.print("%");
      ecranOLED.display();

      if (encoder_pos < 5) {
        encoder_pos = 5;
      } else if (encoder_pos > 40) {
        encoder_pos = 40;
      }

      if (val_vit != encoder_pos) {
        for (int pos = 180; pos > 0; pos -= 1) {
          if ((encoder_pos >= 5) && (encoder_pos <= 40)) {
            myservo.write(pos);
            delay(encoder_pos);
          } else if (encoder_pos < 5) {
            encoder_pos = 5;
            myservo.write(pos);
            delay(encoder_pos);
          } else {
            encoder_pos = 40;
            myservo.write(pos);
            delay(encoder_pos);
          }
        }
        for (int pos = 0; pos < 180; pos += 1) {
          if ((encoder_pos >= 5) && (encoder_pos <= 40)) {
            myservo.write(pos);
            delay(encoder_pos);
          } else if (encoder_pos < 5) {
            encoder_pos = 5;
            myservo.write(pos);
            delay(encoder_pos);
          } else {
            encoder_pos = 40;
            myservo.write(pos);
            delay(encoder_pos);
          }
        }
        val_vit = encoder_pos;
      }
      delay(100);
    }
    val_vit = encoder_pos;
    encoder_pos = 3;
    for (int pos = 180; pos > pos_servo; pos -= 1) {
      myservo.write(pos);
      delay(val_vit);
    }
  } else {
    ecranOLED.clearDisplay();
    affichage_texte_OLED("VITESSE", 2, 22, 26);
    ecranOLED.display();
  }
}

//Permet de régler la borne de fin de course du servo pour ne pas endommager l'extrémité d'un capteur
void borne() {
  if (in_menu) {
    encoder_pos = pos_servo;
    while (in_menu) {
      menu();
      ecranOLED.clearDisplay();
      ecranOLED.setTextSize(2);
      ecranOLED.setCursor(0, 0);
      ecranOLED.setTextColor(SSD1306_WHITE);
      ecranOLED.println("Borne sup:");
      ecranOLED.print(encoder_pos);
      ecranOLED.display();
      if ((encoder_pos > 0) && (encoder_pos <= 180)) {
        myservo.write(encoder_pos);
        delay(15);
      } else if (encoder_pos > 180) {
        encoder_pos = 180;
      } else {
        encoder_pos = 0;
      }
      delay(100);
    }
    pos_servo = encoder_pos;
    valeur_borne = encoder_pos;
    encoder_pos = 4;
  } else {
    ecranOLED.clearDisplay();
    affichage_texte_OLED("BORNE", 2, 38, 26);
    ecranOLED.display();
  }
}

//Permet à l'utilisateur de définir le nombre de mesures sur lesquelles la moyenne de la résistance sera calculée
void mode_mesure() {

  if (in_menu) {

    encoder_pos = nmbre_repet;

    while (in_menu) {
      menu();
      ecranOLED.clearDisplay();
      ecranOLED.setTextSize(2);
      ecranOLED.setCursor(0, 0);
      ecranOLED.setTextColor(SSD1306_WHITE);
      ecranOLED.print("Nbr repet:");
      ecranOLED.print(nmbre_repet);
      ecranOLED.display();

      if ((encoder_pos >= 1) && (encoder_pos <= 20)) {
        nmbre_repet = encoder_pos;
      } else if (encoder_pos < 1) {
        encoder_pos = 1;
      } else {
        encoder_pos = 20;
      }
    }
    nmbre_repet = encoder_pos;
    encoder_pos = 5;

  } else {
    ecranOLED.clearDisplay();
    affichage_texte_OLED("   MODE", 2, 5, 19);
    affichage_texte_OLED("  MESURE", 2, 5, 34);
    ecranOLED.display();
  }
}

//Permet de démarrer une mesure puis d'afficher la moyenne obtenue
void lancer_mesure() {

  if (in_menu) {
    Valeur_graphite = 0;
    Valeur_flex = 0;
    for (int i = pos_servo; i > 0; i--) {
      myservo.write(i);
      delay(val_vit);
    }

    for (int j = 1; j <= nmbre_repet; j++) {
      ecranOLED.clearDisplay();
      ecranOLED.setTextSize(2);
      ecranOLED.setCursor(0, 0);
      ecranOLED.setTextColor(SSD1306_WHITE);
      ecranOLED.print("Essai ");
      ecranOLED.println(j);
      ecranOLED.print("en cours:");
      ecranOLED.display();
      for (int i = 0; i < valeur_borne; i++) {

        myservo.write(i);
        delay(val_vit);
      }
      delay(1000);

      if (utiliser_graphite == 1) {
        Valeur_graphite += analogRead(graphite);
      } else {
        Valeur_flex += analogRead(flexPin);
      }
      for (int k = valeur_borne; k >= 0; k--) {
        myservo.write(k);
        delay(val_vit);
      }
      delay(1000);
    }

    if (utiliser_graphite == 1) {
      Valeur_graphite = Valeur_graphite / nmbre_repet;
      V_value_graph = Valeur_graphite * (VCC / 1023.0);
      resistance = ((1 + (R3 / res_pot)) * (VCC / V_value_graph)) * R1 - R1 - R5;

      ecranOLED.clearDisplay();
      ecranOLED.setTextSize(2);
      ecranOLED.setCursor(0, 0);
      ecranOLED.setTextColor(SSD1306_WHITE);
      ecranOLED.println("Resistance");
      ecranOLED.print(resistance);
      ecranOLED.display();
      delay(20);


    } else {
      Valeur_flex = Valeur_flex / nmbre_repet;
      V_value = Valeur_flex * VCC / 1023.0;
      R_value = R * V_value / (VCC - V_value);
      angle = map(R_value, flatR, bendR, 0.0, 90.0);

      ecranOLED.clearDisplay();
      ecranOLED.setTextSize(2);
      ecranOLED.setCursor(0, 0);
      ecranOLED.setTextColor(SSD1306_WHITE);
      ecranOLED.println("Resistance");
      ecranOLED.println(R_value);
      ecranOLED.println("Angle");
      ecranOLED.print(angle);
      ecranOLED.display();
      delay(20);
    }
    for (int i = 0; i < pos_servo; i++) {
      myservo.write(i);
      delay(val_vit);
    }
    delay(10000);
    in_menu = false;

  } else {
    ecranOLED.clearDisplay();
    affichage_texte_OLED("DEMARRAGE", 2, 12, 26);
    ecranOLED.display();
  }
}

//Permet d'observer en direct la résistance mesurée en fonction du capteur utilisé
void LiveVIEW() {

  if (in_menu) {
    resistance = 0;
    while (in_menu) {
      menu();
      if (utiliser_graphite == 1) {
        Valeur_graphite = analogRead(graphite);
        V_value_graph = Valeur_graphite * (VCC / 1023.0);
        resistance = ((1 + (R3 / res_pot)) * (VCC / V_value_graph)) * R1 - R1 - R5;
        Valeur_graphite_send = Valeur_graphite / 4;

        mySerial.write(Valeur_graphite_send);
        delay(100);
        ecranOLED.clearDisplay();
        ecranOLED.setTextSize(2);
        ecranOLED.setCursor(0, 0);
        ecranOLED.setTextColor(SSD1306_WHITE);
        ecranOLED.print("Resistance");
        ecranOLED.print(resistance);
        ecranOLED.display();
      } else {
        Valeur_flex = analogRead(flexPin);
        V_value_flex = Valeur_flex * VCC / 1023.0;
        resistance = R * V_value_flex / (VCC - V_value_flex);
        Valeur_flex_send = Valeur_flex / 4;


        mySerial.write(Valeur_flex_send);
        delay(100);
        ecranOLED.clearDisplay();
        ecranOLED.setTextSize(2);
        ecranOLED.setCursor(0, 0);
        ecranOLED.setTextColor(SSD1306_WHITE);
        ecranOLED.print("Resistance");
        ecranOLED.print(resistance);
        ecranOLED.display();
      }
      delay(50);
    }

  } else {
    ecranOLED.clearDisplay();
    affichage_texte_OLED("LiveVIEW", 2, 12, 26);
    ecranOLED.display();
  }
}

//Gère l'entrée ou la sortie d'un menu en fonction de l'appui sur le switch de l'encodeur rotatif
void menu() {
  //La variable in_menu change d'état à chaque appui sur le switch
  if (digitalRead(Switch) == LOW) {
    delay(200);
    if (in_menu == false) {
      in_menu = true;
    } else {
      in_menu = false;
    }
  }
}

void setup() {
  //Bluetooth
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  //Flex sensor
  pinMode(flexPin, INPUT);

  //Encoder
  pinMode(encoder0PinA, INPUT);
  digitalWrite(encoder0PinA, HIGH);
  pinMode(encoder0PinB, INPUT);
  digitalWrite(encoder0PinB, HIGH);
  attachInterrupt(0, doEncoder, RISING);
  pinMode(Switch, INPUT_PULLUP);

  //Serial link
  mySerial.begin(9600);
  //Serial.begin(9600);

  //OLED
  if (!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED))
    while (1)
      ;

  //Digital potentiometer
  digitalWrite(csPin, HIGH);
  pinMode(csPin, OUTPUT);
  SPI.begin();
  delay(5);
  setPotWiper(pot0, 4);
  R2_pos = 4;

  //Servo
  myservo.attach(6);
}

void loop() {
  //Gestion des différents menus à afficher en fonction de la position de l'encoder rotatif
  if (encoder_pos <= 0) {
    welcome();
    encoder_pos = 0;
  } else if (encoder_pos == 1) {
    configuration();
  } else if (encoder_pos == 2) {
    calibration();
  } else if (encoder_pos == 3) {
    vitesse();
  } else if (encoder_pos == 4) {
    borne();
  } else if (encoder_pos == 5) {
    mode_mesure();
  } else if (encoder_pos == 6) {
    lancer_mesure();
  } else if (encoder_pos >= 7) {
    LiveVIEW();
    encoder_pos = 7;
  }

  //Mise à jour de la variable in_menu
  menu();

  delay(200);
}
