#include <avr/io.h>
#include <avr/interrupt.h>

void timer_init(void) {
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2  = 0;

    OCR2A  = 0xFF;

    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22);
    TCCR2B |= (1 << CS20);
    TIMSK2 |= (1 << OCIE2A);
}
