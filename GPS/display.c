

#include "display.h"

GPS_INFO   GPS;  //GPS信息结构体


uchar code beiwei[]     = "北纬";
uchar code nanwei[]     = "南纬";
uchar code dongjing[]   = "东经";
uchar code xijing[]     = "西经";
uchar code sudu[]       = "速度:";
uchar code hangxiang[]  = "航向：";
uchar code gaodu[]      = "高度: ";
//uchar code jiaodu[]     = "角度: ";
uchar code haiba[]      = "海拔: ";
uchar code du[]         = "度";
uchar code meter[]      = "米";
uchar code kmperhour[]  = "km/h";
uchar code date[]       = "    年  月  日  ";

uchar code zongshu[]    = "可见卫星总数: ";
uchar code shiyong[]    = "使用卫星数  : ";
uchar code date7[]      = "  GPS 定位系统  ";
uchar code date8[]      = "    当前时间    ";


void Show_Float(float fla, uchar x, uchar y);
void Show_Float1(int fla, uchar x, uchar y);


void GPS_DispTime(void)
{
	uchar i = 0;
	uchar ch;

	char time[5];

	
	Lcd_DispLine(2, 0, date);  //年月日

	//yearp="     ";
	Int_To_Str(GPS.D.year,time);  //将年转换成字符串，存在time中
	Lcd_SetPos(2, 0);             //设置显示地址
	if(strlen(time)==4)	  		 	//判断接收数据是否有效，有效则显示
	{
		i = 0;
		while(time[i] != '\0')
		{
			ch = time[i++];
			Lcd_WriteDat(ch);	      //显示年
		}
	}

	Int_To_Str(GPS.D.month,time);
	Lcd_SetPos(2, 3);
	if(strlen(time)==2)
	{
		i = 0;
		while(time[i] != '\0')
		{
			ch =time[i++];
			Lcd_WriteDat(ch);		 //显示月
		}
	}
	Int_To_Str(GPS.D.day,time);
	Lcd_SetPos(2, 5);
	if(strlen(time)==2)
	{
		i = 0;
		while(time[i] != '\0')
		{
			ch =time[i++];
			Lcd_WriteDat(ch);		 //显示日
		}
	}

	Int_To_Str(GPS.D.hour,time);
	Lcd_SetPos(3, 1);
		if(strlen(time)==2)
	{
		i = 0;
		while(time[i] != '\0')
		{
			ch =time[i++];
			Lcd_WriteDat(ch);	
		}
	}
	Lcd_WriteDat(' ');
	Lcd_WriteDat(':');

	Int_To_Str(GPS.D.minute,time);
	Lcd_SetPos(3, 3);
		if(strlen(time)==2)
	{
		i = 0;
		while(time[i] != '\0')
		{
			ch =time[i++];
			Lcd_WriteDat(ch);	
		}
	}
	Lcd_WriteDat(' ');
	Lcd_WriteDat(':');

	Int_To_Str(GPS.D.second,time);
	Lcd_SetPos(3, 5);
		if(strlen(time)==2)
	{
		i = 0;
		while(time[i] != '\0')
		{
			ch =time[i++];
			Lcd_WriteDat(ch);	
		}
	}
}


void GPS_DisplayOne(void)  //第一页显示 时间日期 
{

	
	clr_screen();//Lcd_WriteCmd(0x01);    //清屏
	Lcd_DispLine(0, 0, date7);  
	Lcd_DispLine(1, 0, date8);  //当前时间
	GPS_DispTime();	   	//显示日期，时间
	
	
}

