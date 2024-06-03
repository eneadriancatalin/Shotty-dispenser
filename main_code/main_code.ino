#include <LCD_I2C.h>
#include <Servo.h>
#include <Wire.h>

Servo myservo;

LCD_I2C lcd(0x27, 16, 2);

int servoAngles[] = { 30, 50, 70, 90, 110, 130, 150, 170 }; // Angles for each shot

// -------- LEDS -------------
int pinsToCheck[8] = { 0 };  // Store the shot position
byte yellowLeds = 0;         // Byte for yellow LEDs
byte greenLeds = 0;          // Byte for green LEDs

// -------- PINS SHIFT REGISTER -------------
// Pin connected to ST_CP of 74HC595
int stcp_Pin = 8;
// Pin connected to SH_CP of 74HC595
int shcp_Pin = 12;
// Pin connected to DS of 74HC595
int ds_Pin = 11;
int redLedPins[8] = { 2, 3, 4, 6, 7, 9, 10, 13 };

// -------- OTHER PINS -------------
const int pot_Pin = A0;    // Pin for potentiometer
const int button_Pin = 5;  // Pin for button

// -------- BUTTON -------------
const unsigned long holdTime = 1000;  // Duration in milliseconds to consider a long press

unsigned long buttonPressTime = 0;
bool buttonState = false;
bool buttonPressed = false;

// -------- SETTINGS -------------
int mode = 2;            // 0 - Manual | 1 - Automatic | 2 - Random | 3 - Clean
int min_Mililitri = 20;  // Minimum milliliters
int max_Mililitri = 50;  // Maximum milliliters
int pot_Val = 0;         // Potentiometer value
int pot_Increment = 5;   // Potentiometer increment value
int pour_Time = 72;      // Pump active time in ms for a ml
int servo_Time = 2000;   // Time for servo to reach 1 glass

void setup() {
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  myservo.attach(A3);
  myservo.write(0);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
  for (int i = 0; i <= 7; i++) {
    pinMode(redLedPins[i], INPUT);
  }

  pinMode(button_Pin, INPUT_PULLUP);
  pinMode(stcp_Pin, OUTPUT);
  pinMode(shcp_Pin, OUTPUT);
  pinMode(ds_Pin, OUTPUT);
  displayShiftRegister(0, 0);
}

void loop() {
  checkRedLeds();
  updatePotValue();
  displayPotValue();
  updateState();
  displayMode();
}

void checkRedLeds() {
  for (int pin = 0; pin < 7; pin++) {
    int pinState = digitalRead(redLedPins[pin]);

    if (pinState == HIGH) {
      pinsToCheck[pin] = 1;
    } else {
      pinsToCheck[pin] = 0;
    }
    Serial.print(pinsToCheck[pin]);
  }
  Serial.print(pinsToCheck[7]);
  Serial.println();
}

void displayShiftRegister(byte lowByteValue, byte highByteValue) {
  Serial.print("Entered shift function ");
  Serial.print(lowByteValue);
  Serial.print(" ");
  Serial.print(highByteValue);
  Serial.println();
  digitalWrite(stcp_Pin, LOW);
  shiftOut(ds_Pin, shcp_Pin, LSBFIRST, highByteValue);
  shiftOut(ds_Pin, shcp_Pin, LSBFIRST, lowByteValue);
  digitalWrite(stcp_Pin, HIGH);
}

void updatePotValue() {
  pot_Val = analogRead(pot_Pin) - 10;
  pot_Val = map(pot_Val, 0, 1023, min_Mililitri, max_Mililitri + pot_Increment) / pot_Increment * pot_Increment;
}

void displayPotValue() {
  lcd.setCursor(0, 1);
  if (pot_Val < 10) {
    lcd.print("0");
  }
  lcd.print(pot_Val);
  lcd.print(" ml");
}

void updateState() {
  int buttonState = digitalRead(button_Pin);

  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;
    buttonPressTime = millis();
    Serial.println("Button pressed.");
    greenLeds = 0;
  } else if (buttonState == HIGH && buttonPressed) {
    buttonPressed = false;
    unsigned long pressDuration = millis() - buttonPressTime;

    Serial.print("Press duration: ");
    Serial.println(pressDuration);

    if (pressDuration < holdTime) {
      for (int i = 0; i < 8; i++) {
        Serial.print(pinsToCheck[i]);
      }
      Serial.println();
      if (mode == 0) {
        pourManual(pinsToCheck);
      } else if (mode == 2) {
        pourRandom(pinsToCheck);
      } else if (mode == 3) {
        clean();
      }
    } else {
      switch (mode) {
        case 0:
          mode = 1;
          break;
        case 1:
          mode = 2;
          break;
        case 2:
          mode = 3;
          break;
        case 3:
          mode = 0;
      }
      clearLCDLine(0);
    }
  }
}

void clearLCDLine(int line) {
  lcd.setCursor(0, line);
  for (int n = 0; n < 20; n++) {
    lcd.print(" ");
  }
}

void pourManual(int pinsToCheck[8]) {
  for (int i = 0; i < 8; i++) {
    if (pinsToCheck[i] == 1) {
      yellowLeds |= (1 << i);
      displayShiftRegister(yellowLeds, greenLeds);
      if (i == 0) {
        pour(0, servoAngles[i]);
      } else {
        pour(servoAngles[0], servoAngles[i]);
      }
      greenLeds |= (1 << i);
      yellowLeds = 0;
      displayShiftRegister(yellowLeds, greenLeds);
    }
  }
}

void clean() {
  Serial.print("Cleaning");
  delay(500);
  digitalWrite(A2, LOW);
  delay(2000);
  digitalWrite(A2, HIGH);
  delay(500);
}

void pour(int i, int j) {
  servo(int i, int j)
  delay(1500);
  digitalWrite(A2, LOW);
  delay(pour_Time* pot_Val);
  digitalWrite(A2, HIGH);
  delay(500);
}

void pourRandom(int pinsToCheck[8]) {
  int trickeryCount = 0;
  int previousPos = -1;
  int randomWhile = random(3, 8);
  int randomPos;
  while (trickeryCount < randomWhile) {
    do {
      randomPos = random(0, 8);
    } while (randomPos == previousPos);

    for (int j = 0; j < 8; j++) {
      Serial.print(pinsToCheck[j]);
    }

    if (pinsToCheck[randomPos] == 1) {
      yellowLeds |= (1 << randomPos);
      displayShiftRegister(yellowLeds, 0);
      delay(1000);
      yellowLeds = 0;
      displayShiftRegister(yellowLeds, 0);
      trickeryCount++;
      previousPos = randomPos;
    }
  }
  int randomGlass;

  do {
    randomGlass = random(0, 8);
  } while (pinsToCheck[randomGlass] == 0);
  yellowLeds |= (1 << randomGlass);
  displayShiftRegister(yellowLeds, 0);
  pour(servoAngles[randomGlass], servoAngles[randomPos]);
  yellowLeds = 0;
  greenLeds |= (1 << randomGlass);
  displayShiftRegister(yellowLeds, greenLeds);
  delay(1000);
}

void servo(int angles, int precedent) {
  if (angles > precedent) {
    for (int i = angles; i > precedent; i--){
      myservo.write(i);
    }
  } else {
    for (int i = precedent; i < angles; i++) {
      myservo.write(i);
    }
  }
}

void displayMode() {
  lcd.setCursor(0, 0);
  switch (mode) {
    case 0:
      lcd.print("Manual");
      break;
    case 1:
      lcd.print("Automatic");
      break;
    case 2:
      lcd.print("Random");
      break;
    case 3:
      lcd.print("Cleaning");
      break;
  }
}
