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
}

void loop() {


}
