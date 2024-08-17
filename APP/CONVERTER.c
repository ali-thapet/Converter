
#define F_CPU 8000000
#include <util/delay.h>

#include "StdTypes.h"
#include "LCD_Int.h"
#include "KEYPAD_Int.h"
#include "CONVERTER_Int.h"

void Convert_DecToBinary(s16 Num)
{
	
	LCD_WriteBinary2_s32(Num);
}

void Convert_DecToHex(s16 Num)
{
	LCD_WriteHex2_s16(Num);
}
void Convert_DecToHex2(u16 Num)
{
	LCD_WriteHex2_u16(Num);
}


void Convert_BinaryToDec(s16 Num)
{
	LCD_WriteNumber_s32(Num);
}
void Convert_BinaryToHex(s16 Num)
{
	LCD_WriteHex2_s16(Num);
}

void Convert_BinaryToHex2(u16 Num)
{
	LCD_WriteHex2_u16(Num);
}


void Convert_HexToBinary(s16 HN,s16 LN)
{
	s16 Num;
	Num=(HN<<8)|LN;
	LCD_WriteBinary2_s32(Num);
}

void Convert_HexToDec(s16 HN,s16 LN)
{
	s16 Num;
	Num=(HN<<8)|LN;
	LCD_WriteNumber_s32(Num);
}


