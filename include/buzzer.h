#ifndef BUZZER_H
#define BUZZER_H

#define BUZZER_PIN PB0

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void startTone(long frequency);

void stopTone();

void playStartSound();

void playGameOverSound();

void playScoreSound();

void buzzer_init();

#endif // BUZZER_H