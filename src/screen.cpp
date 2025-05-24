#include <screen.h>
#include <stdlib.h>

/* Screen comm functions */

void pcf8574_write(uint8_t data) {
    i2c_start();
    i2c_write(I2C_ADDR << 1);
    i2c_write(data);
    i2c_stop();
}

void pulse_enable(uint8_t data) {
    pcf8574_write(data | LCD_EN);
    _delay_us(1);
    pcf8574_write(data & (~LCD_EN));
    _delay_us(50);
}

void send_nibble(uint8_t nibble, uint8_t control) {
    uint8_t temp;
    temp = (nibble << 4) | control | LCD_BACKLIGHT;
    pulse_enable(temp);
}

void send_byte(uint8_t value, uint8_t isData) {
    uint8_t ctrl;
    if (isData) {
        ctrl = LCD_RS;
    } else {
        ctrl = 0;
    }
    send_nibble(value >> 4, ctrl);
    send_nibble(value & 0x0F, ctrl);
}

void lcd_command(uint8_t cmd) {
    send_byte(cmd, 0);
    if (cmd <= 3) {
        _delay_ms(5);
    }
}

void lcd_write_char(char c) {
    send_byte(c, 1);
}

/* Logic for display upate */

void lcd_set_cursor(uint8_t col, uint8_t row) {
    uint8_t addr;
    if (row == 0) {
        addr = 0x00;
    } else {
        addr = 0x40;
    }
    lcd_command(0x80 | (col + addr));
}

void lcd_print(const char* str) {
    while (*str != 0) {
        lcd_write_char(*str);
        str++;
    }
}

void lcd_overwrite(uint8_t col, uint8_t row, const char* str) {
    lcd_set_cursor(col, row);
    lcd_print(str);
}

void lcd_init() {
    _delay_ms(50);
    send_nibble(0x03, 0);
    _delay_ms(5);
    send_nibble(0x03, 0);
    _delay_us(150);
    send_nibble(0x03, 0);
    _delay_us(150);
    send_nibble(0x02, 0);

    lcd_command(0x28);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_command(0x01);
    _delay_ms(2);

    lcd_set_cursor(0, 0);
    lcd_print("Time: 60s  Level");
    lcd_set_cursor(0, 1);
    lcd_print("Score: 0     1 ");
}

void lcd_time_update(unsigned int time) {
    char buffer[20];
    buffer[0] = '0';
    if (time < 10) {
       itoa(time, buffer + 1, 10); 
    } else{
        itoa(time, buffer, 10);
    }
	lcd_overwrite(6, 0, buffer);
}

void lcd_score_update(unsigned int score) {
    char buffer[20];
    itoa(score, buffer, 10);
	lcd_overwrite(7, 1, buffer);
}

void lcd_level_update(unsigned int level) {
    char buffer[20];
    itoa(level, buffer, 10);
	lcd_overwrite(13, 1, buffer);
}