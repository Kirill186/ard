#include <LiquidCrystal.h>

// Количество импульсов на оборот энкодера
const int pulsesPerRevolution = 20;

// Пины энкодера
const int encoderPin1 = 2;
const int encoderPin2 = 3;

// Пины LCD экрана
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int lastEncoderState;
int encoderState;
long lastEncoderValue;
long encoderValue;
int direction = 1;

void setup() {
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);
  lcd.begin(16, 2);
  lcd.print("Frequency:      ");
  lastEncoderValue = encoderValue = 0;
  lastEncoderState = digitalRead(encoderPin1);
}

void loop() {
  encoderState = digitalRead(encoderPin1);
  
  if (encoderState != lastEncoderState) {

    if (digitalRead(encoderPin2) != encoderState) encoderValue += direction;
    else encoderValue -= direction;

    lastEncoderValue = encoderValue;
    lastEncoderState = encoderState;
  }


  int frequency = abs(encoderValue) * 10;
  if (frequency >= 1000) {
    frequency = 999;
    encoderValue = direction * frequency / 10;
  }

  lcd.setCursor(11, 0);
  lcd.print("        ");
  lcd.setCursor(11, 0);
  lcd.print(frequency);
  lcd.print(" Hz");

  delay(50);
}
