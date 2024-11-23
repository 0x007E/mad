
#define F_CPU 12000000UL
#define NUMBER_OF_DISPLAYS 2

#include <avr/io.h>
#include <util/delay.h>

#include "../lib/spi/spi.h"

int main(void)
{
    // Set all LEDs to output
    DDRC = 0xFF;

    spi_init(SPI_Master, SPI_MSB, SPI_Rising, SPI_Rising);
    _delay_ms(2000);

    // Reset displays
    spi_select(SPI_Enable);
    for (unsigned char i=1; i <= (NUMBER_OF_DISPLAYS * 2UL); i++)
    {
        spi_transfer(0xFF);
        _delay_us(100);
    }
    spi_select(SPI_Disable);

    // Enable all displays
    spi_select(SPI_Enable);
    for (unsigned char i=0; i < NUMBER_OF_DISPLAYS; i++)
    {
        spi_transfer(0x1F);
        _delay_us(100);
        spi_transfer(0x01);
        _delay_us(100);
    }
    spi_select(SPI_Disable);

    while (1) 
    {
        // Toggle LEDs
        PORTC ^= 0xFF;

        for (unsigned char y=1; y <= 7; y++)
        {
            spi_select(SPI_Enable);
            for (unsigned char i=0; i < NUMBER_OF_DISPLAYS; i++)
            {
                if((i%2))
                {
                    spi_transfer(y);
                }
                else
                {
                    spi_transfer((8 - i));
                }
                _delay_us(100);
                spi_transfer(0xFF);
                _delay_us(100);
            }
            spi_select(SPI_Disable);
            _delay_ms(250);
        }
        _delay_ms(1000);

        // Clear buffer of all displays
        spi_select(SPI_Enable);
        for (unsigned char i=0; i < NUMBER_OF_DISPLAYS; i++)
        {
            spi_transfer(0x10);
            _delay_us(100);
            spi_transfer(0x00);
            _delay_us(100);
        }
        spi_select(SPI_Disable);
        _delay_ms(1);

        // Show an ASCII character on displays
        spi_select(SPI_Enable);
        for (unsigned char i=0; i < NUMBER_OF_DISPLAYS; i++)
        {
            spi_transfer(0x08);
            _delay_us(100);
            spi_transfer('A');
            _delay_us(100);
        }
        spi_select(SPI_Disable);
        _delay_ms(1000);
    }
}

