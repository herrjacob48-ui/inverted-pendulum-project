#include <Arduino.h>

#include "config.h"
#include "controllers.h"
#include "encoder.h"
#include "filter.h"
#include "stepper.h"

namespace {

AnglePid angle_pid;
PositionLoop position_loop;
Ema theta_dot_filter(cfg::THETA_DOT_ALPHA);
Ema x_dot_filter(cfg::X_DOT_ALPHA);

float x = 0.0f;
float last_theta = 0.0f;
unsigned long last_loop_us = 0;

void shut_down() {
  stepper::stop();
  angle_pid.reset();
  position_loop.reset();
}

void log_telemetry(float target_angle, float theta, float throttle) {
  static int counter = 0;
  if (counter++ % cfg::TELEMETRY_DIVIDER == 0) {
    Serial.printf("X: %5.3fm | Tar_Ang: %4.1f | Ang: %5.1f deg | Throttle: %5.2f\n",
                  x, degrees(target_angle), degrees(theta), throttle);
  }
}

void control_step() {
  const float theta = (encoder::read() * cfg::RADIANS_PER_TICK) * cfg::ANGLE_SIGN;
  const float theta_dot = theta_dot_filter.update((theta - last_theta) / cfg::LOOP_DT_S);
  last_theta = theta;

  const float x_dot = stepper::velocity();
  x += x_dot * cfg::LOOP_DT_S;
  const float x_dot_smooth = x_dot_filter.update(x_dot);

  const float target_angle = position_loop.update(x, x_dot_smooth);
  const float throttle = angle_pid.update(theta, theta_dot, target_angle);

  if (fabsf(theta) > cfg::MAX_TILT_RAD) {
    shut_down();
    Serial.printf("CRASH SHUTDOWN: Angle Over 30 Deg! (%.2f)\n", degrees(theta));
  } else if (fabsf(x) > cfg::TRACK_LIMIT_M) {
    shut_down();
    Serial.printf("CRASH SHUTDOWN: Track Edge Breach! (%.2fm)\n", x);
  } else {
    stepper::command(throttle);
    log_telemetry(target_angle, theta, throttle);
  }
}

}  // namespace

void setup() {
  Serial.begin(115200);
  delay(1000);

  stepper::begin();
  encoder::begin();

  Serial.println("--- Cascaded Core PID Balance & Position Firmware Active ---");
  last_loop_us = micros();
}

void loop() {
  stepper::run();

  const unsigned long now = micros();
  if (now - last_loop_us >= cfg::LOOP_PERIOD_US) {
    last_loop_us = now;
    control_step();
  }
}
