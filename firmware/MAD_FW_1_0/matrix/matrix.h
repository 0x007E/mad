/* -----------------------------------------
 * G.Raf^engineering
 * www.sunriax.at (github.com/0x007e)
 * -----------------------------------------
 *    Platform: Independent
 *    Hardware: ATTiny406/1606/...
 * -----------------------------------------
 *     Version: 1.0 Release
 *      Author: G.Raf
 * Description:
 *	Header for initializing matrix display
 * -----------------------------------------
 */

#ifndef MATRIX_H_
#define MATRIX_H_

    #ifndef F_CPU
        #define F_CPU 20000000UL
    #endif

    #ifndef MATRIX_PINB_DR1
        #define MATRIX_PINB_DR1 PIN0_bm
        #define MATRIX_PINB_DR1_CTRL PIN0CTRL
    #endif

    #ifndef MATRIX_PINC_DR2
        #define MATRIX_PINC_DR2 PIN3_bm
        #define MATRIX_PINC_DR2_CTRL PIN3CTRL
    #endif

    #ifndef MATRIX_PINC_DR3
        #define MATRIX_PINC_DR3 PIN0_bm
        #define MATRIX_PINC_DR3_CTRL PIN0CTRL
    #endif

    #ifndef MATRIX_PINB_DR4
        #define MATRIX_PINB_DR4 PIN3_bm
        #define MATRIX_PINB_DR4_CTRL PIN3CTRL
    #endif

    #ifndef MATRIX_PINA_DR5
        #define MATRIX_PINA_DR5 PIN7_bm
        #define MATRIX_PINA_DR5_CTRL PIN7CTRL
    #endif

    #ifndef MATRIX_PINB_DR6
        #define MATRIX_PINB_DR6 PIN1_bm
        #define MATRIX_PINB_DR6_CTRL PIN1CTRL
    #endif
    
    #ifndef MATRIX_PINA_DR7
        #define MATRIX_PINA_DR7 PIN6_bm
        #define MATRIX_PINA_DR7_CTRL PIN6CTRL
    #endif

    #ifndef MATRIX_PINC_DC1
        #define MATRIX_PINC_DC1 PIN2_bm
        #define MATRIX_PINC_DC1_CTRL PIN2CTRL
    #endif

    #ifndef MATRIX_PINB_DC2
        #define MATRIX_PINB_DC2 PIN5_bm
        #define MATRIX_PINB_DC2_CTRL PIN5CTRL
    #endif
    
    #ifndef MATRIX_PINB_DC3
        #define MATRIX_PINB_DC3 PIN4_bm
        #define MATRIX_PINB_DC3_CTRL PIN4CTRL
    #endif
    
    #ifndef MATRIX_PINC_DC4
        #define MATRIX_PINC_DC4 PIN1_bm
        #define MATRIX_PINC_DC4_CTRL PIN1CTRL
    #endif
    
    #ifndef MATRIX_PINB_DC5
        #define MATRIX_PINB_DC5 PIN2_bm
        #define MATRIX_PINB_DC5_CTRL PIN2CTRL
    #endif

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!! Changes to MATRIX_DOTS_X/Y require an adjustment !!!
    // !!! of matrix_row() and matrix_column() functions    !!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    #ifndef MATRIX_DOTS_X
        #define MATRIX_DOTS_X 5
    #endif

    #ifndef MATRIX_DOTS_Y
        #define MATRIX_DOTS_Y 7
    #endif

    #ifndef MATRIX_TEST_DELAY_MS
        #define MATRIX_TEST_DELAY_MS 20
    #endif

    #ifndef MATRIX_DISPLAY_BUFFER_LENGTH
        #define MATRIX_DISPLAY_BUFFER_LENGTH MATRIX_DOTS_Y
    #endif

    #ifndef MATRIX_QUEUE_BUFFER_LENGTH
        #define MATRIX_QUEUE_BUFFER_LENGTH 2
    #endif

    #ifndef MATRIX_DISPLAY_REFRESH_RATE
        #define MATRIX_DISPLAY_REFRESH_RATE 0x09C4
    #endif

    #ifndef MATRIX_EEPROM_SIZE
        #define MATRIX_EEPROM_SIZE 16
    #endif

    #ifndef MATRIX_EEPROM_WRITE_START_ADDRESS
        #define MATRIX_EEPROM_WRITE_START_ADDRESS 0x30
    #endif
    
    #ifndef MATRIX_EEPROM_READ_START_ADDRESS
        #define MATRIX_EEPROM_READ_START_ADDRESS 0x20
    #endif

    #ifndef MATRIX_EEPROM_WRITE_DELAY_MS
        #define MATRIX_EEPROM_WRITE_DELAY_MS 10
    #endif

    #ifndef MATRIX_EEPROM_MAX_WRITE_CYCLES
        #define MATRIX_EEPROM_MAX_WRITE_CYCLES 100
    #endif

    #include <stdlib.h>
    #include <ctype.h>
    #include <avr/io.h>
    #include <avr/pgmspace.h>
    #include <avr/eeprom.h>
    #include <util/delay.h>

    #define MATRIX_ENABLE() (TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm)
    #define MATRIX_DISABLE() (TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm)
    #define MATRIX_REFRESH_RATE(rate) (TCA0.SINGLE.PER = rate)

    void matrix_setup(void);
    void matrix_refresh(void);
    void matrix_test(void);

    volatile unsigned char matrix_queue(volatile unsigned char data);
    void matrix_execute(void);

    void matrix_ascii_read();
    void matrix_eeprom_read(void);
    void matrix_eeprom_write(void);

#endif /* MATRIX_H_ */