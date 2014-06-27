
#include <stdio.h>
#include <string.h>
#include "GPS.h"
#include "LCD.h"
#include "display.h"

sbit Key = P3^7;

char   xdata rev_buf[80];        //���ջ���     
uchar  xdata rev_start = 0;     //���տ�ʼ��־      
uchar  xdata rev_stop  = 0;     //����ֹͣ��־     
uchar  xdata gps_flag = 0;      //GPS�����־    
  
uchar  xdata num = 0;          
uchar Flag_dis = 1;
extern GPS_INFO   GPS;  //��display.c�ж��壬ʹ��ʱҪ��extern


void Uart_Init(void)
{
	TMOD = 0x21;//��ʱ��1
	PCON = 0x00;//�����ʲ��ӱ�
	SCON = 0x50;//���й�����ʽ1�����н���
	TH1 = 0xfd; //����11.0592 ��ѡ������9600
	TL1 = 0xfd;
	EA = 1;
	ES = 1;	//�����жϿ���
	TR1 = 1;	
}

/****************************************
������	
/****************************************/
void main(void)
{
	uchar error_num = 0;
	Lcd_Init();	  //��ʼ��LCD   
	Uart_Init();  //��ʼ������
	GPS_Init();   //��ʼ��GPS     
	rev_stop=0;
	while(1)
	{
		if (rev_stop)   //���������һ��         
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
					if (GPS_RMC_Parse(rev_buf, &GPS))  //����GPRMC      
					{
					
						GPS_DisplayOne();  //��ʾ��һҳ��Ϣ
						error_num = 0;
						gps_flag = 0;
						rev_stop  = 0;
						
					}
					else
					{
						error_num++;
						if (error_num >= 20) //���������Ч����20��               
						{
							
							error_num = 20;
							clr_screen();
							GPS_Init();     //���س�ʼ��            
						}
						gps_flag = 0;
						rev_stop  = 0;
						
					}
				};break;
				case 2:
				{
					
					if (GPS_RMC_Parse(rev_buf, &GPS)) //����GPRMC         
					{						
						GPS_DisplayTwo();	  //��ʾGPS�ڶ�ҳ��Ϣ          
						error_num = 0;
						gps_flag = 0;
						rev_stop  = 0;							
					}
					else
					{
						error_num++;
						if (error_num >= 20) //���������Ч����20��               
						{
							
							error_num = 20;
							clr_screen();
							GPS_Init();     //���س�ʼ��          
						}
						gps_flag = 0;
						rev_stop  = 0;						
					}
					
				};break;

				case 3:
				{
					if (GPS_GGA_Parse(rev_buf, &GPS)) //����GPGGA         
					{						
						GPS_DisplayThree();	  //��ʾGPS����ҳ��Ϣ          
						error_num = 0;
						gps_flag = 0;
						rev_stop  = 0;							
					}
					else
					{
						error_num++;
						if (error_num >= 20) //���������Ч����20��               
						{
							
							error_num = 20;
							clr_screen();
							GPS_Init();     //���س�ʼ��          
						}
						gps_flag = 0;
						rev_stop  = 0;						
					}
					if (GPS_GSV_Parse(rev_buf, &GPS)) //����GPGSV         
					{					
						GPS_DisplayFour();	  //��ʾGPS����ҳ��Ϣ          
						error_num = 0;
						gps_flag = 0;
						rev_stop  = 0;							
					}
					else
					{
						error_num++;
						if (error_num >= 20) //���������Ч����20��               
						{
							
							error_num = 20;
							clr_screen();
							GPS_Init();     //���س�ʼ��          
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
/*�����жϺ�������GPS���������ݣ����浽������ rev_buf[]
���͵�������
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
		if ((ch == '$') && (gps_flag == 0))  //����յ��ַ�'$'���㿪ʼ����           
		{
			rev_start = 1;
			rev_stop  = 0;
		}
	
		if (rev_start == 1)  //��־λΪ1����ʼ����            
		{
			rev_buf[num++] = ch;  //�ַ��浽������           
			if (ch == '\n')     //������յ�����           
			{
				rev_buf[num] = '\0';
				rev_start = 0;
				rev_stop  = 1;
				gps_flag = 1;
				num = 0;
			}
		}
	}
	RI = 0;	 //RI��0�����½���            
	ES = 1;	
}
