#include <ir_sensor.h>

void ir_sensor_init() {
    DDRD &= ~(1 << PD2);
    EICRA |= (1 << ISC01) | (1 << ISC00);
    EIMSK |= (1 << INT0); 
}