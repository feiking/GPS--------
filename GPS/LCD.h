#ifndef __LCD_H_
#define __LCD_H_

#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint  unsigned int
#define Nop() _nop_()
#define _Nop() _nop_()
#define LCD_data  P0             //数据口
sbit LCD12864_RS  =  P2^5;      //寄存器选择输入 
sbit LCD12864_RW  =  P2^6;      //液晶读/写控制
sbit LCD12864_EN  =  P2^7;      //液晶使能控制	



#define DelayNOP(); {_nop_();_nop_();_nop_();_nop_();};

uchar fan_zhuan_dat(uchar dat);
void  clr_screen();
void delay(uint z);
void chk_busy();	//检测忙
void Lcd_WriteCmd(uchar cmd);
void Lcd_WriteDat(uchar dat);
void Lcd_Init(void);
void Lcd_SetPos(uchar X,uchar Y);
void Lcd_DispLine(uchar line, uchar pos, uchar *str);

#endif //__LCD_H_