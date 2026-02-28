#include <LedControl.h>

LedControl lc = LedControl(11, 13, 10, 1); // DIN, CLK, CS, # of displays

// Player variables
int playerY = 4; 

// Obstacle variables
int obstacleX = 7;
int obstacleY = random(0, 8);

// Score
int score = 0;

// Buzzer pin
const int buzzer = 3;

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read joystick vertical axis
  int yValue = analogRead(A1);
  if (yValue < 400 && playerY > 0) playerY--; // Move up
  if (yValue > 600 && playerY < 7) playerY++; // Move down

  lc.clearDisplay(0);

  // Draw player
  lc.setLed(0, playerY, 0, true);

  // Draw obstacle
  lc.setLed(0, obstacleY, obstacleX, true);

  // Check collision
  if (playerY == obstacleY && obstacleX == 0) {
    tone(buzzer, 1000, 300); // Play buzzer sound
    Serial.println("Game Over! Final Score: " + String(score));
    delay(1000);
    resetGame();
  }

  // Move obstacle left
  obstacleX--;
  if (obstacleX < 0) {
    obstacleX = 7;
    obstacleY = random(0, 8);
    score++;
    Serial.println("Score: " + String(score));
  }

  delay(200); // Speed control
}

void resetGame() {
  score = 0;
  playerY = 4;
  obstacleX = 7;
  obstacleY = random(0, 8);
}
