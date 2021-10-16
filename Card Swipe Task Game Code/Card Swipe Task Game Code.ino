// This project is to recreate the Card Swipe task form Among Us. Everything is mounted by screws and fixed in place securely. Intended to use with the included model (Card Swipe Task Game v1.3)and to be resin printed.
// The included audio files need to be added to the adafruit soundboard mini in the .wav format and needs to be loaded in the following order:
// 0 - failure
// 1 - success
// 2 - round start
//
// Hardware needed:
// 1 - Arduino nano
// 1 - Adafruit USB mini breakout board
// 1 - Adafruit PAM8302 2.5w audio amplifier
// 1 - 3w 4 ohm 36mm speaker
// 1 - Adafruit ADA2341 AudioFX mini
// 1 - I2C 1602 LCD
// 2 - AITRIP IR Photo interupter Module
// 1 - Green 5mm LED
// 1 - Red 5mm LED
// 1 - 90 degree left angle to panel mount mini usb connector 30 cm
// about 150 cm of rainbow 7 wire
// 12 - 1.7*6mm screws
// 4 - 2.6x8x6mm screws
// 4 - 2.6x5x6mm screws
// 4 - 8-32 x 3/4 flat head philips screws

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

char *Failure[] = {
  "TOO FAST",
  "TOO SLOW",
  "INVALID ID"
};
long randNumber1;
long randNumber2;
long failure;
long success;
long x;
boolean hasRun = false;
const int leftTrigger = 2;
const int rightTrigger = 3;
const int failureLED = 7;
const int successLED = 8;
const int successFX = 10;
const int failureFX = 9;
const int startupFX = 11;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.init();
  lcd.backlight();
  //lcd.noCursor();
  pinMode(leftTrigger, INPUT);
  pinMode(rightTrigger, INPUT);
  pinMode(failureLED, OUTPUT);
  pinMode(failureFX, OUTPUT);
  pinMode(successLED, OUTPUT);
  pinMode(successFX, OUTPUT);
  pinMode(startupFX, OUTPUT);
  randomSeed(analogRead(0));
  failure < 11;
  success = 11;
  x = 0;
  
// Startup sequence, alternate flash the success LED and the failure LED while plaing the startupFX audio

  digitalWrite(failureLED, HIGH);
  digitalWrite(startupFX, LOW);
  delay(250);
  digitalWrite(startupFX, HIGH);
  digitalWrite(failureLED, LOW);
  digitalWrite(successLED, HIGH);
  delay(250);
  digitalWrite(successLED, LOW);
  digitalWrite(failureLED, HIGH);
  delay(250);
  digitalWrite(failureLED, LOW);
  digitalWrite(successLED, HIGH);
  delay(250);
  digitalWrite(successLED, LOW);
  digitalWrite(failureLED, HIGH);
  delay(250);
  digitalWrite(failureLED, LOW);
  digitalWrite(successLED, HIGH);
  delay(250);
  digitalWrite(successLED, LOW);
  digitalWrite(failureLED, HIGH);
  delay(250);
  digitalWrite(failureLED, LOW);
  digitalWrite(successLED, HIGH);
  delay(250);
  digitalWrite(successLED, LOW);
}

void loop() {

// Start game: display the "Please Swipe ID" text and set input/output pins to apropriate ready states

  lcd.setCursor(0, 0);
  lcd.print("Please Swipe ID");
  digitalWrite(failureLED, LOW);
  digitalWrite(successLED, LOW);
  digitalWrite(successFX, HIGH);
  digitalWrite(startupFX, HIGH);
  digitalWrite(failureFX, HIGH);

// Intital untriggered state and initilize RNG to have a maximun ramge of 0-12 for the game turns and 0-3 for the individual random failure responses. Serial prints can be removed to speed up processing but I am happy with the speed so i left them in.

  if (digitalRead(leftTrigger) == HIGH) {
    hasRun = false;
    randNumber1 = random(x, 12);
    randNumber2 = random(3);
    Serial.println("hasRun = false");
    Serial.println("x = ");
    Serial.println(x);
    Serial.println("RNG = ");
    Serial.println(randNumber1);
  }
// Triggered state

  while ((hasRun == false) && (digitalRead(leftTrigger) == LOW)) {
    Serial.println(hasRun);

// "Fail" response cycle

    if (randNumber1 < success) {
      Serial.println(Failure[randNumber2]);
      lcd.clear();
      digitalWrite(failureFX, LOW);
      digitalWrite(failureLED, HIGH);
      lcd.setCursor(3, 0);
      lcd.print(Failure[randNumber2]);
      lcd.setCursor(3, 1);
      lcd.print("Try Again");
      delay(240);
      digitalWrite(failureFX, HIGH);
      digitalWrite(failureLED, LOW);
      delay(250);
      digitalWrite(failureLED, HIGH);
      delay(250);
      digitalWrite(failureLED, LOW);
      delay(250);
      digitalWrite(failureLED, HIGH);
      delay(250);
      digitalWrite(failureLED, LOW);
      delay(250);
      digitalWrite(failureLED, HIGH);
      delay(245);
      lcd.clear();
      digitalWrite(failureLED, LOW);
      x++;
      hasRun = false;
    }
  
  // "Success" response cycle
  
    else if (randNumber1 >= success) {
      Serial.println("Accepted!");
      lcd.clear();
      digitalWrite(successLED, HIGH);
      digitalWrite(successFX, LOW);
      lcd.setCursor(3, 0);
      lcd.print("ACCEPTED!");
      lcd.setCursor(3, 1);
      lcd.print("THANK YOU!");
      delay(200);
      digitalWrite(successFX, HIGH);
      delay(1799);
      lcd.clear();
      digitalWrite(successLED, LOW);
      x = 0;
      hasRun = true;
    }
  }
}
