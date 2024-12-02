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
*	Library for initializing matrix display
* -----------------------------------------
*/

#include "matrix.h"

const __flash unsigned char ascii[][5] = {
    {   // SPACE
        0b0000000,
        0b0000000,
        0b0000000,
        0b0000000,
        0b0000000
    },
    {   // !
        0b0000000,
        0b0000000,
        0b1101111,
        0b0000000,
        0b0000000
    },
    {   // "
        0b0000000,
        0b0000000,
        0b0000011,
        0b0000011,
        0b0000000
    },
    {   // #
        0b0010100,
        0b0111110,
        0b0010100,
        0b0111110,
        0b0010100
    },
    {   // $
        0b0100100,
        0b0101010,
        0b1111110,
        0b0101010,
        0b0010010
    },
    {   // %
        0b0100010,
        0b0010101,
        0b0101010,
        0b1010100,
        0b0100010
    },
    {   // &
        0b0011010,
        0b0100101,
        0b0100101,
        0b0101101,
        0b0110000
    },
    {   // '
        0b0000000,
        0b0000000,
        0b0000011,
        0b0000000,
        0b0000000
    },
    {   // (
        0b0000000,
        0b0111110,
        0b1000001,
        0b0000000,
        0b0000000
    },
    {   // )
        0b0000000,
        0b0000000,
        0b1000001,
        0b0111110,
        0b0000000
    },
    {   // *
        0b0000000,
        0b0000101,
        0b0000010,
        0b0000101,
        0b0000000
    },
    {   // +
        0b0000000,
        0b0001000,
        0b0011100,
        0b0001000,
        0b0000000
    },
    {   // ,
        0b0000000,
        0b0000000,
        0b0000000,
        0b1100000,
        0b0000000
    },
    {   // -
        0b0000000,
        0b0001000,
        0b0001000,
        0b0001000,
        0b0000000
    },
    {   // .
        0b0000000,
        0b0000000,
        0b0000000,
        0b1000000,
        0b0000000
    },
    {   // /
        0b0000000,
        0b1100000,
        0b0111110,
        0b0000011,
        0b0000000
    },
    {   // 0
        0b0000000,
        0b0111110,
        0b1000001,
        0b0111110,
        0b0000000
    },
    {   // 1
        0b0000000,
        0b0000010,
        0b1111111,
        0b0000000,
        0b0000000
    },
    {   // 2
        0b1000000,
        0b1110010,
        0b1011001,
        0b1000110,
        0b0000000
    },
    {   // 3
        0b0000000,
        0b1001001,
        0b1001001,
        0b0110110,
        0b0000000
    },
    {   // 4
        0b0000000,
        0b0001100,
        0b0001010,
        0b1111111,
        0b0001000
    },
    {   // 5
        0b1000000,
        0b1001111,
        0b1001001,
        0b1001001,
        0b0110001
    },
    {   // 6
        0b0000000,
        0b1111111,
        0b1001001,
        0b1111001,
        0b0000000
    },
    {   // 7
        0b0000001,
        0b0000111,
        0b0011001,
        0b1100001,
        0b0000000
    },
    {   // 8
        0b0110110,
        0b1001001,
        0b1001001,
        0b0110110,
        0b0000000
    },
    {   // 9
        0b0000000,
        0b0000110,
        0b0001001,
        0b1111110,
        0b0000000
    },
    {   // :
        0b0000000,
        0b0000000,
        0b0010100,
        0b0000000,
        0b0000000
    },
    {   // ;
        0b0000000,
        0b0010000,
        0b0001010,
        0b0000000,
        0b0000000
    },
    {   // <
        0b0000000,
        0b0001000,
        0b0010100,
        0b0100010,
        0b0000000
    },
    {   // =
        0b0000000,
        0b0010100,
        0b0010100,
        0b0010100,
        0b0000000
    },
    {   // >
        0b0000000,
        0b0100010,
        0b0010100,
        0b0001000,
        0b0000000
    },
    {   // ?
        0b0000000,
        0b0110010,
        0b1101001,
        0b0100110,
        0b0000000
    },
    {   // @
        0b0111110,
        0b1001101,
        0b1010011,
        0b1011111,
        0b1001110
    },
    {   // A
        0b1111110,
        0b0001001,
        0b0001001,
        0b0001001,
        0b1111110
    },
    {   // B
        0b1111111,
        0b1001001,
        0b1001001,
        0b1001001,
        0b0110110
    },
    {   // C
        0b0111110,
        0b1000001,
        0b1000001,
        0b1000001,
        0b1000001
    },
    {   // D
        0b1111111,
        0b1000001,
        0b1000001,
        0b1000001,
        0b0111110
    },
    {   // E
        0b1111111,
        0b1001001,
        0b1001001,
        0b1001001,
        0b1001001
    },
    {   // F
        0b1111111,
        0b0001001,
        0b0001001,
        0b0001001,
        0b0000001
    },
    {   // G
        0b0111110,
        0b1000001,
        0b1001001,
        0b1001001,
        0b1111001
    },
    {   // H
        0b1111111,
        0b0001000,
        0b0001000,
        0b0001000,
        0b1111111
    },
    {   // I
        0b0000000,
        0b1000001,
        0b1111111,
        0b1000001,
        0b0000000
    },
    {   // J
        0b0100000,
        0b1000000,
        0b1000000,
        0b1000000,
        0b0111111
    },
    {   // K
        0b1111111,
        0b0001000,
        0b0010100,
        0b0100010,
        0b1000001
    },
    {   // L
        0b1111111,
        0b1000000,
        0b1000000,
        0b1000000,
        0b1000000
    },
    {   // M
        0b1111111,
        0b0000010,
        0b1111100,
        0b0000010,
        0b1111111
    },
    {   // N
        0b1111111,
        0b0000010,
        0b0011100,
        0b0100000,
        0b1111111
    },
    {   // O
        0b0111110,
        0b1000001,
        0b1000001,
        0b1000001,
        0b0111110
    },
    {   // P
        0b1111111,
        0b0001001,
        0b0001001,
        0b0001001,
        0b0000110
    },
    {   // Q
        0b0111110,
        0b1000001,
        0b1010001,
        0b0100001,
        0b1011110
    },
    {   // R
        0b1111111,
        0b0001001,
        0b0011001,
        0b0101001,
        0b1000110
    },
    {   // S
        0b1000110,
        0b1001001,
        0b1001001,
        0b1001001,
        0b0110001
    },
    {   // T
        0b0000001,
        0b0000001,
        0b1111111,
        0b0000001,
        0b0000001
    },
    {   // U
        0b0111111,
        0b1000000,
        0b1000000,
        0b1000000,
        0b0111111
    },
    {   // V
        0b0011111,
        0b0100000,
        0b1000000,
        0b0100000,
        0b0011111
    },
    {   // W
        0b0111111,
        0b1000000,
        0b0111100,
        0b1000000,
        0b0111111
    },
    {   // X
        0b1000001,
        0b0100010,
        0b0011100,
        0b0100010,
        0b1000001
    },
    {   // Y
        0b0000001,
        0b0000010,
        0b1111100,
        0b0000010,
        0b0000001
    },
    {
        0b1100001,
        0b1010001,
        0b1001001,
        0b1000101,
        0b1000011
    },
    {   // [
        0b0000000,
        0b1111111,
        0b1000001,
        0b1000001,
        0b0000000
    },
    {   // BACKSLASH
        0b0000000,
        0b0000011,
        0b0011100,
        0b1100000,
        0b0000000
    },
    {   // ]
        0b0000000,
        0b1000001,
        0b1000001,
        0b1111111,
        0b0000000
    },
    {   // ^
        0b0000000,
        0b0000010,
        0b0000001,
        0b0000010,
        0b0000000
    },
    {   // _
        0b0000000,
        0b1000000,
        0b1000000,
        0b1000000,
        0b0000000
    },
    {   // `
        0b0000000,
        0b0000000,
        0b0000001,
        0b0000010,
        0b0000000
    }
};

