

#include "LCD.h"


void delay(uint z)
{
	uint x, y;
	for (x = z; x > 0; x--)
		for(y = 110; y > 0; y--);
}
uchar fan_zhuan_dat(uchar dat)
{
	uchar i,j=0x01,a,b;
	for(i=0;i<8;i++)
	{
		a=j&dat;
		a>>=i;
		
		b<<=1;
		j<<=1;
		b=b|a;
	}
	return b;
}
void chk_busy()	//���æ
{
   LCD12864_RS=0;
   LCD12864_RW=1;
   LCD12864_EN=1;
   LCD_data=0xff;
   while((LCD_data&0x01)==0x01);
   LCD12864_EN=0;
}
void  clr_screen()
{
   Lcd_WriteCmd(0x34);      //����ָ�����
   delay(5);    
   Lcd_WriteCmd(0x30);      //����ָ�����
   delay(5); 
   Lcd_WriteCmd(0x01);      //���� 
   delay(5);     
}

/*
static bit Lcd_Busy(void)
{                          
	bit result;

	LCD_RS = 0;
	LCD_RW = 1;
	LCD_EN = 1;
	DelayNOP();

	result = (bit)(P0&0x80);
	LCD_EN = 0;

	return(result); 
}
*/


void Lcd_WriteCmd(uchar cmd)
{                          

	chk_busy();
	LCD12864_RS = 0;//����/����ѡ���ߣ�����ѡ������
	LCD12864_RW = 0;//дģʽ
	LCD_data = fan_zhuan_dat(cmd);//�����ݽ��з�ת��ֵ��P0��(���͵�12864)
	LCD12864_EN = 1;//ʹ�ܶ�
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	LCD12864_EN = 0;	//ʹ�� 
}


void Lcd_WriteDat(uchar dat)
{                          
	LCD12864_RS = 1;//����
	LCD12864_RW = 0;//дģʽ
	LCD_data = fan_zhuan_dat(dat);
	LCD12864_EN = 1;
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	LCD12864_EN = 0;
}

void Lcd_Init(void)
{ 


	
	Lcd_WriteCmd(0x34);      //����ָ�����
	delay(5);
	Lcd_WriteCmd(0x30);      //����ָ�����
	delay(5);
	Lcd_WriteCmd(0x0C);      //��ʾ�����ع��
	delay(5);
	Lcd_WriteCmd(0x01);      //���LCD����ʾ����
	delay(5);
}



void Lcd_SetPos(uchar X,uchar Y)
{                          
   uchar  pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   Lcd_WriteCmd(pos);     //��ʾ��ַ
}


void Lcd_DispLine(uchar line, uchar pos, uchar *str)
{
	int i = 0;
	Lcd_SetPos(line, pos);
	while (str[i] != '\0')
	{
		Lcd_WriteDat(str[i]);
		i++;
	}
}
