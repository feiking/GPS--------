

#include "display.h"

GPS_INFO   GPS;  //GPS��Ϣ�ṹ��


uchar code beiwei[]     = "��γ";
uchar code nanwei[]     = "��γ";
uchar code dongjing[]   = "����";
uchar code xijing[]     = "����";
uchar code sudu[]       = "�ٶ�:";
uchar code hangxiang[]  = "����";
uchar code gaodu[]      = "�߶�: ";
//uchar code jiaodu[]     = "�Ƕ�: ";
uchar code haiba[]      = "����: ";
uchar code du[]         = "��";
uchar code meter[]      = "��";
uchar code kmperhour[]  = "km/h";
uchar code date[]       = "    ��  ��  ��  ";

uchar code zongshu[]    = "�ɼ���������: ";
uchar code shiyong[]    = "ʹ��������  : ";
uchar code date7[]      = "  GPS ��λϵͳ  ";
uchar code date8[]      = "    ��ǰʱ��    ";


void Show_Float(float fla, uchar x, uchar y);
void Show_Float1(int fla, uchar x, uchar y);


void GPS_DispTime(void)
{
	uchar i = 0;
	uchar ch;

	char time[5];

	
	Lcd_DispLine(2, 0, date);  //������

	//yearp="     ";
	Int_To_Str(GPS.D.year,time);  //����ת�����ַ���������time��
	Lcd_SetPos(2, 0);             //������ʾ��ַ
	if(strlen(time)==4)	  		 	//�жϽ��������Ƿ���Ч����Ч����ʾ
	{
		i = 0;
		while(time[i] != '\0')
		{
			ch = time[i++];
			Lcd_WriteDat(ch);	      //��ʾ��
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
			Lcd_WriteDat(ch);		 //��ʾ��
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
			Lcd_WriteDat(ch);		 //��ʾ��
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


void GPS_DisplayOne(void)  //��һҳ��ʾ ʱ������ 
{

	
	clr_screen();//Lcd_WriteCmd(0x01);    //����
	Lcd_DispLine(0, 0, date7);  
	Lcd_DispLine(1, 0, date8);  //��ǰʱ��
	GPS_DispTime();	   	//��ʾ���ڣ�ʱ��
	
	
}

void GPS_DisplayTWO(void)
{
	uchar ch, i;
	 char info[10];

	clr_screen();
	Lcd_DispLine(0, 0, sudu); //��ʾ��ǰ�ٶ�
	Show_Float(GPS.speed, 0, 3);	  //��ʾ�ٶ�ֵ
	Lcd_DispLine(0, 6, kmperhour);	  //��ʾ�ٶȷ���

	Lcd_DispLine(1, 0, hangxiang);	 //��ʾ��ǰ����
	Show_Float(GPS.direction, 1, 3); //��ʾ����ֵ
	Lcd_DispLine(1, 6, du);			 //��ʾ�������

	if (GPS.NS == 'N')              //�ж��Ǳ�γ������γ
    Lcd_DispLine(2, 0, beiwei);		//��ʾ��γ
	else if (GPS.NS == 'S')
	Lcd_DispLine(2, 0, nanwei);		//������ʾ��γ

	if (GPS.EW == 'E')              //�ж��Ƕ�����������
	Lcd_DispLine(3, 0, dongjing);   //��ʾ����
	else if (GPS.EW == 'W')
	Lcd_DispLine(3, 0, xijing);	    //��������


	Int_To_Str(GPS.latitude_Degree,info);  //��ʾγ��
	Lcd_SetPos(2, 2);
	if(strlen(info)==2)
	{						  //ֻ��������ʾγ�ȣ�����ʾγ��
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

		Int_To_Str(GPS.latitude_Cent,info);  //��ʾγ��
		if(strlen(info)==2)
		{					  //ֻ��������ʾγ�֣�����ʾγ��
			i = 0;
			while(info[i] != '\0')
			{
				ch = info[i++];
				Lcd_WriteDat(ch);
			}
			Lcd_WriteDat(0xA1);
			Lcd_WriteDat(0xE4);

			Int_To_Str(GPS.latitude_Second,info);  //��ʾγ��
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
	Int_To_Str(GPS.longitude_Degree,info);  //��ʾ����
	if(strlen(info)==3)
	{
		Lcd_DispLine(3, 2, info);
		Lcd_WriteDat(' ');
		Lcd_WriteDat(0xA1);
		Lcd_WriteDat(0xE3);
	
		Int_To_Str(GPS.longitude_Cent,info);  //��ʾ����
		if(strlen(info)==2)
		{
			Lcd_DispLine(3, 5, info);
			Lcd_WriteDat(0xA1);
			Lcd_WriteDat(0xE4);
		
			Int_To_Str(GPS.longitude_Second,info);  //��ʾ����
			if(strlen(info)==2)
			{
				Lcd_DispLine(3, 7, info);
			}
		}
	} 

}
void GPS_DisplayThree(void) //��ʾ�ٶȺ���
{
	clr_screen();//Lcd_WriteCmd(0x01);    //����


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
void GPS_DisplayFour(void) //��ʾ�ٶȺ���
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
	integar = (int)fla;             							// ��ʾ��������
	Int_To_Str(fla,Info);  //��ʾ��������
	i = 0;
	while(Info[i] !='\0')
	{
		ch=Info[i++];
		Lcd_WriteDat(ch);
	}
	Lcd_WriteDat('.');   //��ʾС����

	fla = fla - integar; //��ʾС������
	
	fla =  fla * 10;     //0.1                   						// ��ʾ 0.1
	integar = (int) fla;
	fla = fla - integar;				 						// �ı�fla��ֵ,ʹfla����С��1
	ch = integar + 0x30; 	
	Lcd_WriteDat(ch);
	
	fla =  fla*10;	    //0.01					 						// ��ʾ 0.01
	integar = (int) fla;
	fla = fla - integar;					 					// �ı�fla��ֵ,ʹfla����С��1
	ch = integar + 0x30 ; 
	Lcd_WriteDat(ch);
}
void Show_Float1(int fla, uchar x, uchar y)
{
	int integar;
	char Info[10],ch;
	uchar i;
	
	Lcd_SetPos(x, y);		
	integar = (int)fla;             							// ��ʾ��������
	Int_To_Str(fla,Info);  //��ʾ��������
	i = 0;
	while(Info[i] !='\0')
	{
		ch=Info[i++];
		Lcd_WriteDat(ch);
	}
	
}