void matrix_setup()
{
    PORTA.DIRSET = MATRIX_PINA_DR5 | MATRIX_PINA_DR7;
    PORTB.DIRSET = MATRIX_PINB_DR1 | MATRIX_PINB_DR4 | MATRIX_PINB_DR6 | MATRIX_PINB_DC2 | MATRIX_PINB_DC3 | MATRIX_PINB_DC5;
    PORTC.DIRSET = MATRIX_PINC_DR2 | MATRIX_PINC_DR3 | MATRIX_PINC_DC1 | MATRIX_PINC_DC4;
    
    // TIMER Setup
    TCA0.SINGLE.PER = MATRIX_DISPLAY_REFRESH_RATE;
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV8_gc;
}


static void matrix_row_clear()
{
    PORTA.OUTCLR = MATRIX_PINA_DR5 | MATRIX_PINA_DR7;
    PORTB.OUTCLR = MATRIX_PINB_DR1 | MATRIX_PINB_DR4 | MATRIX_PINB_DR6;
    PORTC.OUTCLR = MATRIX_PINC_DR2 | MATRIX_PINC_DR3;
}

static void matrix_row(volatile unsigned char row)
{
    matrix_row_clear();

    switch (row)
    {
        case 0:
            PORTB.OUTSET = MATRIX_PINB_DR1;
        break;
        case 1:
            PORTC.OUTSET = MATRIX_PINC_DR2;
        break;
        case 2:
            PORTC.OUTSET = MATRIX_PINC_DR3;
        break;
        case 3:
            PORTB.OUTSET = MATRIX_PINB_DR4;
        break;
        case 4:
            PORTA.OUTSET = MATRIX_PINA_DR5;
        break;
        case 5:
            PORTB.OUTSET = MATRIX_PINB_DR6;
        break;
        case 6:
            PORTA.OUTSET = MATRIX_PINA_DR7;
        break;
        default:
        break;
    }
}

