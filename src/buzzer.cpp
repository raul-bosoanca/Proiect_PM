#include <buzzer.h>

void buzzer_init() {
    DDRB |= (1 << BUZZER_PIN); // Set as output
    playStartSound();
}

void playTone(long frequency, int duration) {
    const int32_t delay_us = 1000000UL / (frequency * 2); // half-period
    uint32_t cycles = (uint32_t)frequency * duration / 1000;

    for (uint32_t i = 0; i < cycles; i++) {
        PORTB |= (1 << BUZZER_PIN);   // HIGH
        for (int i = 0; i < delay_us; i++) {
            _delay_us(1);
        }
        PORTB &= ~(1 << BUZZER_PIN);  // LOW
        for (int i = 0; i < delay_us; i++) {
            _delay_us(1);
        }
    }
}

void playStartSound() {
    playTone(440, 100);
    playTone(494, 100);
    playTone(523, 100);
    playTone(659, 100);
    playTone(784, 150);
    _delay_ms(100);
    playTone(880, 120);
    playTone(988, 120);
    playTone(1047, 180);
}

void playGameOverSound() {
    playTone(523, 200);
    playTone(494, 200);
    playTone(440, 300);
    _delay_ms(100);
    playTone(392, 150);
    playTone(349, 150);
    playTone(311, 300);
    _delay_ms(100);
    playTone(262, 400);
}

void playScoreSound() {
    playTone(261, 150);
    playTone(330, 150);
    playTone(392, 200);
}