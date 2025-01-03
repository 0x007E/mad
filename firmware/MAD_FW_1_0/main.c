/* -----------------------------------------
* G.Raf^engineering
* www.sunriax.at
* -----------------------------------------
*    Platform: .matrix display controller
*    Hardware: ATTiny406/1606/...
* -----------------------------------------
*     Version: 1.0 Release
*      Author: G.Raf
* Description:
*   .matrix display controller firmware
* -----------------------------------------
*/

#define F_CPU 20000000UL

// Uncomment to disable signal led
#define SIGNAL_LED PIN5_bm

#define BAUDRATE 9600UL
#define UART_INIT_WAIT_MS 1000UL
// #define USE_U2X

#include <avr/io.h>
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "./system/system.h"
#include "./matrix/matrix.h"

#ifdef USE_U2X
    #define USART0_BAUD_RATE(BAUD_RATE) ((float)(CLK_PER * 64 / (8 * (float)BAUD_RATE)) + 0.5)
#else
    #define USART0_BAUD_RATE(BAUD_RATE) ((float)(CLK_PER * 64 / (16 * (float)BAUD_RATE)) + 0.5)
#endif

ISR(SPI0_INT_vect)
{
    sei();	// Allow nested interrupts
    SPI0.DATA = matrix_queue(SPI0.DATA);
    SPI0.INTFLAGS = SPI_IF_bm;
}

ISR(USART0_RXC_vect)
{
    sei();	// Allow nested interrupts
    
    matrix_queue(0x08);
    matrix_queue(USART0.RXDATAL);
    matrix_execute();
    
    // DATA transfer LED
#ifdef SIGNAL_LED
    PORTA.OUTTGL = SIGNAL_LED;
#endif
    USART0.STATUS = USART_RXCIF_bm;
}

ISR(PORTA_PORT_vect)
{
    sei();	// Allow nested interrupts

    // DATA transfer LED
#ifdef SIGNAL_LED
    PORTA.OUTTGL = SIGNAL_LED;
#endif

    matrix_execute();

    PORTA.INTFLAGS = PIN4_bm;
}

ISR(TCA0_OVF_vect)
{
    matrix_refresh();

    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

int main(void)
{
    system_init();

    // PORT Setup
    PORTA.DIRCLR = PIN4_bm;				// Set SS to input
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm;	// Enable pullup on SS
    
    // DATA transfer LED
#ifdef SIGNAL_LED
    PORTA.DIRSET = SIGNAL_LED;          // Enable signal LED
#endif

    // DISPLAY Update
    matrix_setup();

    // Enable interrupts globally
    sei();

    matrix_test();

    // UART Setup
    if(!(PORTA.IN & PIN4_bm))
    {
        // DATA transfer LED
#ifdef SIGNAL_LED
        PORTA.OUTSET = SIGNAL_LED;
#endif
        _delay_ms(UART_INIT_WAIT_MS);

        PORTMUX.CTRLB = PORTMUX_USART0_ALTERNATE_gc;
        
        USART0.BAUD = (unsigned int)USART0_BAUD_RATE(BAUDRATE);
        USART0.CTRLA = USART_RXCIE_bm;
        USART0.CTRLB = USART_RXEN_bm;
        
        #if USE_U2X
        USART0.CTRLB |= USART_RXMODE_CLK2X_gc;
        #endif

        MATRIX_ENABLE();
    }
    //SPI Setup
    else
    {
        PORTA.DIR &= ~PIN1_bm;	// Set MOSI to input
        PORTA.DIR |= PIN2_bm;	// Set MISO to output
        PORTA.DIR &= ~PIN3_bm;	// Set SCK to input
        
        PORTA.PIN4CTRL |= PORT_ISC_RISING_gc;
        
        SPI0.CTRLA = SPI_ENABLE_bm;
        SPI0.INTCTRL = SPI_IE_bm;
    }
    
    while (1)
    {
        matrix_ascii_read();
        matrix_eeprom_read();
        matrix_eeprom_write();
    }
}