static void matrix_column_clear()
{
    PORTB.OUTSET = MATRIX_PINB_DC2 | MATRIX_PINB_DC3 | MATRIX_PINB_DC5;
    PORTC.OUTSET = MATRIX_PINC_DC1 | MATRIX_PINC_DC4;
}

volatile unsigned char matrix_display_buffer[MATRIX_DISPLAY_BUFFER_LENGTH];

static void matrix_column(volatile unsigned char row)
{
    matrix_column_clear();

    unsigned char column = matrix_display_buffer[row];

    if(column & (0x01))
    {
        PORTC.OUTCLR = MATRIX_PINC_DC1;
    }
    if(column & (0x02))
    {
        PORTB.OUTCLR = MATRIX_PINB_DC2;
    }
    if(column & (0x04))
    {
        PORTB.OUTCLR = MATRIX_PINB_DC3;
    }
    if(column & (0x08))
    {
        PORTC.OUTCLR = MATRIX_PINC_DC4;
    }
    if(column & (0x10))
    {
        PORTB.OUTCLR = MATRIX_PINB_DC5;
    }
}

volatile unsigned char matrix_row_position;

void matrix_refresh(void)
{
    matrix_column(matrix_row_position);
    matrix_row(matrix_row_position);

    if((++matrix_row_position) >= MATRIX_DOTS_Y)
    {
        matrix_row_position = 0;
    }
}

static void matrix_clear_buffer(void)
{
    for (unsigned char y=0; y < MATRIX_DISPLAY_BUFFER_LENGTH; y++)
    {
        matrix_display_buffer[y] = 0x00;
    }
}

void matrix_test()
{
    matrix_clear_buffer();
    _delay_ms((MATRIX_TEST_DELAY_MS<<2));

    MATRIX_ENABLE();

    for (unsigned char y=0; y < MATRIX_DOTS_Y; y++)
    {
        for (unsigned char x=0; x < MATRIX_DOTS_X; x++)
        {
            matrix_display_buffer[y] |= (1<<x);
            _delay_ms(MATRIX_TEST_DELAY_MS);
        }
    }
    
    matrix_clear_buffer();
    _delay_ms((MATRIX_TEST_DELAY_MS<<2));

    MATRIX_DISABLE();
}

volatile unsigned char matrix_queue_command;
volatile unsigned char matrix_queue_data;
volatile unsigned char matrix_queue_position;

static void matrix_queue_reset(void)
{
    matrix_queue_position = 0;
}

volatile unsigned char matrix_queue(volatile unsigned char data)
{
    if((matrix_queue_position++) == 0)
    {
        matrix_queue_command = data;

        return matrix_queue_data;
    }
    matrix_queue_reset();
    matrix_queue_data = data;

    return matrix_queue_command;
}


static void matrix_copy_to_buffer()
{
    if((matrix_queue_command - 1) >= MATRIX_DISPLAY_BUFFER_LENGTH)
    {
        return;
    }
    matrix_display_buffer[(matrix_queue_command - 1)] = matrix_queue_data;
}

static void matrix_array2buffer(unsigned char *source, volatile unsigned char *destination)
{
    for (unsigned char y=0; y < MATRIX_DOTS_Y; y++)
    {
        destination[y] = 0x00;
        
        for (unsigned char x=0; x < MATRIX_DOTS_X; x++)
        {
            destination[y] |= ((0x01 & (source[x]>>y))<<x);
        }
    }
}

