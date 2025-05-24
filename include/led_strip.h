#ifndef LED_STRIP_H
#define LED_STRIP_H

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN 6

void led_strip_init();

void sendBit(bool bitVal);
void sendByte(uint8_t byte);
void sendColor(uint8_t red, uint8_t green, uint8_t blue);


/**
 * @brief Sends a pattern of colors to the LED strip with a specified speed.
 *
 * This function transmits an array of color values to the LED strip, allowing for dynamic
 * patterns or effects. The speed parameter controls how quickly the pattern is displayed.
 *
 * @param colors Pointer to an array of color values (typically RGB or GRB format).
 * @param length Number of color values in the array.
 * @param speed Speed at which the pattern should be sent or displayed.
 */
void send_led_strip_pattern(uint8_t* colors, uint16_t length, uint8_t speed); 

#endif // LED_STRIP_H