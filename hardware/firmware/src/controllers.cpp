#include "controllers.h"

#include <Arduino.h>

#include "config.h"

float PositionLoop::update(float x, float x_dot) {
  const float error = -x;

  if (fabsf(error) < cfg::POS_INTEGRAL_ZONE_M) {
    integral_ += error * cfg::LOOP_DT_S;
    integral_ = constrain(integral_, -cfg::POS_INTEGRAL_LIMIT, cfg::POS_INTEGRAL_LIMIT);
  } else {
    integral_ = 0.0f;
  }

  const float target = cfg::POS_KP * error + cfg::POS_KI * integral_ - cfg::POS_KD * x_dot;
  return constrain(target, -cfg::MAX_TARGET_ANGLE_RAD, cfg::MAX_TARGET_ANGLE_RAD);
}

float AnglePid::update(float angle, float angular_velocity, float target_angle) {
  const float error = target_angle - angle;

  integral_ += error * cfg::LOOP_DT_S;
  integral_ = constrain(integral_, -cfg::ANGLE_INTEGRAL_LIMIT, cfg::ANGLE_INTEGRAL_LIMIT);

  const float output = cfg::ANGLE_KP * error + cfg::ANGLE_KI * integral_ - cfg::ANGLE_KD * angular_velocity;
  return constrain(output, -1.0f, 1.0f);
}
