#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <avr/io.h>

#define SERVO_PIN                           PB2
#define SOFTWARE_ACTUATOR_PRESCALER_LVL4      5
#define SOFTWARE_ACTUATOR_PRESCALER_LVL5      2

void actuator_init();

void actuator_setLength(uint8_t length);

#endif // ACTUATOR_H