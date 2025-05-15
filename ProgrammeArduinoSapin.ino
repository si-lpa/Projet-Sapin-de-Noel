const int buttonPin = A0;
const int soundButtonPin = A1;
const int ledPins[] = {11, 10, 9, 6, 5};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
const int HP = 7;

int buttonState = 0;
int lastButtonState = 0;
int soundButtonState = 0;
int lastSoundButtonState = 0;

int mode = 0;
bool lightsOn = false;
bool soundOn = false;
int melodyIndex = 0; // Compteur pour les mélodies

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT);
  pinMode(soundButtonPin, INPUT);
  pinMode(HP, OUTPUT);
  eteindreToutesLesLumiere();
  noTone(HP);
}

void loop() {
  int reading = digitalRead(buttonPin);
  int soundButtonReading = digitalRead(soundButtonPin);

  if (reading != lastButtonState) {
    if (reading == HIGH) {
      mode = (mode + 1) % 6;
      if (mode == 0) {
        eteindreToutesLesLumiere();
      }
    }
  }

  if (soundButtonReading != lastSoundButtonState) {
    if (soundButtonReading == HIGH) {
      soundOn = !soundOn;
      if (!soundOn) {
        noTone(HP);
      }
    }
  }

  switch (mode) {
    case 0:
      eteindreToutesLesLumiere();
      break;
    case 1:
      clignoterLumiere(100);
      break;
    case 2:
      clignoterLumiere(500);
      break;
    case 3:
      clignoterLumiere(1000);
      break;
    case 4:
      clignotementAleatoire();
      break;
    case 5:
      variationIntensite();
      break;
  }

  if (soundOn) {
    jouerMelodie();
  }

  lastButtonState = reading;
  lastSoundButtonState = soundButtonReading;
}

void allumerToutesLesLumiere() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

void eteindreToutesLesLumiere() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

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

void clignotementAleatoire() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], random(2));
  }
  delay(100);
}

void variationIntensite() {
  for (int i = 0; i < numLeds; i++) {
    analogWrite(ledPins[i], random(255));
  }
  delay(100);
}

void jouerMelodie() {
  switch (melodyIndex) {
    case 0: // Mélodie 1: "Petit Papa Noël"
      tone(HP, 392, 400); // Sol
      delay(400);
      tone(HP, 392, 400); // Sol
      delay(400);
      tone(HP, 392, 400); // Sol
      delay(400);
      tone(HP, 440, 400); // La
      delay(400);
      tone(HP, 440, 400); // La
      delay(400);
      tone(HP, 440, 400); // La
      delay(400);
      tone(HP, 349, 400); // Fa
      delay(400);
      tone(HP, 349, 400); // Fa
      delay(400);
      tone(HP, 392, 400); // Sol
      delay(400);
      break;

    case 1: // Mélodie 2: "Douce Nuit"
      tone(HP, 262, 1000); // Do
      delay(200);
      tone(HP, 262, 1000); // Do
      delay(200);
      tone(HP, 392, 1000); // Sol
      delay(200);
      tone(HP, 392, 1000); // Sol
      delay(200);
      tone(HP, 440, 1000); // La
      delay(200);
      tone(HP, 440, 1000); // La
      delay(200);
      tone(HP, 392, 1000); // Sol
      delay(200);
      tone(HP, 349, 1000); // Fa
      delay(200);
      tone(HP, 349, 1000); // Fa
      delay(200);
      tone(HP, 330, 1000); // Mi
      delay(200);
      tone(HP, 330, 1000); // Mi
      delay(200);
      tone(HP, 294, 1000); // Ré
      delay(200);
      tone(HP, 294, 1000); // Ré
      delay(200);
      tone(HP, 262, 1000); // Do
      delay(200);
      break;

    case 2: // Mélodie 3: "Vive le vent"
      tone(HP, 392, 500); // Sol
      delay(500);
      tone(HP, 392, 500); // Sol
      delay(500);
      tone(HP, 440, 500); // La
      delay(500);
      tone(HP, 440, 500); // La
      delay(500);
      tone(HP, 523, 500); // Do
      delay(500);
      tone(HP, 523, 500); // Do
      delay(500);
      tone(HP, 440, 500); // La
      delay(500);
      tone(HP, 392, 500); // Sol
      delay(500);
      tone(HP, 392, 500); // Sol
      delay(500);
      tone(HP, 392, 500); // Sol
      delay(500);
      tone(HP, 440, 500); // La
      delay(500);
      tone(HP, 440, 500); // La
      delay(500);
      tone(HP, 523, 500); // Do
      delay(500);
      break;
  }

  melodyIndex = (melodyIndex + 1) % 3;
}
