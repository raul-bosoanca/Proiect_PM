#include <Arduino.h>
#include <screen.h>
#include <stdlib.h>

unsigned int level = 1;
unsigned int time = 60;
unsigned int score = 0;
char buffer[20];

void setup() {
	i2c_init();
	lcd_init();
}

void loop() {
	itoa(time, buffer, 10);
	lcd_overwrite(6, 0, buffer);
	time--;
	delay(1000);
}