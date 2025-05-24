#include <avr/io.h>

#define SERVO_PIN  PB2          // pin 10

void actuator_init(void)
{
    DDRB  |= _BV(SERVO_PIN);    // pin 10 output

    /* Timer-1: Fast-PWM mode 14, TOP = ICR1, presc 8 → 50 Hz */
    TCCR1A = _BV(COM1B1) | _BV(WGM11);          // OC1B non-inverting
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11);
    ICR1   = 40000;                             // 20 ms period
    OCR1B  = 3000;                              // 1.5 ms (centre)
}

void actuator_setLength(uint8_t angle)           // 0-180°
{
    OCR1B = 2000 + ((uint32_t)angle * 2000) / 180;
}
