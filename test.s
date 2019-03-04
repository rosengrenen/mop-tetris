   1              		.arch armv6-m
   2              		.eabi_attribute 20, 1
   3              		.eabi_attribute 21, 1
   4              		.eabi_attribute 23, 3
   5              		.eabi_attribute 24, 1
   6              		.eabi_attribute 25, 1
   7              		.eabi_attribute 26, 1
   8              		.eabi_attribute 30, 6
   9              		.eabi_attribute 34, 0
  10              		.eabi_attribute 18, 4
  11              		.file	"startup.c"
  12              		.text
  13              	.Ltext0:
  14              		.cfi_sections	.debug_frame
  15              		.section	.start_section,"ax",%progbits
  16              		.align	1
  17              		.global	startup
  18              		.syntax unified
  19              		.code	16
  20              		.thumb_func
  21              		.fpu softvfp
  23              	startup:
  24              	.LFB0:
  25              		.file 1 "/home/rasmus/Documents/chalmers/tetris/startup.c"
   1:/home/rasmus/Documents/chalmers/tetris/startup.c **** /*
   2:/home/rasmus/Documents/chalmers/tetris/startup.c ****  * 	startup.c
   3:/home/rasmus/Documents/chalmers/tetris/startup.c ****  *
   4:/home/rasmus/Documents/chalmers/tetris/startup.c ****  */
   5:/home/rasmus/Documents/chalmers/tetris/startup.c **** void startup(void) __attribute__((naked)) __attribute__((section (".start_section")) );
   6:/home/rasmus/Documents/chalmers/tetris/startup.c **** 
   7:/home/rasmus/Documents/chalmers/tetris/startup.c **** /**
   8:/home/rasmus/Documents/chalmers/tetris/startup.c ****  * Grafik
   9:/home/rasmus/Documents/chalmers/tetris/startup.c ****  * Ascii
  10:/home/rasmus/Documents/chalmers/tetris/startup.c ****  * Keyboard
  11:/home/rasmus/Documents/chalmers/tetris/startup.c ****  * Delay
  12:/home/rasmus/Documents/chalmers/tetris/startup.c ****  */
  13:/home/rasmus/Documents/chalmers/tetris/startup.c ****  
  14:/home/rasmus/Documents/chalmers/tetris/startup.c **** void startup ( void )
  15:/home/rasmus/Documents/chalmers/tetris/startup.c **** {
  26              		.loc 1 15 0
  27              		.cfi_startproc
  28              		@ Naked Function: prologue and epilogue provided by programmer.
  29              		@ args = 0, pretend = 0, frame = 0
  30              		@ frame_needed = 1, uses_anonymous_args = 0
  16:/home/rasmus/Documents/chalmers/tetris/startup.c **** asm volatile(
  31              		.loc 1 16 0
  32              		.syntax divided
  33              	@ 16 "/home/rasmus/Documents/chalmers/tetris/startup.c" 1
  34 0000 0248     		 LDR R0,=0x2001C000
  35 0002 8546     	 MOV SP,R0
  36 0004 FFF7FEFF 	 BL main
  37 0008 FEE7     	.L1: B .L1
  38              	
  39              	@ 0 "" 2
  17:/home/rasmus/Documents/chalmers/tetris/startup.c **** 	" LDR R0,=0x2001C000\n"		/* set stack */
  18:/home/rasmus/Documents/chalmers/tetris/startup.c **** 	" MOV SP,R0\n"
  19:/home/rasmus/Documents/chalmers/tetris/startup.c **** 	" BL main\n"				/* call main */
  20:/home/rasmus/Documents/chalmers/tetris/startup.c **** 	".L1: B .L1\n"				/* never return */
  21:/home/rasmus/Documents/chalmers/tetris/startup.c **** 	) ;
  22:/home/rasmus/Documents/chalmers/tetris/startup.c **** }
  40              		.loc 1 22 0
  41              		.thumb
  42              		.syntax unified
  43 000a C046     		nop
  44              		.cfi_endproc
  45              	.LFE0:
  47              		.text
  48              		.align	1
  49              		.global	app_init
  50              		.syntax unified
  51              		.code	16
  52              		.thumb_func
  53              		.fpu softvfp
  55              	app_init:
  56              	.LFB1:
  23:/home/rasmus/Documents/chalmers/tetris/startup.c **** 
  24:/home/rasmus/Documents/chalmers/tetris/startup.c **** #include "graphics.h"
  25:/home/rasmus/Documents/chalmers/tetris/startup.c **** #include "keyboard.h"
  26:/home/rasmus/Documents/chalmers/tetris/startup.c **** 
  27:/home/rasmus/Documents/chalmers/tetris/startup.c **** void app_init()
  28:/home/rasmus/Documents/chalmers/tetris/startup.c **** {
  57              		.loc 1 28 0
  58              		.cfi_startproc
  59              		@ args = 0, pretend = 0, frame = 0
  60              		@ frame_needed = 1, uses_anonymous_args = 0
  61 0000 80B5     		push	{r7, lr}
  62              		.cfi_def_cfa_offset 8
  63              		.cfi_offset 7, -8
  64              		.cfi_offset 14, -4
  65 0002 00AF     		add	r7, sp, #0
  66              		.cfi_def_cfa_register 7
  29:/home/rasmus/Documents/chalmers/tetris/startup.c ****     keyb_init();
  67              		.loc 1 29 0
  68 0004 FFF7FEFF 		bl	keyb_init
  30:/home/rasmus/Documents/chalmers/tetris/startup.c ****     graphic_init();
  69              		.loc 1 30 0
  70 0008 FFF7FEFF 		bl	graphic_init
  31:/home/rasmus/Documents/chalmers/tetris/startup.c ****     //graphic_clear_screen();
  32:/home/rasmus/Documents/chalmers/tetris/startup.c ****     //ascii_init();
  33:/home/rasmus/Documents/chalmers/tetris/startup.c **** }
  71              		.loc 1 33 0
  72 000c C046     		nop
  73 000e BD46     		mov	sp, r7
  74              		@ sp needed
  75 0010 80BD     		pop	{r7, pc}
  76              		.cfi_endproc
  77              	.LFE1:
  79              		.align	1
  80              		.global	main
  81              		.syntax unified
  82              		.code	16
  83              		.thumb_func
  84              		.fpu softvfp
  86              	main:
  87              	.LFB2:
  34:/home/rasmus/Documents/chalmers/tetris/startup.c **** 
  35:/home/rasmus/Documents/chalmers/tetris/startup.c **** int main()
  36:/home/rasmus/Documents/chalmers/tetris/startup.c **** {
  88              		.loc 1 36 0
  89              		.cfi_startproc
  90              		@ args = 0, pretend = 0, frame = 8
  91              		@ frame_needed = 1, uses_anonymous_args = 0
  92 0012 80B5     		push	{r7, lr}
  93              		.cfi_def_cfa_offset 8
  94              		.cfi_offset 7, -8
  95              		.cfi_offset 14, -4
  96 0014 82B0     		sub	sp, sp, #8
  97              		.cfi_def_cfa_offset 16
  98 0016 00AF     		add	r7, sp, #0
  99              		.cfi_def_cfa_register 7
  37:/home/rasmus/Documents/chalmers/tetris/startup.c ****     app_init();
 100              		.loc 1 37 0
 101 0018 FFF7FEFF 		bl	app_init
  38:/home/rasmus/Documents/chalmers/tetris/startup.c ****     
  39:/home/rasmus/Documents/chalmers/tetris/startup.c ****     unsigned int i = 0;
 102              		.loc 1 39 0
 103 001c 0023     		movs	r3, #0
 104 001e 7B60     		str	r3, [r7, #4]
 105              	.L4:
  40:/home/rasmus/Documents/chalmers/tetris/startup.c ****     while (1)
  41:/home/rasmus/Documents/chalmers/tetris/startup.c ****     {
  42:/home/rasmus/Documents/chalmers/tetris/startup.c ****         graphic_pixel(i, 5, 1);
 106              		.loc 1 42 0 discriminator 1
 107 0020 7B68     		ldr	r3, [r7, #4]
 108 0022 DBB2     		uxtb	r3, r3
 109 0024 0122     		movs	r2, #1
 110 0026 0521     		movs	r1, #5
 111 0028 1800     		movs	r0, r3
 112 002a FFF7FEFF 		bl	graphic_pixel
  43:/home/rasmus/Documents/chalmers/tetris/startup.c ****         graphic_swap();
 113              		.loc 1 43 0 discriminator 1
 114 002e FFF7FEFF 		bl	graphic_swap
  44:/home/rasmus/Documents/chalmers/tetris/startup.c ****         i++;
 115              		.loc 1 44 0 discriminator 1
 116 0032 7B68     		ldr	r3, [r7, #4]
 117 0034 0133     		adds	r3, r3, #1
 118 0036 7B60     		str	r3, [r7, #4]
  42:/home/rasmus/Documents/chalmers/tetris/startup.c ****         graphic_swap();
 119              		.loc 1 42 0 discriminator 1
 120 0038 F2E7     		b	.L4
 121              		.cfi_endproc
 122              	.LFE2:
 124              	.Letext0:
