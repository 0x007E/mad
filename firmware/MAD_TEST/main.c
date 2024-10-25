
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "../lib/spi/spi.h"

int main(void)
{
    DDRC = 0xFF;

    spi_init(SPI_Master, SPI_MSB, SPI_Rising, SPI_Rising);
    _delay_ms(2000);

    spi_select(SPI_Enable);
    for (unsigned char i=1; i <= 10; i++)
    {
        spi_transfer(0xFF);
        _delay_us(100);
    }
    spi_select(SPI_Disable);

    spi_select(SPI_Enable);
    spi_transfer(0x1F);
    _delay_us(100);
    spi_transfer(0x01);
    _delay_us(100);
    spi_transfer(0x1F);
    _delay_us(100);
    spi_transfer(0x01);
    _delay_us(100);
    spi_select(SPI_Disable);

    while (1) 
    {

        PORTC ^= 0xFF;

        for (unsigned char i=1; i <= 7; i++)
        {
            spi_select(SPI_Enable);
            spi_transfer(i);
            _delay_us(100);
            spi_transfer(0xFF);
            _delay_us(100);
            spi_transfer((8 - i));
            _delay_us(100);
            spi_transfer(0xFF);
            _delay_us(100);
            spi_select(SPI_Disable);
            _delay_ms(250);
        }
        _delay_ms(1000);
        
        spi_select(SPI_Enable);
        for (unsigned char i=1; i <= 10; i++)
        {
            spi_transfer(0xFF);
            _delay_us(100);
        }
        spi_select(SPI_Disable);
        _delay_ms(1);

        spi_select(SPI_Enable);
        spi_transfer(0x10);
        _delay_us(100);
        spi_transfer(0x00);
        _delay_us(100);
        spi_transfer(0x10);
        _delay_us(100);
        spi_transfer(0x00);
        _delay_us(100);
        spi_select(SPI_Disable);
        _delay_ms(1);

        spi_select(SPI_Enable);
        spi_transfer(0x08);
        _delay_us(100);
        spi_transfer('B');
        _delay_us(100);
        spi_transfer(0x08);
        _delay_us(100);
        spi_transfer('A');
        _delay_us(100);
        spi_select(SPI_Disable);
        _delay_ms(4000);

        spi_select(SPI_Enable);
        spi_transfer(0x10);
        _delay_us(100);
        spi_transfer(0x00);
        _delay_us(100);
        spi_transfer(0x10);
        _delay_us(100);
        spi_transfer(0x00);
        _delay_us(100);
        spi_select(SPI_Disable);
        _delay_ms(1);
    }
}

