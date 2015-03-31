#include <stc\stc15f2k60s2.h>
#include "delay.h"
#include "DS1302.h"

															//��    ��    ʱ    ��    ��  ����    ��
unsigned char code init[] = {0x00, 0x00, 0x12, 0x20, 0x08, 0x03, 0x14};
signed char  now[7];


/**************************************
��DS1302��1�ֽ�����
**************************************/
unsigned char DS1302_ReadByte()
{
    unsigned char i;
    unsigned char dat = 0;

    for (i=0; i<8; i++)             //8λ������
    {
		DS1302_SCLK = 0;                   //ʱ��������
		delay_us(2);                //��ʱ�ȴ�
        dat >>= 1;	                //��������һλ
		if (DS1302_IO) dat |= 0x80;        //��ȡ����
		DS1302_SCLK = 1;                   //ʱ��������
		delay_us(2);                //��ʱ�ȴ�
	}

    return dat;
}

/**************************************
��DS1302д1�ֽ�����
**************************************/
void DS1302_WriteByte(unsigned char dat)
{
    char i;

    for (i=0; i<8; i++)             //8λ������
    {
        DS1302_SCLK = 0;                   //ʱ��������
        delay_us(2);                //��ʱ�ȴ�
        dat >>= 1;                  //�Ƴ�����
        DS1302_IO = CY;                    //�ͳ����˿�
        DS1302_SCLK = 1;                   //ʱ��������
        delay_us(2);                //��ʱ�ȴ�
    }
}

/**************************************
��DS1302ĳ��ַ�ĵ�����
**************************************/
unsigned char DS1302_ReadData(unsigned char addr)
{
    unsigned char dat;

    DS1302_RST = 0;
    delay_us(2);
    DS1302_SCLK = 0;
    delay_us(2);
    DS1302_RST = 1;
    delay_us(2);
    DS1302_WriteByte(addr);         //д��ַ
    dat = DS1302_ReadByte();        //������
    DS1302_SCLK = 1;
    DS1302_RST = 0;

    return dat;
}

/**************************************
��DS1302��ĳ����ַд������
**************************************/
void DS1302_WriteData(unsigned char addr, unsigned char dat)
{
    DS1302_RST = 0;
    delay_us(2);
    DS1302_SCLK = 0;
    delay_us(2);
    DS1302_RST = 1;
    delay_us(2);
    DS1302_WriteByte(addr);         //д��ַ
    DS1302_WriteByte(dat);          //д����
    DS1302_SCLK = 1;
    DS1302_RST = 0;
}

/**************************************
д���ʼʱ��
**************************************/
void DS1302_SetTime(unsigned char *p)
{
    unsigned char addr = 0x80;
    unsigned char n = 7;

    DS1302_WriteData(0x8e, 0x00);   //����д����
    while (n--)
    {
        DS1302_WriteData(addr, *p++);
        addr += 2;
    }
    DS1302_WriteData(0x8e, 0x80);   //д����
}

/**************************************
��ȡ��ǰʱ��
**************************************/
void DS1302_GetTime(unsigned char *p)
{
    unsigned char addr = 0x81;
    unsigned char n = 7;

    while (n--)
    {
        *p++ = DS1302_ReadData(addr);
        addr += 2;
    }
}

/**************************************
��ʼ��DS1302
**************************************/
void DS1302_Initial()
{
    DS1302_RST = 0;
    DS1302_SCLK = 0;
    DS1302_WriteData(0x8e, 0x00);   //����д����
    DS1302_WriteData(0x80, 0x00);   //ʱ������
    DS1302_WriteData(0x90, 0xa6);   //һ�������ܣ�4K������
    DS1302_WriteData(0x8e, 0x80);   //д����
}