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

LiquidCrystal_I2C lcd(0x3F, 16, 2);

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
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  
  scene = MAIN_MENU;
  randomSeed(analogRead(0));
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
  lcd.setCursor(0, 0);
  lcd.print("      LFn't     ");
  lcd.setCursor(0, 1);
  lcd.print("    Start (G)   ");
  if (isPressed(P1_GREEN) || isPressed(P2_GREEN)) {
    scene = PRE_GAME;
    while(isPressed(P1_GREEN) || isPressed(P2_GREEN)) {}
  }
}

void preLoop() {
  lcd.setCursor(0, 0);
  lcd.print("   Rounds (G)   ");
  lcd.setCursor(0, 1);
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
    while (isPressed(P1_BLUE) || isPressed(P2_BLUE)) {}
  }

  if (isPressed(P1_RED) || isPressed(P2_RED)) {
    if (roundsNumber > 1) {
      roundsNumber --;
    }
    while (isPressed(P1_RED) || isPressed(P2_RED)) {}
  }

  if (isPressed(P1_GREEN) || isPressed(P2_GREEN)) {
    scene = GAME;
    while (isPressed(P1_GREEN) || isPressed(P2_GREEN)) {}
  }
}

void gameLoop() {
  if (roundsPlayed >= roundsNumber) {
    scene = GAME_OVER;
    return;
  }

  int color = random(4);
  int led = LED_RED;
  int buttonP1 = P1_RED;
  int buttonP2 = P2_RED;
  int valP1;
  int valP2;
  switch (color) {
    case 0:
      led = LED_RED;
      buttonP1 = P1_RED;
      buttonP2 = P2_RED;
      break;
    case 1:
      led = LED_GREEN;
      buttonP1 = P1_GREEN;
      buttonP2 = P2_GREEN;
      break;
    case 2:
      led = LED_BLUE;
      buttonP1 = P1_BLUE;
      buttonP2 = P2_BLUE;
      break;
    case 3:
      led = LED_YELLOW;
      buttonP1 = P1_YELLOW;
      buttonP2 = P2_YELLOW;
      break;
  }

  lcd.setCursor(0, 0);
  lcd.print("   Round: ");
  char buf[4];
  itoa(roundsPlayed+1, buf, 10);
  lcd.print(buf);
  lcd.print("      ");

  lcd.setCursor(0, 1);
  lcd.print("                ");

  delay(1000);
  lcd.setCursor(8, 1);
  lcd.print("3");
  delay(1000);
  lcd.setCursor(8, 1);
  lcd.print("2");
  delay(1000);
  lcd.setCursor(8, 1);
  lcd.print("1");
  delay(1000);
  lcd.setCursor(5, 1);
  lcd.print("Press!");

  digitalWrite(led, HIGH);

  while ( (valP1 = digitalRead(buttonP1)) == HIGH && (valP2 = digitalRead(buttonP2)) == HIGH ) {}

  if (valP1 == LOW) {
    player1Score ++;
  }
  if (valP2 == LOW) {
    player2Score ++;
  }

  digitalWrite(led, LOW);

  while (isPressed(buttonP1) || isPressed(buttonP2)) {}  

  roundsPlayed ++;
}

void overLoop() {
  lcd.setCursor(0, 0);
  if (player1Score > player2Score) {
    lcd.print("   Winner: P1   ");
  }
  else if (player1Score < player2Score) {
    lcd.print("   Winner: P2   ");
  }
  else if (player1Score == player2Score) {
    lcd.print("       Tie      ");
  }
  lcd.setCursor(0, 1);
  lcd.print("  Continue (G)  ");
  if (isPressed(P1_GREEN) || isPressed(P2_GREEN)) {
    resetGame();
    scene = MAIN_MENU;
    while (isPressed(P1_GREEN) || isPressed(P2_GREEN)) {}
  }
}

void resetGame() {
  roundsPlayed = 0;
  player1Score = 0;
  player2Score = 0;  
}
