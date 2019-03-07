#include "graphics.h"

static uint8_t buffer = 0;
static uint8_t buffers[2][64 / 8 * 128];

void graphic_ctrl_bit_set(uint8_t x)
{
	*GPIO_E_ODR_LOW &= ~B_SELECT;
    *GPIO_E_ODR_LOW |= x;
}

void graphic_ctrl_bit_clear(uint8_t x)
{
    *GPIO_E_ODR_LOW &= ~(B_SELECT | x);
}

void graphic_select_controller(uint8_t controller)
{
    if (!controller)
    {
        graphic_ctrl_bit_clear(B_CS1 | B_CS2);
    }
    else if ((controller & B_CS1) && (controller & B_CS2))
    {
        graphic_ctrl_bit_set(B_CS1 | B_CS2);
    }
    else if (controller & B_CS1)
    {
        graphic_ctrl_bit_set(B_CS1);
        graphic_ctrl_bit_clear(B_CS2);
    }
    else if (controller & B_CS2)
    {
        graphic_ctrl_bit_set(B_CS2);
        graphic_ctrl_bit_clear(B_CS1);
    }
}

void graphic_wait_ready()
{
    graphic_ctrl_bit_clear(B_E);
    *GPIO_E_MODER = 0x00005555;
    graphic_ctrl_bit_set(B_RW);
    graphic_ctrl_bit_clear(B_RS);
    delay_500ns();
    while (1)
    {
        graphic_ctrl_bit_set(B_E);
        delay_500ns();
		unsigned char value = *GPIO_E_IDR_HIGH;
		graphic_ctrl_bit_clear(B_E);
		delay_500ns();
        if (!(value & LCD_BUSY))
        {
            break;
        }
    }
    graphic_ctrl_bit_set(B_E);
    *GPIO_E_MODER = 0x55555555;
}

uint8_t graphic_read(uint8_t controller)
{
    uint8_t value;
    
    graphic_ctrl_bit_clear(B_E);
    *GPIO_E_MODER = 0x00005555;
    graphic_ctrl_bit_set(B_RS | B_RW);
    graphic_select_controller(controller);
    delay_500ns();
    graphic_ctrl_bit_set(B_E);
    delay_500ns();
    value = *GPIO_E_IDR_HIGH;
    graphic_ctrl_bit_clear(B_E);
    *GPIO_E_MODER = 0x55555555;
    if (controller & B_CS1)
    {
        graphic_select_controller(B_CS1);
        graphic_wait_ready();
    }
    if (controller & B_CS2)
    {
        graphic_select_controller(B_CS2);
        graphic_wait_ready();
    }
    return value;
}

void graphic_write(uint8_t value, uint8_t controller)
{
    *GPIO_E_ODR_HIGH = value;
    graphic_select_controller(controller);
    delay_500ns();
    graphic_ctrl_bit_set(B_E);
    delay_500ns();
    graphic_ctrl_bit_clear(B_E);
    if (controller & B_CS1)
    {
        graphic_select_controller(B_CS1);
        graphic_wait_ready();
    }
    if (controller & B_CS2)
    {
        graphic_select_controller(B_CS2);
        graphic_wait_ready();
    }
    *GPIO_E_ODR_HIGH = 0;
    graphic_ctrl_bit_set(B_E);
    graphic_select_controller(0);
}

void graphic_write_command(uint8_t command, uint8_t controller)
{
    graphic_ctrl_bit_clear(B_E);
    graphic_select_controller(controller);
    graphic_ctrl_bit_clear(B_RS | B_RW);
    graphic_write(command, controller);
}

void graphic_write_data(uint8_t data, uint8_t controller)
{
    
    graphic_ctrl_bit_clear(B_E);
    graphic_select_controller(controller);
    graphic_ctrl_bit_set(B_RS);
    graphic_ctrl_bit_clear(B_RW);
    graphic_write(data, controller);
}

uint8_t graphic_read_data(uint8_t controller)
{
    graphic_read(controller);
    return graphic_read(controller);
}

void graphic_init()
{
    graphic_ctrl_bit_set(B_E);
    delay_micro(10);
    graphic_ctrl_bit_clear(B_CS1 | B_CS2 | B_RST | B_E);
    delay_milli(30);
    graphic_ctrl_bit_set(B_RST);
    graphic_write_command(LCD_OFF, B_CS1 | B_CS2);    
    graphic_write_command(LCD_ON, B_CS1 | B_CS2);
    graphic_write_command(LCD_DISP_START, B_CS1 | B_CS2);
    graphic_write_command(LCD_SET_ADD, B_CS1 | B_CS2);
    graphic_write_command(LCD_SET_PAGE, B_CS1 | B_CS2);
    graphic_select_controller(0);
}

void graphic_clear_screen()
{
    for (uint32_t page = 0; page < 8; ++page)
    {
        graphic_write_command(LCD_SET_PAGE | page, B_CS1 | B_CS2);
        graphic_write_command(LCD_SET_ADD, B_CS1 | B_CS2);
        for (uint32_t address = 0; address < 64; ++address)
        {
            graphic_write_data(0, B_CS1 | B_CS2);
        }
    }
	
}

void graphic_pixel(uint8_t x, uint8_t y, uint8_t set)
{
    if (x < 0 || x >= 128 || y < 0 || y >= 64)
    {
        return;
    }
    if (set)
    {
        buffers[buffer][y / 8 * 128 + x] |= 1 << (y % 8);
    }
    else
    {
        buffers[buffer][y / 8 * 128 + x] &= ~(1 << (y % 8));
    }
}

void graphic_clear()
{
    for (int32_t x = 0; x < 128; ++x)
    {
        for (int32_t y = 0; y < 8; ++y)
        {
            buffers[buffer][y * 128 + x] = 0;
        }
    }
}

void graphic_swap()
{
    uint8_t controller = B_CS1;
    for (uint32_t address = 0; address < 128; ++address)
    {
        if (address == 64)
        {
            controller = B_CS2;
        }
        for (uint32_t page = 0; page < 8; ++page)
        {
            if (buffers[buffer ? 0 : 1][page * 128 + address] != buffers[buffer][page * 128 + address]) 
            {
                graphic_write_command(LCD_SET_ADD | address, controller);
                graphic_write_command(LCD_SET_PAGE | page, controller);
                graphic_write_data(buffers[buffer][page * 128 + address], controller);
            }
        }
    }
    if (buffer)
    {
        buffer = 0;
    }
    else
    {
        buffer = 1;
    }
}