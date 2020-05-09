// Version 1.0
// 10/13/19

#include "Nokia_5110.h"

void NOKIA_Send_Command(char cmd)
{
	CLR_NOKIA_CE;
	CLR_NOKIA_DC;
	SPI_MasterTransmit(cmd);
	SET_NOKIA_CE;
}

void NOKIA_Send_Data(char data)
{
	CLR_NOKIA_CE;
	SET_NOKIA_DC;
	SPI_MasterTransmit(data);
	SET_NOKIA_CE;
}

void NOKIA_Send_Data_Stream(char data[])
{
	int i = 0;
	CLR_NOKIA_CE;
	SET_NOKIA_DC;
	while(data[i] != '\0')
	{
		SPI_MasterTransmit(data[i]);
	}
	SET_NOKIA_CE;
}

void NOKIA_Init(void)
{
	DDRD = (1<<DDD5) | (1<<DDD7); // Set pins as outputs for DC and CE
	SET_NOKIA_CE; // Set CE pin to begins command transmission protocol
	NOKIA_Send_Command(0x21); // function set PD=0 (non-powerdown), V=0(hori addr mode), H=1 (extd instr set mode)
	NOKIA_Send_Command(0xB0); // set Vop (contrast)
	NOKIA_Send_Command(0x04); // set Temp Coefficient
	NOKIA_Send_Command(0x14); // set LCD Bias mode 1:48
	NOKIA_Send_Command(0x20); // function set PD=0 (non-powerdown), V=0(hori addr mode), H=0 (basic instr set mode)
	NOKIA_Send_Command(0x0C); // display control set normal mode D=1, E=0
	NOKIA_Fill_Display(0);
	NOKIA_Send_Command(0x40); // init Y-addr to 0
	NOKIA_Send_Command(0x80); // init x-addr to 0
}

void NOKIA_Invert(void)
{
	NOKIA_Send_Command(0x0D);
}

void NOKIA_Draw_Chkr(void)
{
	for(int i = 0; i < 252; i++) //504 addresses to write 1 byte to, loop 252 time since writing 2 bytes
	{
		NOKIA_Send_Data(0xAA);
		NOKIA_Send_Data(0x55);
	}
}

void NOKIA_Fill_Display(char fill)
{
	char fill_type;
	if(fill == 1)
	{
		fill_type = 0xFF;
	}
	else
	{
		fill_type = 0x00;
	}
	for(int i = 0; i < 504; i++) //504 addresses to write 1 byte to
	{
		NOKIA_Send_Data(fill_type);
	}
}

void NOKIA_Draw_Char(char ascii_char)
{
	for(int i = 0; i < 5; i++)
	{
		NOKIA_Send_Data(ASCII[ascii_char - 0x20][i]);
	}
	NOKIA_Send_Data(0x00);
}

void NOKIA_Draw_String(char ascii_chars[], int size)
{
	int i = 0;
	while(i < size-1){
		NOKIA_Draw_Char(ascii_chars[i]);
		i++;
	}
}

void NOKIA_Draw_Pixel(uint8_t x_position, uint8_t y_position)
{
	uint8_t y_addr = y_position / 8;
	uint8_t data = y_position % 8;
	
	NOKIA_Send_Command(0x40 + y_addr); // set y_addr
	//NOKIA_Send_Command(0x80 + x_position); // set x_addr
	NOKIA_Send_Data(1 << data);
}