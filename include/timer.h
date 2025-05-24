#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define SOFTWARE_TIMER_PRESCALER          500

void timer_init(void);

#endif // TIMER_H