static void matrix_ascii2buffer()
{
    unsigned char temp[MATRIX_DOTS_X];

    memcpy_P(temp, ascii[(matrix_queue_data - ' ')], sizeof(temp));
    matrix_array2buffer(temp, matrix_display_buffer);
}

static unsigned char matrix_ascii_read_operation;

void matrix_ascii_read()
{
    if(matrix_ascii_read_operation)
    {
        matrix_ascii2buffer();
        matrix_ascii_read_operation = 0;
    }
}

static void matrix_eeprom2buffer(unsigned char address, volatile unsigned char *buffer)
{
    if(address >= MATRIX_EEPROM_SIZE)
    {
        return;
    }

    unsigned char temp[MATRIX_DOTS_X];
    
    eeprom_read_block(temp, (unsigned char*)(((0x0F & address) * MATRIX_DOTS_Y) + address), sizeof(temp));
    matrix_array2buffer(temp, buffer);
}

static unsigned char matrix_eeprom_read_operation;

void matrix_eeprom_read()
{
    if(matrix_eeprom_read_operation)
    {
        matrix_eeprom2buffer((matrix_eeprom_read_operation - MATRIX_EEPROM_READ_START_ADDRESS), matrix_display_buffer);
        matrix_eeprom_read_operation = 0;
    }
}

static void matrix_buffer2eeprom(unsigned char address, volatile unsigned char *buffer)
{
    if(address >= MATRIX_EEPROM_SIZE)
    {
        return;
    }

    unsigned char temp[MATRIX_DOTS_X];
    
    for (unsigned char y=0; y < MATRIX_DOTS_X; y++)
    {
        temp[y] = 0x00;
        
        for (unsigned char x=0; x < MATRIX_DOTS_Y; x++)
        {
            temp[y] |= ((0x01 & (buffer[x]>>y))<<x);
        }
    }
    
    matrix_clear_buffer();
    
    eeprom_write_block(temp, (unsigned char*)(((0x0F & address) * MATRIX_DOTS_Y) + address), sizeof(temp));
    _delay_ms(MATRIX_EEPROM_WRITE_DELAY_MS);
}

static unsigned char matrix_eeprom_write_counter;
static unsigned char matrix_eeprom_write_operation;

void matrix_eeprom_write()
{
    if(matrix_eeprom_write_operation)
    {
        if((++matrix_eeprom_write_counter) < MATRIX_EEPROM_MAX_WRITE_CYCLES)
        {
            matrix_buffer2eeprom((matrix_eeprom_write_operation - MATRIX_EEPROM_WRITE_START_ADDRESS), matrix_display_buffer);
        }
        matrix_eeprom_write_operation = 0;
    }
}

static unsigned int matrix_refresh_rate;

void matrix_execute(void)
{
    switch (matrix_queue_command)
    {
        case 0x01:	// ROW 1
        case 0x02:	// ROW 2
        case 0x03:	// ROW 3
        case 0x04:	// ROW 4
        case 0x05:	// ROW 5
        case 0x06:	// ROW 6
        case 0x07:	// ROW 7
            matrix_copy_to_buffer();
        break;
        case 0x08:	// Copy ASCII character from flash to DISPLAY
            //matrix_ascii2buffer();
            matrix_ascii_read_operation = 1;
        break;
        case 0x10:	// CLEAR DISPLAY
            matrix_clear_buffer();
        break;
        case 0x1F:	// DISPLAY On/Off
            if(matrix_queue_data & 0x01)
            {
                MATRIX_ENABLE();
            }
            else
            {
                matrix_row_clear();
                matrix_column_clear();
                MATRIX_DISABLE();
            }
        break;
        case 0x20:	// Copy EEPROM content to DISPLAY
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x2D:
        case 0x2E:
        case 0x2F:
             matrix_eeprom_read_operation = matrix_queue_data;
        break;
        case 0x30:	// Copy DISPLAY content to EEPROM
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
            matrix_eeprom_write_operation = matrix_queue_data;
        break;
        case 0xF0:
            matrix_refresh_rate = 0x00FF & matrix_queue_data;
        break;
        case 0xF1:
            matrix_refresh_rate &= 0x00FF;
            matrix_refresh_rate |= 0xFF00 & (matrix_queue_data<<8);
            MATRIX_REFRESH_RATE(matrix_refresh_rate);
        break;
        case 0xFF:
            matrix_queue_reset();
        break;
        default:
        break;
    }
}