void GPS_DisplayTWO(void)
{
	uchar ch, i;
	 char info[10];

	clr_screen();
	Lcd_DispLine(0, 0, sudu); //显示当前速度
	Show_Float(GPS.speed, 0, 3);	  //显示速度值
	Lcd_DispLine(0, 6, kmperhour);	  //显示速度符号

	Lcd_DispLine(1, 0, hangxiang);	 //显示当前航向
	Show_Float(GPS.direction, 1, 3); //显示航向值
	Lcd_DispLine(1, 6, du);			 //显示航向符号

	if (GPS.NS == 'N')              //判断是北纬还是南纬
    Lcd_DispLine(2, 0, beiwei);		//显示北纬
	else if (GPS.NS == 'S')
	Lcd_DispLine(2, 0, nanwei);		//否则显示南纬

	if (GPS.EW == 'E')              //判断是东经还是西经
	Lcd_DispLine(3, 0, dongjing);   //显示东经
	else if (GPS.EW == 'W')
	Lcd_DispLine(3, 0, xijing);	    //否则西经


	Int_To_Str(GPS.latitude_Degree,info);  //显示纬度
	Lcd_SetPos(2, 2);
	if(strlen(info)==2)
	{						  //只有正常显示纬度，才显示纬分
		i = 0;
		while(info[i] != '\0')
		{
			ch = info[i++];
			Lcd_WriteDat(ch);
		}
		Lcd_WriteDat(' ');
		Lcd_WriteDat(' ');
		Lcd_WriteDat(0xA1);
		Lcd_WriteDat(0xE3);	

		Int_To_Str(GPS.latitude_Cent,info);  //显示纬分
		if(strlen(info)==2)
		{					  //只有正常显示纬分，才显示纬秒
			i = 0;
			while(info[i] != '\0')
			{
				ch = info[i++];
				Lcd_WriteDat(ch);
			}
			Lcd_WriteDat(0xA1);
			Lcd_WriteDat(0xE4);

			Int_To_Str(GPS.latitude_Second,info);  //显示纬秒
			if(strlen(info)==2)
			{
				i = 0;
				while(info[i] != '\0')
				{
					ch = info[i++];
					Lcd_WriteDat(ch);
				}
			}
		}	
	} 
	Int_To_Str(GPS.longitude_Degree,info);  //显示经度
	if(strlen(info)==3)
	{
		Lcd_DispLine(3, 2, info);
		Lcd_WriteDat(' ');
		Lcd_WriteDat(0xA1);
		Lcd_WriteDat(0xE3);
	
		Int_To_Str(GPS.longitude_Cent,info);  //显示经分
		if(strlen(info)==2)
		{
			Lcd_DispLine(3, 5, info);
			Lcd_WriteDat(0xA1);
			Lcd_WriteDat(0xE4);
		
			Int_To_Str(GPS.longitude_Second,info);  //显示经秒
			if(strlen(info)==2)
			{
				Lcd_DispLine(3, 7, info);
			}
		}
	} 

}
void GPS_DisplayThree(void) //显示速度航向
{
	clr_screen();//Lcd_WriteCmd(0x01);    //清屏


	Lcd_DispLine(0, 0, zongshu);
	Lcd_DispLine(1, 0, shiyong);
	Show_Float1(GPS.satellite, 0, 7);
	Show_Float1(GPS.satellite_use, 1, 7);

	Lcd_DispLine(2, 0, gaodu);
	Show_Float(GPS.height_ground, 2, 3);
	Lcd_DispLine(2, 6, meter);

	Lcd_DispLine(3, 0, haiba);
	Show_Float(GPS.height_sea, 3, 3);
	Lcd_DispLine(3, 6, meter);
		
}
void GPS_DisplayFour(void) //显示速度航向
{
	Lcd_DispLine(0, 0, zongshu);
	Show_Float1(GPS.satellite, 0, 7);		
}

void Show_Float(float fla, uchar x, uchar y)
{
	int integar;
	char Info[10],ch;
	uchar i;
	
	Lcd_SetPos(x, y);		
	integar = (int)fla;             							// 显示整数部分
	Int_To_Str(fla,Info);  //显示整数部分
	i = 0;
	while(Info[i] !='\0')
	{
		ch=Info[i++];
		Lcd_WriteDat(ch);
	}
	Lcd_WriteDat('.');   //显示小数点

	fla = fla - integar; //显示小数部分
	
	fla =  fla * 10;     //0.1                   						// 显示 0.1
	integar = (int) fla;
	fla = fla - integar;				 						// 改变fla的值,使fla总是小于1
	ch = integar + 0x30; 	
	Lcd_WriteDat(ch);
	
	fla =  fla*10;	    //0.01					 						// 显示 0.01
	integar = (int) fla;
	fla = fla - integar;					 					// 改变fla的值,使fla总是小于1
	ch = integar + 0x30 ; 
	Lcd_WriteDat(ch);
}
void Show_Float1(int fla, uchar x, uchar y)
{
	int integar;
	char Info[10],ch;
	uchar i;
	
	Lcd_SetPos(x, y);		
	integar = (int)fla;             							// 显示整数部分
	Int_To_Str(fla,Info);  //显示整数部分
	i = 0;
	while(Info[i] !='\0')
	{
		ch=Info[i++];
		Lcd_WriteDat(ch);
	}
	
}

