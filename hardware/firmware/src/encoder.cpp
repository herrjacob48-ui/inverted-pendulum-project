#include "encoder.h"

#include <Arduino.h>

#include "config.h"

namespace encoder {
namespace {

volatile long ticks = 0;

void IRAM_ATTR on_edge() {
  const int a = digitalRead(cfg::ENCODER_A_PIN);
  const int b = digitalRead(cfg::ENCODER_B_PIN);
  ticks += (a != b) ? 1 : -1;
}

}  // namespace

void begin() {
  pinMode(cfg::ENCODER_A_PIN, INPUT);
  pinMode(cfg::ENCODER_B_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(cfg::ENCODER_A_PIN), on_edge, CHANGE);
  ticks = 0;
}

long read() {
  noInterrupts();
  const long value = ticks;
  interrupts();
  return value;
}

}  // namespace encoder
