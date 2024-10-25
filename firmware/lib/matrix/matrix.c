/* -----------------------------------------
* G.Raf^engineering
* www.sunriax.at
* -----------------------------------------
*    Platform: Megacard/STK500/STK600
*    Hardware: ATmega??-????
* -----------------------------------------
*     Version: 1.0 Release
*      Author: G.Raf
* Description:
*   Function file for matrix library
* -----------------------------------------
*/

#include "matrix.h"

void matrix_init()
{
    spi_init(SPI_Master, SPI_MSB, SPI_Rising, SPI_Rising);

    // Wait until display initialisation is complete
    _delay_ms(MATRIX_INIT_DELAY_MS);
}

static void matrix_command(unsigned char display, unsigned char operation, unsigned char data)
{
    if(display > MATRIX_DISPLAYS)
    {
        return;
    }

    spi_select(SPI_Enable);

    for (unsigned char i=MATRIX_DISPLAYS; i > 0; i--)
    {
        if(display == MATRIX_COMMAND_ALL_DISPLAYS || i == display)
        {
            spi_transfer(operation);
            _delay_us(MATRIX_TRANSFER_DELAY_US);
            spi_transfer(data);
            _delay_us(MATRIX_TRANSFER_DELAY_US);
        }
        else
        {
            spi_transfer(MATRIX_COMMAND_NOP);
            _delay_us(MATRIX_TRANSFER_DELAY_US);
            spi_transfer(MATRIX_COMMAND_NOP);
            _delay_us(MATRIX_TRANSFER_DELAY_US);
        }

    }
    spi_select(SPI_Disable);
}

void matrix_enable()
{
    matrix_command(
    MATRIX_COMMAND_ALL_DISPLAYS,
    MATRIX_COMMAND_DISPLAY_STATUS,
    MATRIX_COMMAND_DISPLAY_STATUS_ENABLE
    );
}

void matrix_disable()
{
    matrix_command(
    MATRIX_COMMAND_ALL_DISPLAYS,
    MATRIX_COMMAND_DISPLAY_STATUS,
    MATRIX_COMMAND_DISPLAY_STATUS_DISABLE
    );
}

void matrix_reset()
{
    matrix_command(
    MATRIX_COMMAND_ALL_DISPLAYS,
    MATRIX_COMMAND_DISPLAY_RESET,
    MATRIX_COMMAND_DISPLAY_RESET
    );
}

void matrix_data(unsigned char display, unsigned char* buffer)
{
    for(unsigned char i=1; i <= MATRIX_ROWS; i++)
    {
        matrix_command(
        display,
        i,
        buffer[(i - 1)]
        );
    }

}

void matrix_frame(unsigned char* buffer)
{
    for (unsigned char y=MATRIX_ROWS; y > 0; y--)
    {
        spi_select(SPI_Enable);

        for (unsigned char x=MATRIX_DISPLAYS; x > 0; x--)
        {
            spi_transfer(y);
            _delay_us(10);
            spi_transfer(buffer[(((x - 1) * MATRIX_ROWS) + (y - 1))]);
            _delay_us(10);
        }
        spi_select(SPI_Disable);
    }
}

void matrix_char(unsigned char display, char character)
{
    matrix_command(display, MATRIX_COMMAND_DISPLAY_CHAR, (unsigned char)(character));
}

void matrix_clear(unsigned char display)
{
    matrix_command(display, MATRIX_COMMAND_DISPLAY_CLEAR, 0x00);
}

void matrix_clear_all()
{
    for (unsigned char x=1; x <= MATRIX_DISPLAYS; x++)
    {
        matrix_clear(x);
        _delay_ms(MATRIX_CLEAR_RECOVERY_TIME_MS);
    }
}

void matrix_buffer2eeprom(unsigned char display, unsigned char address, unsigned char* buffer)
{
    if((display == 0) || (display > MATRIX_DISPLAYS) || (address >= MATRIX_EEPROM_SIZE))
    {
        return;
    }

    matrix_data(display, buffer);
    matrix_command(
    display,
    (MATRIX_COMMAND_EEPROM_WRITE_START_ADDRESS + address),
    (MATRIX_COMMAND_EEPROM_WRITE_START_ADDRESS + address)
    );
    _delay_ms(MATRIX_EEPROM_WRITE_RECOVERY_TIME_MS);
}

void matrix_eeprom2buffer(unsigned char display, unsigned char address)
{
    matrix_command(
    display,
    (MATRIX_COMMAND_EEPROM_READ_START_ADDRESS + address),
    (MATRIX_COMMAND_EEPROM_READ_START_ADDRESS + address)
    );
}

void matrix_display_refresh(unsigned char display, unsigned int rate)
{
    if((display == 0) || (display > MATRIX_DISPLAYS))
    {
        return;
    }

    matrix_command(
    display,
    MATRIX_COMMAND_DISPLAY_REFRESH_RATE_LOW,
    (unsigned char)(rate)
    );
    
    matrix_command(
    display,
    MATRIX_COMMAND_DISPLAY_REFRESH_RATE_HIGH,
    (unsigned char)(rate>>8)
    );
}