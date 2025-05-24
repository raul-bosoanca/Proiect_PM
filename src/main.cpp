#include <Arduino.h>
#include <screen.h>
#include <ir_sensor.h>
#include <led_strip.h>
#include <led_patterns.h>

unsigned int level = 1;
unsigned int time = 60;
unsigned int score = 0;

unsigned led_pattern_counter = 0;

volatile unsigned long last_interrupt_time = 0;
const unsigned long debounce_delay = 500; 

void setup() {
	i2c_init();
	lcd_init();
	ir_sensor_init();
	init_led_strip();
	sei();
}

void loop() {
	// lcd_time_update(time);
	lcd_time_update(score);
	time--;
	if (led_pattern_counter) {
		send_led_strip_pattern((uint8_t*)led_pattern_1, LED_PATTERN_1_LENGTH, 30);
		led_pattern_counter--;
	}
	delay(1000);
}

ISR(INT0_vect) {
  	unsigned long current_time = millis();
    if (current_time - last_interrupt_time > debounce_delay) {
    	score++;
		led_pattern_counter++;
    	last_interrupt_time = current_time;
  	}
}	