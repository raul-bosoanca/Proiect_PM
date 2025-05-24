#include <led_strip.h>
#include <avr/interrupt.h>

void init_led_strip() {
    DDRD |= (1 << PD6);
    PORTD &= ~(1 << PD6); 
}

void sendBit(bool bitVal) {
    if (bitVal) {
        PORTD |= (1 << PD6);
        asm volatile(
            "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
        );
        PORTD &= ~(1 << PD6);
        asm volatile(
            "nop\n\t""nop\n\t""nop\n\t""nop\n\t"
        );
    } else {
        PORTD |= (1 << PD6);
        asm volatile(
            "nop\n\t""nop\n\t""nop\n\t"
        );
        PORTD &= ~(1 << PD6);
        asm volatile(
            "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
        );
    }
}

void sendByte(uint8_t byte) {
    for (int i = 7; i >= 0; i--) {
        bool bitVal = byte & (1 << i);
        sendBit(bitVal);
    }
}

void sendColor(uint8_t red, uint8_t green, uint8_t blue) {
    sendByte(green);
    sendByte(red);
    sendByte(blue);
}

void send_led_strip_pattern(uint8_t* colors, uint16_t length, uint8_t speed) {
    for (uint16_t i = 0; i < length * 24; i += 3) {
        cli();
        sendColor(colors[i] / 25, colors[i + 1] / 25, colors[i + 2] / 25);
        if (i % 24 == 21) {
            sei();
            PORTD &= ~(1 << PD6);
            _delay_us(50);
            _delay_ms(1000 / speed);
        }
    }
}
