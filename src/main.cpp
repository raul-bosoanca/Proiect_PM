#include <Arduino.h>
#include <screen.h>
#include <ir_sensor.h>
#include <led_strip.h>
#include <led_patterns.h>
#include <buzzer.h>
#include <timer.h>
#include <actuator.h>

unsigned int level = 1;
unsigned int time = 60;
unsigned int score = 0;
int time_counter = 0;

unsigned led_pattern_counter = 0;

volatile unsigned long last_interrupt_time = 0;
const unsigned long debounce_delay = 500;

int lenght = 30;
int direction = 1;

void setup() {
	buzzer_init();
	i2c_init();
	lcd_init();
	ir_sensor_init();
	led_strip_init();
	timer_init();
	actuator_init();
	sei();
}

void loop() {
	if (led_pattern_counter) {
		send_led_strip_pattern((uint8_t*)led_pattern_1, LED_PATTERN_1_LENGTH, 30);
		led_pattern_counter--;
		playScoreSound();
	}
	if (level == 6) {
		playGameOverSound();
		lcd_overwrite(0, 0, "Game Over!       ");
		lcd_overwrite(0, 1, "Final Score: ");
		lcd_level_update(score);
		cli();
		while (1);
	}
}

ISR(INT0_vect) {
  	unsigned long current_time = millis();
    if (current_time - last_interrupt_time > debounce_delay) {
    	score++;
		led_pattern_counter++;
    	last_interrupt_time = current_time;
  	}
}

ISR(TIMER2_COMPA_vect)
{
	if (level >= 6) {
		return;
	}
	++time_counter;
	if (level == 4 && time_counter % SOFTWARE_ACTUATOR_PRESCALER_LVL4 == 0
		|| level == 5 && time_counter % SOFTWARE_ACTUATOR_PRESCALER_LVL5 == 0) 
	{
		actuator_setLength(lenght);
		lenght += direction;
		if (lenght >= 150) direction = -1;
		else if (lenght <= 30) direction = 1;
	}

	if (time_counter % SOFTWARE_TIMER_PRESCALER) {
		return;
	}
	
	time_counter = 0;
	time--;
    if (time == 0) {
		lcd_level_update(++level);
		if (level == 6) {
			return;
		}
		time = 60;
	}
	lcd_time_update(time);
	lcd_score_update(score);
}