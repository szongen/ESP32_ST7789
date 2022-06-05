#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "driver/gpio.h"

#define USE_HORIZONTAL 0  //???¨²?????????????? 0??1????? 2??3?????


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 240
#define LCD_H 320

#else
#define LCD_W 320
#define LCD_H 240
#endif


typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef int64_t s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

/**
 * D0 -34
 * D1 -35
 * D2 -32
 * D3 -33
 * D4 -25
 * D5 -26
 * D6 -27
 * D7 -14
 * RD -12
 * WR -13 
 * DC -5
 * RST -18
 * CS -19
 */

#define GPIO_D0 23
#define GPIO_D1 22
#define GPIO_D2 32
#define GPIO_D3 33
#define GPIO_D4 25
#define GPIO_D5 26
#define GPIO_D6 27
#define GPIO_D7 14
#define GPIO_RD 12
#define GPIO_WR 13
#define GPIO_DC 5
#define GPIO_RES 18
#define GPIO_CS 19

#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0

//-----------------LCD??????---------------- 



void DATA_OUTPUT(uint8_t data);

#define DATAOUT(x) DATA_OUTPUT(x); 
// #define DATAIN     GPIOA->IDR;   //????????

#define	LCD_RES_Set()	gpio_set_level(GPIO_RES,GPIO_PIN_SET)    //??¦Ë			  PB3
#define	LCD_CS_Set()  gpio_set_level(GPIO_CS,GPIO_PIN_SET)       //?????  	PB4
#define	LCD_DC_Set()  gpio_set_level(GPIO_DC,GPIO_PIN_SET)        //????/????   PB5
#define	LCD_WR_Set()	gpio_set_level(GPIO_WR,GPIO_PIN_SET)        //§Õ????	    PB6
#define	LCD_RD_Set()	gpio_set_level(GPIO_RD,GPIO_PIN_SET)       //??????		  PB7
#define	LCD_BLK_Set()	       //???????	  PB8

#define	LCD_RES_Clr()	gpio_set_level(GPIO_RES,GPIO_PIN_RESET)         //??¦Ë				PB3    
#define	LCD_CS_Clr()  gpio_set_level(GPIO_CS,GPIO_PIN_RESET)     //?????    PB4
#define	LCD_DC_Clr()	gpio_set_level(GPIO_DC,GPIO_PIN_RESET)     //????/????   PB5
#define	LCD_WR_Clr()	gpio_set_level(GPIO_WR,GPIO_PIN_RESET)     //§Õ????	    PB6
#define	LCD_RD_Clr()	gpio_set_level(GPIO_RD,GPIO_PIN_RESET)     //??????	    PB7
#define	LCD_BLK_Clr()	    //???????	  PB8



void LCD_GPIO_Init(void);//?????GPIO
void LCD_Writ_Bus(u8 dat);//???SPI???
void LCD_WR_DATA8(u8 dat);//§Õ????????
void LCD_WR_DATA(u16 dat);//§Õ?????????
void LCD_WR_REG(u8 dat);//§Õ????????
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//??????????
void LCD_Init(void);//LCD?????
#endif




