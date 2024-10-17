#include <Arduino.h>
#include "relay_control.h"
#include "config.h"

void RelayControl::openA() {
  openP();
  delay(1);
  digitalWrite(relay_A, HIGH);
  delay(1);
  digitalWrite(relay_B, LOW);
}


void RelayControl::openB() {
  openP();
  delay(1);
  digitalWrite(relay_B, HIGH);
  delay(1);
  digitalWrite(relay_A, LOW);
}

void RelayControl::openP() {
  digitalWrite(relay_P, LOW);
}

void RelayControl::closeP() {
  digitalWrite(relay_P, HIGH);
}

void RelayControl::disable() {
  digitalWrite(relay_A, HIGH);
  digitalWrite(relay_B, HIGH);
  digitalWrite(relay_P, HIGH);
}