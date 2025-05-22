// Définition des broches utilisées
const int buttonPin = A0;               // Premier bouton (pour les lumières)
const int soundButtonPin = A1;          // Deuxième bouton (pour le son)
const int ledPins[] = {11, 10, 9, 6, 5}; // Broches auxquelles les LED sont connectées
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // Calcul automatique du nombre de LED
const int HP = 7;                        // Broche du haut-parleur (enceinte)

// Variables pour mémoriser l'état des boutons
int buttonState = 0;
int lastButtonState = 0;
int soundButtonState = 0;
int lastSoundButtonState = 0;

// Variables de contrôle
int mode = 0;               // Mode de clignotement des lumières
bool lightsOn = false;      // État des lumières (non utilisé directement ici)
bool soundOn = false;       // État des enceintes (ON/OFF)
int melodyIndex = 0;        // Mélodie actuelle à jouer

void setup() {
  // Déclaration des broches des LED comme sorties
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Déclaration des boutons comme entrées
  pinMode(buttonPin, INPUT);
  pinMode(soundButtonPin, INPUT);

  // Déclaration de la broche du haut-parleur comme sortie
  pinMode(HP, OUTPUT);

  // Éteindre les lumières et le son au démarrage
  eteindreToutesLesLumiere();
  noTone(HP);
}

void loop() {
  // Lecture de l'état actuel des deux boutons
  int reading = digitalRead(buttonPin);
  int soundButtonReading = digitalRead(soundButtonPin);

  // Gestion du bouton des lumières
  if (reading != lastButtonState) {
    if (reading == HIGH) {
      // Passage au mode suivant (6 modes, retour à 0 après 5)
      mode = (mode + 1) % 6;
      if (mode == 0) {
        eteindreToutesLesLumiere(); // Mode 0 = tout éteindre
      }
    }
  }

  // Gestion du bouton du son
  if (soundButtonReading != lastSoundButtonState) {
    if (soundButtonReading == HIGH) {
      soundOn = !soundOn; // Bascule ON/OFF
      if (!soundOn) {
        noTone(HP); // Si OFF, on coupe le son
      }
    }
  }

  // Gestion des effets lumineux selon le mode sélectionné
  switch (mode) {
    case 0:
      eteindreToutesLesLumiere(); break;
    case 1:
      clignoterLumiere(100); break;
    case 2:
      clignoterLumiere(500); break;
    case 3:
      clignoterLumiere(1000); break;
    case 4:
      clignotementAleatoire(); break;
    case 5:
      variationIntensite(); break;
  }

  // Si le son est activé, jouer la mélodie
  if (soundOn) {
    jouerMelodie();
  }

  // Mise à jour des derniers états des boutons
  lastButtonState = reading;
  lastSoundButtonState = soundButtonReading;
}

// Fonction pour allumer toutes les LED
void allumerToutesLesLumiere() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

// Fonction pour éteindre toutes les LED
void eteindreToutesLesLumiere() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

// Fonction pour faire clignoter toutes les LED avec un délai donné
void clignoterLumiere(int delai) {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(delai);
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(delai);
}

// Fonction pour clignoter les LED de manière aléatoire
void clignotementAleatoire() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], random(2)); // random(2) = 0 ou 1
  }
  delay(100);
}

// Fonction pour varier l’intensité lumineuse des LED
void variationIntensite() {
  for (int i = 0; i < numLeds; i++) {
    analogWrite(ledPins[i], random(255)); // Valeur aléatoire entre 0 et 255
  }
  delay(100);
}

// Fonction pour jouer une mélodie différente selon l’index
void jouerMelodie() {
  switch (melodyIndex) {
    case 0: // Mélodie 1 : Petit Papa Noël
      tone(HP, 392, 400); delay(400); // Sol
      tone(HP, 392, 400); delay(400);
      tone(HP, 392, 400); delay(400);
      tone(HP, 440, 400); delay(400); // La
      tone(HP, 440, 400); delay(400);
      tone(HP, 440, 400); delay(400);
      tone(HP, 349, 400); delay(400); // Fa
      tone(HP, 349, 400); delay(400);
      tone(HP, 392, 400); delay(400); // Sol
      break;

    case 1: // Mélodie 2 : Douce Nuit
      tone(HP, 262, 1000); delay(200); // Do
      tone(HP, 262, 1000); delay(200);
      tone(HP, 392, 1000); delay(200); // Sol
      tone(HP, 392, 1000); delay(200);
      tone(HP, 440, 1000); delay(200); // La
      tone(HP, 440, 1000); delay(200);
      tone(HP, 392, 1000); delay(200); // Sol
      tone(HP, 349, 1000); delay(200); // Fa
      tone(HP, 349, 1000); delay(200);
      tone(HP, 330, 1000); delay(200); // Mi
      tone(HP, 330, 1000); delay(200);
      tone(HP, 294, 1000); delay(200); // Ré
      tone(HP, 294, 1000); delay(200);
      tone(HP, 262, 1000); delay(200); // Do
      break;

    case 2: // Mélodie 3 : Vive le vent
      tone(HP, 392, 500); delay(500); // Sol
      tone(HP, 392, 500); delay(500);
      tone(HP, 440, 500); delay(500); // La
      tone(HP, 440, 500); delay(500);
      tone(HP, 523, 500); delay(500); // Do
      tone(HP, 523, 500); delay(500);
      tone(HP, 440, 500); delay(500); // La
      tone(HP, 392, 500); delay(500); // Sol
      tone(HP, 392, 500); delay(500);
      tone(HP, 392, 500); delay(500);
      tone(HP, 440, 500); delay(500); // La
      tone(HP, 440, 500); delay(500);
      tone(HP, 523, 500); delay(500); // Do
      break;
  }

  // Passer à la mélodie suivante
  melodyIndex = (melodyIndex + 1) % 3;
}
