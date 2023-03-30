#include <PulsePal.h>
#include <LiquidCrystal.h>

const int inputPinIncrease = 2;
const int inputPinDecrease = 3;
const int outputPin = 13;
const int rs = 12;
const int en = 11;
const int d4 = 7;
const int d5 = 6;
const int d6 = 5;
const int d7 = 4;

PulsePal pulsePal;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(inputPinIncrease, INPUT);
  pinMode(inputPinDecrease, INPUT);
  pinMode(outputPin, OUTPUT);
  pulsePal.begin();
  pulsePal.setFrequency(10);
  pulsePal.setPhaseDuration(1, 100);
  pulsePal.setPhaseDelay(1, 0);
  pulsePal.setPhasePolarity(1, PulsePal::PhasePolarity::Positive);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Pulse Generator");
}

void loop() {
  int inputIncreaseValue = digitalRead(inputPinIncrease);
  int inputDecreaseValue = digitalRead(inputPinDecrease);
  if (inputIncreaseValue == HIGH) {
    if (pulsePal.getFrequency() < 500) {
      int newFrequency = pulsePal.getFrequency() + 1;
      pulsePal.setFrequency(newFrequency);
      lcd.setCursor(0, 0);
      lcd.print("Freq: ");
      lcd.print(newFrequency);
      lcd.print(" Hz    ");
    }
  } else if (inputDecreaseValue == HIGH) {
    if (pulsePal.getFrequency() > 1) {
      int newFrequency = pulsePal.getFrequency() - 1;
      pulsePal.setFrequency(newFrequency);
      lcd.setCursor(0, 0);
      lcd.print("Freq: ");
      lcd.print(newFrequency);
      lcd.print(" Hz    ");
    }
  } else {
    digitalWrite(outputPin, LOW);
    pulsePal.stop();
    lcd.setCursor(0, 1);
    lcd.print("Idle             ");
    lcd.setCursor(0, 0);
    lcd.print("Freq: ");
    lcd.print(pulsePal.getFrequency());
    lcd.print(" Hz    ");
  }

  int inputValue = digitalRead(inputPinIncrease) || digitalRead(inputPinDecrease);
  if (inputValue == HIGH) {
    digitalWrite(outputPin, HIGH);
    pulsePal.start();
    lcd.setCursor(0, 1);
    lcd.print("Generating pulse");
    lcd.setCursor(0, 0);
    lcd.print("Freq: ");
    lcd.print(pulsePal.getFrequency());
    lcd.print(" Hz    ");
  } else {
    digitalWrite(outputPin, LOW);
    pulsePal.stop();
    lcd.setCursor(0, 1);
    lcd.print("Idle             ");
    lcd.setCursor(0, 0);
    lcd.print("Freq: ");
    lcd.print(pulsePal.getFrequency());
    lcd.print(" Hz    ");
  }
}
