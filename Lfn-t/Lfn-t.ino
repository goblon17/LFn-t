#include "LiquidCrystal_I2C.h"

#define P1_RED 2
#define P1_GREEN 3
#define P1_BLUE 4
#define P1_YELLOW 5

#define P2_RED 6
#define P2_GREEN 7
#define P2_BLUE 8
#define P2_YELLOW 9

#define LED_RED 10
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_YELLOW 13

#define isPressed(x) (digitalRead(x)==LOW)

#define MAX_ROUNDS_NUMBER 999

void menuLoop();
void preLoop();
void gameLoop();
void overLoop();

void resetGame();

enum scene_e {
  MAIN_MENU,
  PRE_GAME,
  GAME,
  GAME_OVER
};

scene_e scene;

int roundsNumber = 3;
int roundsPlayed = 0;
int player1Score = 0;
int player2Score = 0;

LiquidCrystal_I2C lcd(0x20, 16, 2);

void setup() {
  // Setup player 1 buttons
  pinMode(P1_RED, INPUT_PULLUP);
  pinMode(P1_GREEN, INPUT_PULLUP);
  pinMode(P1_BLUE, INPUT_PULLUP);
  pinMode(P1_YELLOW, INPUT_PULLUP);

  // Setup player 2 buttons
  pinMode(P2_RED, INPUT_PULLUP);
  pinMode(P2_GREEN, INPUT_PULLUP);
  pinMode(P2_BLUE, INPUT_PULLUP);
  pinMode(P2_YELLOW, INPUT_PULLUP);

  // Setup LEDs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_YELLOW, LOW);

  // Setup LCD
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.clear();
  
  scene = MAIN_MENU;
}

void loop() {
  switch (scene) {
    case MAIN_MENU:
      menuLoop();
      break;
    case PRE_GAME:
      preLoop();
      break;
    case GAME:
      gameLoop();
      break;
    case GAME_OVER:
      overLoop();
      break;
  }
}

void menuLoop() {
  lcd.clear();
  lcd.print("      LFn't     ");
  lcd.print("    Start (G)   ");
  if (isPressed(P1_GREEN) || isPressed(P2_GREEN)) {
    scene = PRE_GAME;
  }
}

void preLoop() {
  lcd.clear();
  lcd.print("   Rounds (G)   ");
  lcd.print("<R            B>");
  char buf[4];
  itoa(roundsNumber, buf, 10);
  int pos = 8 - (strlen(buf) / 2);
  lcd.setCursor(pos, 1);
  lcd.printstr(buf);

  if (isPressed(P1_BLUE) || isPressed(P2_BLUE)) {
    if (roundsNumber < MAX_ROUNDS_NUMBER) {
      roundsNumber ++;
    }
  }

  if (isPressed(P1_RED) || isPressed(P2_RED)) {
    if (roundsNumber > 1) {
      roundsNumber --;
    }
  }

  if (isPressed(P1_GREEN) || isPressed(P2_GREEN)) {
    scene = GAME;
  }
}

void gameLoop() {

}

void overLoop() {
  lcd.clear();
  if (player1Score > player2Score) {
    lcd.print("   Winner: P1   ");
  }
  else if (player1Score < player2Score) {
    lcd.print("   Winner: P2   ");
  }
  else if (player1Score == player2Score) {
    lcd.print("       Tie      ");
  }
  lcd.print("  Continue (G)  ");
  if (isPressed(P1_GREEN) || isPressed(P2_GREEN)) {
    resetGame();
    scene = MAIN_MENU;
  }
}

void resetGame() {
  roundsPlayed = 0;
  player1Score = 0;
  player2Score = 0;  
}
