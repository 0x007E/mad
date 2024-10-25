
#define F_CPU 12000000UL
//#define WRITE_EEPROM

#include <avr/io.h>
#include <util/delay.h>

#include "../lib/matrix/matrix.h"

unsigned char buffer[(MATRIX_DISPLAYS * MATRIX_ROWS)];

int main(void)
{
    matrix_init();
    matrix_reset();
    _delay_ms(MATRIX_RESET_RECOVERY_TIME_MS);

    matrix_enable();

    #ifdef WRITE_EEPROM

    unsigned char temp[] = {
        0b00000001,
        0b00000011,
        0b00000111,
        0b00001111,
        0b00000111,
        0b00000011,
        0b00000001
    };

    matrix_buffer2eeprom(1, 0, temp);
    matrix_buffer2eeprom(2, 0, temp);

    temp[0] = 0b00010000;
    temp[1] = 0b00011000;
    temp[2] = 0b00011100;
    temp[3] = 0b00011110;
    temp[4] = 0b00011100;
    temp[5] = 0b00011000;
    temp[6] = 0b00010000;

    matrix_buffer2eeprom(1, 1, temp);
    matrix_buffer2eeprom(2, 1, temp);

    #endif

    unsigned char i=1;

    for (unsigned char y=0; y < (MATRIX_DISPLAYS * MATRIX_ROWS); y++)
    {

        for (unsigned char x=0; x < MATRIX_COLUMNS; x++)
        {
            if(i <= x)
            {
                break;
            }
            buffer[y] |= (1<<(i - 1));
        }

        if((++i) > MATRIX_COLUMNS)
        {
            i = 1;
        }
    }
    matrix_frame(buffer);
    _delay_ms(2000);

    unsigned int display_refresh_rate = MATRIX_STANDARD_DISPLAY_REFRESH_RATE;

    PORTA |= 0x0F;

    while (1)
    {
        matrix_char(1, 'A');
        _delay_ms(1000);
        matrix_char(2, 'B');
        _delay_ms(1000);
        matrix_clear(1);
        _delay_ms(1000);
        matrix_clear(2);
        _delay_ms(1000);
        matrix_char(1, 'A');
        _delay_ms(1000);
        matrix_char(2, 'B');
        _delay_ms(1000);
        matrix_clear_all();
        _delay_ms(1000);
        matrix_eeprom2buffer(1, 0);
        matrix_eeprom2buffer(2, 1);
        _delay_ms(1000);
        matrix_eeprom2buffer(1, 1);
        matrix_eeprom2buffer(2, 0);
        _delay_ms(1000);

        if(!(PINA & 0x01))
        {
            display_refresh_rate -= 100UL;
            matrix_display_refresh(1, display_refresh_rate);
        }
        else if(!(PINA & 0x02))
        {
            display_refresh_rate += 100UL;
            matrix_display_refresh(1, display_refresh_rate);
        }
    }
}

