/* -----------------------------------------
 * G.Raf^engineering
 * www.sunriax.at
 * -----------------------------------------
 *    Platform: Megacard/STK500/STK600
 *    Hardware: ATmega16A
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *   Header file for matrix library
 * -----------------------------------------
 */

#ifndef MATRIX_H_
    #define MATRIX_H_

    #ifndef F_CPU
        #define F_CPU 12000000UL
    #endif

    #ifndef MATRIX_DISPLAYS
        #define MATRIX_DISPLAYS 2
    #endif

    #ifndef MATRIX_ROWS
        #define MATRIX_ROWS 7
    #endif

    #ifndef MATRIX_EEPROM_SIZE
        #define MATRIX_EEPROM_SIZE 16
    #endif

    #ifndef MATRIX_COLUMNS
        #define MATRIX_COLUMNS 5
    #endif

    #ifndef MATRIX_INIT_DELAY_MS
        #define MATRIX_INIT_DELAY_MS 2000
    #endif

    #ifndef MATRIX_TRANSFER_DELAY_US
        #define MATRIX_TRANSFER_DELAY_US 100
    #endif

    #ifndef MATRIX_RESET_RECOVERY_TIME_MS
        #define MATRIX_RESET_RECOVERY_TIME_MS 100
    #endif

    #ifndef MATRIX_CLEAR_RECOVERY_TIME_MS
        #define MATRIX_CLEAR_RECOVERY_TIME_MS 10
    #endif

    #ifndef MATRIX_EEPROM_WRITE_RECOVERY_TIME_MS
        #define MATRIX_EEPROM_WRITE_RECOVERY_TIME_MS 100
    #endif

    #ifndef MATRIX_COMMAND_NOP
        #define MATRIX_COMMAND_NOP 0x00
    #endif
    
    #ifndef MATRIX_COMMAND_DISPLAY_CHAR
        #define MATRIX_COMMAND_DISPLAY_CHAR 0x08
    #endif

    #ifndef MATRIX_COMMAND_DISPLAY_CLEAR
        #define MATRIX_COMMAND_DISPLAY_CLEAR 0x10
    #endif

    #ifndef MATRIX_COMMAND_DISPLAY_STATUS
        #define MATRIX_COMMAND_DISPLAY_STATUS 0x1F

        #define MATRIX_COMMAND_DISPLAY_STATUS_ENABLE 0x01
        #define MATRIX_COMMAND_DISPLAY_STATUS_DISABLE 0x00
    #endif
    
    #ifndef MATRIX_COMMAND_EEPROM_READ_START_ADDRESS
        #define MATRIX_COMMAND_EEPROM_READ_START_ADDRESS 0x20
    #endif

    #ifndef MATRIX_COMMAND_EEPROM_WRITE_START_ADDRESS
        #define MATRIX_COMMAND_EEPROM_WRITE_START_ADDRESS 0x30
    #endif

    #ifndef MATRIX_COMMAND_DISPLAY_REFRESH_RATE_LOW
        #define MATRIX_COMMAND_DISPLAY_REFRESH_RATE_LOW 0xF0
    #endif

    #ifndef MATRIX_COMMAND_DISPLAY_REFRESH_RATE_HIGH
        #define MATRIX_COMMAND_DISPLAY_REFRESH_RATE_HIGH 0xF1
    #endif

    #ifndef MATRIX_COMMAND_DISPLAY_RESET
        #define MATRIX_COMMAND_DISPLAY_RESET 0xFF
    #endif

    #ifndef MATRIX_COMMAND_ALL_DISPLAYS
        #define MATRIX_COMMAND_ALL_DISPLAYS 0
    #endif
    
    #ifndef MATRIX_STANDARD_DISPLAY_REFRESH_RATE
        #define MATRIX_STANDARD_DISPLAY_REFRESH_RATE 0x0B29
    #endif

    #include <avr/io.h>
    #include <util/delay.h>

    #include "../../lib/spi/spi.h"

    void matrix_init(void);
    void matrix_enable(void);
    void matrix_disable(void);
    void matrix_reset(void);
    void matrix_data(unsigned char display, unsigned char* buffer);
    void matrix_frame(unsigned char* buffer);
    void matrix_char(unsigned char display, char character);
    void matrix_clear(unsigned char display);
    void matrix_clear_all(void);
    void matrix_buffer2eeprom(unsigned char display, unsigned char address, unsigned char* buffer);
    void matrix_eeprom2buffer(unsigned char display, unsigned char address);
    void matrix_display_refresh(unsigned char display, unsigned int rate);
#endif /* MATRIX_H_ */