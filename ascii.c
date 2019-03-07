#include "ascii.h"

#include "delay.h"

#define 	STK_CTRL	((volatile unsigned int *) 0xE000E010)
#define 	STK_LOAD	((volatile unsigned int *) 0xE000E014)
#define 	STK_VAL		((volatile unsigned int *) 0xE000E018)
#define 	GPIO_E 		(volatile unsigned int *) 0x40021000
#define		GPIO_E_MODER 	((volatile unsigned int *) (GPIO_E))
#define		GPIO_E_ODR_LOW	(volatile unsigned char *) 0x40021014
#define		GPIO_E_ODR_HIGH	(volatile unsigned char *) 0x40021015
#define		GPIO_E_IDR_LOW	(volatile unsigned char *) 0x40021010
#define		GPIO_E_IDR_HIGH	(volatile unsigned char *) 0x40021011
#define		B_E			0x40
#define		B_SELECT	4
#define		B_RW		2
#define		B_RS		1

void ascii_ctrl_bit_set(unsigned char x){
	unsigned char c;
	c = *GPIO_E_ODR_LOW;
	c |= (B_SELECT | x);
	*GPIO_E_ODR_LOW = c;
	
}
void ascii_ctrl_bit_clear(unsigned char x){
	unsigned char c;
	c= *GPIO_E_ODR_LOW;
	c &= (B_SELECT | ~x);
	*GPIO_E_ODR_LOW = c;
	
}
void ascii_write_cmd(unsigned char command){
	ascii_ctrl_bit_clear(B_RS);
	ascii_ctrl_bit_clear(B_RW);
	ascii_write_controller(command);
}


void ascii_write_data(unsigned char data){
	ascii_ctrl_bit_set(B_RS);
	ascii_ctrl_bit_clear(B_RW);
	ascii_write_controller(data);
}

void ascii_write_controller(unsigned char c)	{
	ascii_ctrl_bit_set(B_E);
	*GPIO_E_ODR_HIGH = c;
	ascii_ctrl_bit_clear(B_E);
	delay_500ns();
}

unsigned char ascii_read_controller(void){
	unsigned char c;
	ascii_ctrl_bit_set(B_E);
	delay_500ns();
	c=*GPIO_E_IDR_HIGH;
	ascii_ctrl_bit_clear(B_E);
	return c;
}

unsigned char ascii_read_status(void){
	unsigned char c;
	*GPIO_E_MODER = 0x00005555;
	ascii_ctrl_bit_set(B_RW);
	ascii_ctrl_bit_clear(B_RS);
	c= ascii_read_controller();
	*GPIO_E_MODER = 0x55555555;
	return c;
}

unsigned char ascii_read_data(void){
	unsigned char c;
	*GPIO_E_MODER = 0x00005555;
	ascii_ctrl_bit_set(B_RW);
	ascii_ctrl_bit_set(B_RS);
	c= ascii_read_controller();
	*GPIO_E_MODER = 0x55555555;
	return c;
}

void ascii_wait_ready(void){
	while((ascii_read_status()&0x80)==0x80);
	delay_micro(8);
}

void ascii_write_char(unsigned char c){
	ascii_wait_ready();
	ascii_write_data(c);
	delay_micro(43);
}

void ascii_gotoxy(unsigned char x, unsigned char y){
	unsigned char address;
	if(y!=1){
		address=0x40|(x-1);
	}else{
		address=x-1;
	}
	ascii_write_cmd(0x80|address);
}

void ascii_init(void){
	ascii_wait_ready();
	ascii_write_cmd(0x38);/*function set*/
	delay_micro(39);
	ascii_wait_ready();
	ascii_write_cmd(0x0C);/*display on*/
	delay_micro(39);
	ascii_wait_ready();
	ascii_write_cmd(1);/*clear display*/
	delay_milli(2);
	ascii_wait_ready();
	ascii_write_cmd(6); /*entry mode set*/
	delay_micro(39);
}

void ascii_print_at(char* string, int8_t x, int8_t y)
{
    ascii_gotoxy(x, y);
    while (*string)
    {
        ascii_write_char(*string++);
    }
}

void ascii_clear()
{
    ascii_wait_ready();
	ascii_write_cmd(1);/*clear display*/
	delay_milli(2);
}