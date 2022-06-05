#include "lcd_init.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void LCD_GPIO_Init(void)
{
	gpio_reset_pin(GPIO_D0);
    gpio_set_direction(GPIO_D0, GPIO_MODE_OUTPUT);
    gpio_reset_pin(GPIO_D1);
    gpio_set_direction(GPIO_D1, GPIO_MODE_OUTPUT);
	gpio_reset_pin(GPIO_D2);
    gpio_set_direction(GPIO_D2, GPIO_MODE_OUTPUT);
    gpio_reset_pin(GPIO_D3);
    gpio_set_direction(GPIO_D3, GPIO_MODE_OUTPUT);
	gpio_reset_pin(GPIO_D4);
    gpio_set_direction(GPIO_D4, GPIO_MODE_OUTPUT);
    gpio_reset_pin(GPIO_D5);
    gpio_set_direction(GPIO_D5, GPIO_MODE_OUTPUT);
	gpio_reset_pin(GPIO_D6);
    gpio_set_direction(GPIO_D6, GPIO_MODE_OUTPUT);
    gpio_reset_pin(GPIO_D7);
    gpio_set_direction(GPIO_D7, GPIO_MODE_OUTPUT);

    gpio_reset_pin(GPIO_RD);
    gpio_set_direction(GPIO_RD, GPIO_MODE_OUTPUT);
	gpio_reset_pin(GPIO_WR);
    gpio_set_direction(GPIO_WR, GPIO_MODE_OUTPUT);
	gpio_reset_pin(GPIO_DC);
    gpio_set_direction(GPIO_DC, GPIO_MODE_OUTPUT);
	gpio_reset_pin(GPIO_RES);
    gpio_set_direction(GPIO_RES, GPIO_MODE_OUTPUT);  
	gpio_reset_pin(GPIO_CS);
    gpio_set_direction(GPIO_CS, GPIO_MODE_OUTPUT);
}


void DATA_OUTPUT(uint8_t data)
{
    if(data&(1<<0))
    {
        gpio_set_level(GPIO_D0,GPIO_PIN_SET);
    }
    else
    {
        gpio_set_level(GPIO_D0,GPIO_PIN_RESET);
    }
    if(data&(1<<1))
    {
        gpio_set_level(GPIO_D1,GPIO_PIN_SET);
    }
    else
    {
        gpio_set_level(GPIO_D1,GPIO_PIN_RESET);
    }
    if(data&(1<<2))
    {
        gpio_set_level(GPIO_D2,GPIO_PIN_SET);
    }
    else
    {
        gpio_set_level(GPIO_D2,GPIO_PIN_RESET);
    }
    if(data&(1<<3))
    {
        gpio_set_level(GPIO_D3,GPIO_PIN_SET);
    }
    else
    {
        gpio_set_level(GPIO_D3,GPIO_PIN_RESET);
    }
    if(data&(1<<4))
    {
        gpio_set_level(GPIO_D4,GPIO_PIN_SET);
    }
    else
    {
        gpio_set_level(GPIO_D4,GPIO_PIN_RESET);
    }
    if(data&(1<<5))
    {
        gpio_set_level(GPIO_D5,GPIO_PIN_SET);
    }
    else
    {
        gpio_set_level(GPIO_D5,GPIO_PIN_RESET);
    }
    if(data&(1<<6))
    {
        gpio_set_level(GPIO_D6,GPIO_PIN_SET);
    }
    else
    {
        gpio_set_level(GPIO_D6,GPIO_PIN_RESET);
    }
    if(data&(1<<7))
    {
        gpio_set_level(GPIO_D7,GPIO_PIN_SET);
    }
    else
    {
        gpio_set_level(GPIO_D7,GPIO_PIN_RESET);
    }
}

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8 dat) 
{	
	LCD_CS_Clr();
	LCD_WR_Clr();
	DATAOUT(dat);
	LCD_WR_Set();
	LCD_CS_Set();
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
	LCD_DC_Clr();//写命令
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//写数据
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
	else
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
}

void LCD_Init(void)
{
	LCD_GPIO_Init();//初始化GPIO
	
	LCD_RES_Clr();//复位
	vTaskDelay(100/ portTICK_PERIOD_MS);
	LCD_RES_Set();
	vTaskDelay(100/ portTICK_PERIOD_MS);
	
	LCD_BLK_Set();//打开背光
    vTaskDelay(100/ portTICK_PERIOD_MS);
	
	LCD_WR_REG(0x11); 
	vTaskDelay(120/ portTICK_PERIOD_MS); 

	LCD_WR_REG(0x36); 
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0);

	LCD_WR_REG(0x3A);	
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33); 

	LCD_WR_REG(0xB7); 
	LCD_WR_DATA8(0x35);  

	LCD_WR_REG(0xBB);
	LCD_WR_DATA8(0x19);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x12);   

	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x20);  

	LCD_WR_REG(0xC6); 
	LCD_WR_DATA8(0x0F);    

	LCD_WR_REG(0xD0); 
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2B);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x4C);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x44);
	LCD_WR_DATA8(0x51);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x20);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0x20); //反显关闭

	LCD_WR_REG(0x29); 
}








