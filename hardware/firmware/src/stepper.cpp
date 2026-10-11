#include "stepper.h"

#include <Arduino.h>

#include "config.h"

namespace stepper {
namespace {

float speed_hz = 0.0f;
float velocity_mps = 0.0f;
int direction = 1;
bool step_level = false;
unsigned long last_step_us = 0;

float slew(float current, float target, float max_step) {
  if (target > current + max_step) return current + max_step;
  if (target < current - max_step) return current - max_step;
  return target;
}

}  // namespace

void begin() {
  pinMode(cfg::STEP_PIN, OUTPUT);
  pinMode(cfg::DIR_PIN, OUTPUT);
  digitalWrite(cfg::STEP_PIN, LOW);
  digitalWrite(cfg::DIR_PIN, LOW);
}

void command(float throttle) {
  if (fabsf(throttle) < cfg::THROTTLE_DEADBAND) {
    speed_hz = 0.0f;
    velocity_mps = 0.0f;
    return;
  }

  direction = (throttle > 0) ? 1 : -1;
  digitalWrite(cfg::DIR_PIN, direction == 1 ? LOW : HIGH);

  float target_hz = fabsf(throttle) * cfg::FULL_THROTTLE_HZ;
  if (target_hz < cfg::MIN_SPEED_HZ) target_hz = cfg::MIN_SPEED_HZ;

  speed_hz = slew(speed_hz, target_hz, cfg::MAX_ACCEL_HZ);
  velocity_mps = cfg::VELOCITY_SIGN * (speed_hz / cfg::STEPS_PER_METER) * direction;
}

void stop() {
  speed_hz = 0.0f;
  digitalWrite(cfg::STEP_PIN, LOW);
}

float velocity() { return velocity_mps; }

void run() {
  if (speed_hz < cfg::MIN_STEP_RATE_HZ) return;

  const unsigned long now = micros();
  const unsigned long half_period_us = 500000.0f / speed_hz;
  if (now - last_step_us >= half_period_us) {
    last_step_us = now;
    step_level = !step_level;
    digitalWrite(cfg::STEP_PIN, step_level);
  }
}

}  // namespace stepper
