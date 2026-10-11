#pragma once

namespace stepper {

void begin();
void run();
void command(float throttle);
void stop();
float velocity();

}  // namespace stepper
