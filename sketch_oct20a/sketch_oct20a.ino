#include <LiquidCrystal.h>
#include <Keypad.h>

int timer = 180; // seconds

int currentTimer;
unsigned long previousMillis = 0;
String password = "";
String guessedPassword = "";
boolean bombIsActive = false;
boolean bombExploded = false;
unsigned long bombActivatedMillis = 0;
int interval = 1000; // miliseconds

// buzzer pin
int buzzer = 4;

// led pin
int led = 3;

// display pins
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// keypad config
const byte ROWS = 4;
const byte COLS = 4;
 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


// keypad pins
byte rowPins[ROWS] = {38, 39, 40, 41};
byte colPins[COLS] = {42, 43, 44, 45};

// creating keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); 
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

}


void loop() {
  
  char customKey = customKeypad.getKey();
  unsigned long currentMillis = millis();

    if (!bombExploded) {
      if (bombIsActive and (currentMillis - previousMillis >= interval)) {
        currentTimer = timer - (millis() / interval) + (bombActivatedMillis / interval);
        previousMillis = currentMillis;  
        digitalWrite(led, HIGH);
        digitalWrite(buzzer, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        digitalWrite(buzzer, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(currentTimer);
        lcd.setCursor(0, 1);
        lcd.print(guessedPassword);
        if (currentTimer <= 0) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("BOOM");
          digitalWrite(buzzer, HIGH);
          digitalWrite(led, HIGH);
          delay(5000);
          digitalWrite(buzzer, LOW);
          digitalWrite(led, LOW);
          bombExploded = true;
        }
      }
    
    if (customKey) {
      digitalWrite(buzzer, HIGH);
      delay(20);
      digitalWrite(buzzer, LOW);
      if (bombIsActive) {
        if (customKey == '#') {
          if (guessedPassword != password) {
            guessedPassword = "";
            lcd.clear();
            for (int i = 0; i < 3; i++) {
              delay(250);
              lcd.setCursor(0, 0);
              lcd.print("WRONG PASSWORD");
              delay(250);
              lcd.clear();
            }
            if (interval >= 300) {
              interval = interval - 100;
            }
          }
          else {
            bombIsActive = false;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("DEFUSED");
          }
        }
        else if (customKey == '*') {
          guessedPassword = "";
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(currentTimer);
        }
        else {
          Serial.println(customKey);
          guessedPassword = guessedPassword + customKey;
          lcd.setCursor(0, 1);
          lcd.print(guessedPassword);
          
        }
      }
      else {
        if (customKey == '#') {
          bombIsActive = true;
          bombActivatedMillis = millis();
          lcd.clear();
          lcd.setCursor(0, 1);
          for (int i = 0; i < password.length(); i++) {
            lcd.print('*');
      }
          delay(400);
          lcd.clear();
        }
        else if (customKey == '*') {
          password = "";
          lcd.clear();
        }
        else if (!bombIsActive) {
          lcd.clear();
          if (password.length() >= 15){
            lcd.setCursor(0, 0);
            lcd.print("MAX LENGTH");
          }
          password = password + customKey;
          lcd.setCursor(0, 1);
          lcd.print(password);
        }
      }
    Serial.println(password);
    Serial.println(bombIsActive);

    }
  }
} 