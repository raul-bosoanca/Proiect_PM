#ifndef SCREEN_H
#define SCREEN_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>

// #define F_CPU                                                                           16000000UL
#define I2C_SCL_FREQ                                                                      100000UL
#define I2C_PRESCALER                                                                            1
#define TWBR_VALUE                           (((F_CPU / I2C_SCL_FREQ) - 16) / (2 * I2C_PRESCALER))

#define I2C_ADDR                                                                              0x27
#define LCD_RS                                                                                0x01
#define LCD_RW                                                                                0x02
#define LCD_EN                                                                                0x04
#define LCD_BACKLIGHT                                                                         0x08

/* I2C comm functions */
inline void i2c_init() {
    TWSR = 0x00;
    TWBR = (uint8_t)TWBR_VALUE;
    TWCR = (1 << TWEN);
}

inline void i2c_wait() {
    while (!(TWCR & (1 << TWINT))) {}
}

inline void i2c_start() {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    i2c_wait();
}

inline void i2c_stop() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

inline void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    i2c_wait();
}

/* Screen comm functions */
void pcf8574_write(uint8_t data);
void pulse_enable(uint8_t data);
void send_nibble(uint8_t nibble, uint8_t control);
void send_byte(uint8_t value, uint8_t isData);
void lcd_command(uint8_t cmd);
void lcd_write_char(char c);
void lcd_init();
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_print(const char* str);
void lcd_overwrite(uint8_t col, uint8_t row, const char* str);

#endif // SCREEN_H
