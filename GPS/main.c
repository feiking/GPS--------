
#include <stdio.h>
#include <string.h>
#include "GPS.h"
#include "LCD.h"
#include "display.h"

sbit Key = P3^7;

char   xdata rev_buf[80];        //接收缓存     
uchar  xdata rev_start = 0;     //接收开始标志      
uchar  xdata rev_stop  = 0;     //接收停止标志     
uchar  xdata gps_flag = 0;      //GPS处理标志    
  
uchar  xdata num = 0;          
uchar Flag_dis = 1;
extern GPS_INFO   GPS;  //在display.c中定义，使用时要加extern


void Uart_Init(void)
{
	TMOD = 0x21;//定时器1
	PCON = 0x00;//波特率不加倍
	SCON = 0x50;//串行工作方式1允许串行接收
	TH1 = 0xfd; //晶振11.0592 ，选择波特率9600
	TL1 = 0xfd;
	EA = 1;
	ES = 1;	//串行中断开启
	TR1 = 1;	
}

/****************************************
主函数	
/****************************************/
void main(void)
{
	uchar error_num = 0;
	Lcd_Init();	  //初始化LCD   
	Uart_Init();  //初始化串口
	GPS_Init();   //初始化GPS     
	rev_stop=0;
	while(1)
	{
		if (rev_stop)   //如果接收完一行         
		{
			
		   if(Key == 0)
		   {
		   		while(!Key);
				Flag_dis ++;
				if(Flag_dis == 4)
				Flag_dis = 1;	 	
		   }  
		   switch(Flag_dis)
		   {
		   		case 1:
				{
					if (GPS_RMC_Parse(rev_buf, &GPS))  //解析GPRMC      
					{
					
						GPS_DisplayOne();  //显示第一页信息
						error_num = 0;
						gps_flag = 0;
						rev_stop  = 0;
						
					}
					else
					{
						error_num++;
						if (error_num >= 20) //如果数据无效超过20次               
						{
							
							error_num = 20;
							clr_screen();
							GPS_Init();     //返回初始化            
						}
						gps_flag = 0;
						rev_stop  = 0;
						
					}
				};break;
				case 2:
				{
					
					if (GPS_RMC_Parse(rev_buf, &GPS)) //解析GPRMC         
					{						
						GPS_DisplayTwo();	  //显示GPS第二页信息          
						error_num = 0;
						gps_flag = 0;
						rev_stop  = 0;							
					}
					else
					{
						error_num++;
						if (error_num >= 20) //如果数据无效超过20次               
						{
							
							error_num = 20;
							clr_screen();
							GPS_Init();     //返回初始化          
						}
						gps_flag = 0;
						rev_stop  = 0;						
					}
					
				};break;

				case 3:
				{
					if (GPS_GGA_Parse(rev_buf, &GPS)) //解析GPGGA         
					{						
						GPS_DisplayThree();	  //显示GPS第三页信息          
						error_num = 0;
						gps_flag = 0;
						rev_stop  = 0;							
					}
					else
					{
						error_num++;
						if (error_num >= 20) //如果数据无效超过20次               
						{
							
							error_num = 20;
							clr_screen();
							GPS_Init();     //返回初始化          
						}
						gps_flag = 0;
						rev_stop  = 0;						
					}
					if (GPS_GSV_Parse(rev_buf, &GPS)) //解析GPGSV         
					{					
						GPS_DisplayFour();	  //显示GPS第三页信息          
						error_num = 0;
						gps_flag = 0;
						rev_stop  = 0;							
					}
					else
					{
						error_num++;
						if (error_num >= 20) //如果数据无效超过20次               
						{
							
							error_num = 20;
							clr_screen();
							GPS_Init();     //返回初始化          
						}
						gps_flag = 0;
						rev_stop  = 0;						
					}					
				};break;
		   }
		}
	}
}
/****************************************/
/*串口中断函数接收GPS发来的数据，并存到缓冲区 rev_buf[]
发送的数据流
$GPGSV,2,2,06,20,44,057,41,27,08,288,33*75
$GPGLL,3157.64696,N,11850.54907,E,112056.00,A,A*61
$GPRMC,112057.00,A,3157.64695,N,11850.54908,E,0.170,,240712,,,A*71
$GPVTG,,T,,M,0.170,N,0.315,K,A*22
$GPGGA,112057.00,3157.64695,N,11850.54908,E,1,05,4.10,33.1,M,2.6,M,,*5C
$GPGSA,A,3,17,20,04,27,09,,,,,,,,4.79,4.10,2.47*00
$GPGSV,2,1,06,04,48,271,41,09,06,298,34,11,,,26,17,64,002,40*48
*/
/****************************************/

void Uart_Receive(void) interrupt 4
{
	uchar ch;
	ES = 0;
	if (RI)
	{
		ch = SBUF;     
		if ((ch == '$') && (gps_flag == 0))  //如果收到字符'$'，便开始接收           
		{
			rev_start = 1;
			rev_stop  = 0;
		}
	
		if (rev_start == 1)  //标志位为1，开始接收            
		{
			rev_buf[num++] = ch;  //字符存到数组中           
			if (ch == '\n')     //如果接收到换行           
			{
				rev_buf[num] = '\0';
				rev_start = 0;
				rev_stop  = 1;
				gps_flag = 1;
				num = 0;
			}
		}
	}
	RI = 0;	 //RI清0，重新接收            
	ES = 1;	
}
