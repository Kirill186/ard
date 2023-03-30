#include <TimerOne.h>
#include <LiquidCrystal.h>

// Define LCD pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define pulse parameters
const unsigned long PULSE_WIDTH = 500; // Pulse width in microseconds
const unsigned long PULSE_PERIOD = 1000; // Pulse period in microseconds
const unsigned long PULSE_HIGH_TIME = 0; // Pulse high time in microseconds

// Define initial frequency
int frequency = 1;

// Define button pins
const int BUTTON_INC_PIN = 6;
const int BUTTON_DEC_PIN = 7;

// Define button states
int buttonIncState = 0;
int buttonDecState = 0;

// Define button last states
int buttonIncLastState = LOW;
int buttonDecLastState = LOW;

// Define button debounce time
unsigned long debounceTime = 50;

// Define last time buttons were pressed
unsigned long lastDebounceTime = 0;

// Define interrupt function for pulse generation
void generatePulse() {
  static boolean output = LOW;
  digitalWrite(13, output);
  output = !output;
}

// Define function to update LCD display
void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Freq: ");
  lcd.print(frequency);
  lcd.print(" Hz");
}

void setup() {
  // Set up LCD display
  lcd.begin(16, 2);

  // Set up button pins as inputs
  pinMode(BUTTON_INC_PIN, INPUT);
  pinMode(BUTTON_DEC_PIN, INPUT);

  // Set up interrupt for pulse generation
  Timer1.initialize(PULSE_PERIOD);
  Timer1.attachInterrupt(generatePulse);

  // Turn on LED to indicate setup is complete
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // Update LCD display with initial frequency
  updateLCD();
}

void loop() {
  // Read button states
  int buttonIncReading = digitalRead(BUTTON_INC_PIN);
  int buttonDecReading = digitalRead(BUTTON_DEC_PIN);

  // Check if button states have changed
  if (buttonIncReading != buttonIncLastState || buttonDecReading != buttonDecLastState) {
    lastDebounceTime = millis();
  }

  // Debounce buttons
  if (millis() - lastDebounceTime > debounceTime) {
    if (buttonIncReading != buttonIncLastState) {
      if (buttonIncReading == HIGH) {
        frequency++;
        updateLCD();
      }
    }
    if (buttonDecReading != buttonDecLastState) {
      if (buttonDecReading == HIGH) {
        if (frequency > 1) {
          frequency--;
          updateLCD();
        }
      }
    }
  }

  // Update button last states
  buttonIncLastState = buttonIncReading;
  buttonDecLastState = buttonDecReading;

  // Delay for a short time to debounce switches
  delay(50);
}
