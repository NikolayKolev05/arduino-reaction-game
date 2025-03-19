#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int ledPins[] = {8, 9, 10};
const int buttonPin = 7;

long startTime;
long reactionTime;
int requiredTime = 500;
int level = 1;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.print("Reaction game");
  delay(2000);
  lcd.clear();
  Serial.begin(9600);
}

void loop() {
  lcd.print("Level: ");
  lcd.print(level);
  Serial.print("Level: ");
  Serial.println(level);

  delay(random(1000, 5000));
  lcd.clear();

  int randomIndex = random(0, 3);
  int selectedLed = ledPins[randomIndex];
  digitalWrite(selectedLed, HIGH);
  startTime = millis();
  lcd.print("Press it!");

  while (digitalRead(buttonPin) == HIGH) {
    if (millis() - startTime > requiredTime) {
      gameOver();
      return;
    }
  }

  digitalWrite(selectedLed, LOW);
  reactionTime = millis() - startTime;
  lcd.clear();

  if (reactionTime <= requiredTime) {
    lcd.print("Time: ");
    lcd.print(reactionTime);
    lcd.print(" ms");
    delay(2000);
    level++;
    adjustRequiredTime();
  } else {
    gameOver();
  }

  lcd.clear();
}

void adjustRequiredTime() {
  if (requiredTime > 200) {
    requiredTime -= 50;
  } else if (requiredTime > 140) {
    requiredTime -= 20;
  } else {
    gameWon();
  }
}

void gameOver() {
  lcd.clear();
  lcd.print("Game Over!");
  delay(2000);
  lcd.clear();
  lcd.print("Your time: ");
  lcd.print(reactionTime);
  lcd.print("ms");
  lcd.setCursor(0, 1);
  lcd.print("Req: ");
  lcd.print(requiredTime);
  lcd.print(" ms");
  delay(3000);
  resetGame();
}

void gameWon() {
  lcd.clear();
  lcd.print("Congrats!");
  lcd.setCursor(0, 1);
  lcd.print("You Win!!!");
  delay(4000);
  resetGame();
}

void resetGame() {
  requiredTime = 500;
  level = 1;
  lcd.clear();
}
