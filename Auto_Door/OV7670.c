#include <stc\stc15f2k60s2.h>
#include "delay.h"
#include "sccb.h"
#include "OV7670.h"




#define OV7670_REG_NUM  114


code	unsigned	char OV7670_reg[OV7670_REG_NUM][2]=
{	 
/*OV7670 QVGA RGB565*/
{0x3a, 0x04},
{0x40, 0xd0},
{0x12, 0x14},
{0x32, 0x80},
{0x17, 0x16},
{0x18, 0x04},
{0x19, 0x02},
{0x1a, 0x7b},
{0x03, 0x06},
{0x0c, 0x0c},
{0x15, 0x02},
{0x3e, 0x00},
{0x70, 0x00},
{0x71, 0x01},
{0x72, 0x11},
{0x73, 0x09},
{0xa2, 0x02},
{0x11, 0x00},
{0x7a, 0x20},
{0x7b, 0x1c},
{0x7c, 0x28},
{0x7d, 0x3c},
{0x7e, 0x55},
{0x7f, 0x68},
{0x80, 0x76},
{0x81, 0x80},
{0x82, 0x88},
{0x83, 0x8f},
{0x84, 0x96},
{0x85, 0xa3},
{0x86, 0xaf},
{0x87, 0xc4},
{0x88, 0xd7},
{0x89, 0xe8},
{0x13, 0xe7},
{0x00, 0x00},
{0x10, 0x00},
{0x0d, 0x00},
{0x14, 0x20},
{0xa5, 0x05},
{0xab, 0x07},
{0x24, 0x75},
{0x25, 0x63},
{0x26, 0xA5},
{0x9f, 0x78},
{0xa0, 0x68},
{0xa1, 0x03},
{0xa6, 0xdf},
{0xa7, 0xdf},
{0xa8, 0xf0},
{0xa9, 0x90},
{0xaa, 0x94},
{0x13, 0xe5},
{0x0e, 0x61},
{0x0f, 0x4b},
{0x16, 0x02},
{0x1e, 0x27},
{0x21, 0x02},
{0x22, 0x91},
{0x29, 0x07},
{0x33, 0x0b},
{0x35, 0x0b},
{0x37, 0x1d},
{0x38, 0x71},
{0x39, 0x2a},
{0x3c, 0x78},
{0x4d, 0x40},
{0x4e, 0x20},
{0x69, 0x5d},
{0x6b, 0x40},
{0x74, 0x19},
{0x8d, 0x4f},
{0x8e, 0x00},
{0x8f, 0x00},
{0x90, 0x00},
{0x91, 0x00},
{0x92, 0x00},
{0x96, 0x00},
{0x9a, 0x80},
{0xb0, 0x84},
{0xb1, 0x0c},
{0xb2, 0x0e},
{0xb3, 0x82},
{0xb8, 0x0a},
{0x43, 0x14},
{0x44, 0xf0},
{0x45, 0x34},
{0x46, 0x58},
{0x47, 0x28},
{0x48, 0x3a},
{0x59, 0x88},
{0x5a, 0x88},
{0x5b, 0x44},
{0x5c, 0x67},
{0x5d, 0x49},
{0x5e, 0x0e},
{0x64, 0x04},
{0x65, 0x20},
{0x66, 0x05},
{0x94, 0x04},
{0x95, 0x08},
{0x6c, 0x0a},
{0x6d, 0x55},
{0x4f, 0x80},
{0x50, 0x80},
{0x51, 0x00},
{0x52, 0x22},
{0x53, 0x5e},
{0x54, 0x80},
{0x6e, 0x11},
{0x6f, 0x9f},
{0x55, 0x00},
{0x56, 0x40},
{0x58, 0x9e},
};

void	OV7670_Init()
{
	unsigned char i;
	PWDN=0;					//�ر�ʡ��ģʽ
	//Ӳ����λ
	RESET=0;
	delay_ms(10);
	RESET=1;	
	delay_ms(10);
	sccb_senddata(0x12,0x80);		//������λ
	for(i=0;i<OV7670_REG_NUM;i++)
  {
		sccb_senddata(OV7670_reg[i][0],OV7670_reg[i][1]);
	}
}
//ʡ��ģʽ
void OV7670_off()
{
	PWDN=1;
}
//����ģʽ
void OV7670_on()
{
	PWDN=0;
}