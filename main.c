
#define F_CPU 8000000
#include <util/delay.h>

#include "StdTypes.h"
#include "String.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "KEYPAD_Int.h"
#include "CONVERTER_Int.h"


                  
	/************************** Decimal, Binary and Hex converter using keypad and LCD **************************/
				  
				  
                                                         /* Notes */
													   
/* 1- to convert from Hex :  - write number then press '+' to set it then go to next digit to write next number.
                             - to write from 'A' to 'F' press 'A' more than once.  
							 
   2- from 0 -> 32767 positive and form  32768 -> 65535 is negative
   3- to convert from Binary :  - you must write 16 digits to have right result
*/



// vflag      to  (view flag) control display or not display message
// clearflag  to  Control clear the LCD or not
// NNflag     to  (New Number)Control if i will write the first number or second number
//HN=LOW      first 4 bits from left 
//LN=LOW      first 4 bits from right 
//HN2=LOW     second 4 bits from left 
//LN2=LOW     second 4 bits from right 




int main(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	u32 Num=LOW;
    s16 r,i=LOW,C=LOW;
	s16 Mode=LOW,HN=LOW,LN=LOW,HN2=LOW,LN2=LOW,Fch=LOW,Sch=LOW;
	u8 Flag1=0,Flag2=-1,vflag=LOW,clearflag=LOW,NNflag=LOW;
	LCD_Clear();
	LCD_WriteString("Converter Made");
	LCD_SetCursor(1,0);
	LCD_WriteString(" By Ali Thapet ");	
	_delay_ms(2000);
    while (1) 
    {
		r=KEYPAD_GetKey();
		if(Flag1==0)
		{
			if(clearflag==0)
			{
				LCD_Clear();
				clearflag=1;
			}
			if(vflag==0)
			{
				LCD_SetCursor(0,0);
				LCD_WriteString("Convert From");
				LCD_SetCursor(1,0);
				LCD_WriteString("1-D  2-B  3-H");
				vflag=1;
			}
			
			if(r!=NO_KEY)
			{ 
				Num=Num*10+(r-'0');
				if(Num>=1&&Num<=3)
				{
					Fch=Num;
					Num=0;
					LCD_Clear();
					LCD_WriteChar(r);
					Flag1=1;
					Flag2=1;
					vflag=0;
				}
				else
				{
					Num=0;
				}
				if(r=='c')
				{
					clearflag=0;
					vflag=0;
					Num=0;
				}
				
			}
		}
		else if(Flag2==1)
		{
			if(Fch==1)
			{
				if(vflag==0)
				{
					LCD_SetCursor(0,0);
					LCD_WriteString("             ");
					LCD_SetCursor(0,0);
					LCD_WriteString("Convert To");
					LCD_SetCursor(1,0);
					LCD_WriteString("              ");
					LCD_SetCursor(1,0);
					LCD_WriteString("1-B  2-H");
					vflag=1;
				}
				if(r!=NO_KEY)
				{
					Num=Num*10+(r-'0');
					if(Num==1||Num==2)
					{
						Sch=Num;
						Num=0;
						LCD_Clear();
						LCD_WriteChar(r);
						if(Sch==1)
						{
							Mode=11;
							vflag=0;
						}
						if(Sch==2)
						{
							Mode=12;
							vflag=0;
						}
						Flag2=0;
						clearflag=1;
						LCD_Clear();
					}
					if(r=='c')
					{
						clearflag=0;
						Num=0;
						Flag1=0;
						Flag2=0;
						vflag=0;
					}
					
				}
		  }
		  if(Fch==2)
		  {
			  if(vflag==0)
			  {
				  LCD_SetCursor(0,0);
				  LCD_WriteString("             ");
				  LCD_SetCursor(0,0);
				  LCD_WriteString("Convert To");
				  LCD_SetCursor(1,0);
				  LCD_WriteString("              ");
				  LCD_SetCursor(1,0);
				  LCD_WriteString("1-D  2-H");
				  vflag=1;
			  }
			  if(r!=NO_KEY)
			  {
				  Num=Num*10+(r-'0');
				  if(Num==1||Num==2)
				  {
					  Sch=Num;
					  Num=0;
					  LCD_Clear();
					  LCD_WriteChar(r);
					  if(Sch==1)
					  {
						  Mode=21;
						  vflag=0;
						  i=15;
					  }
					  if(Sch==2)
					  {
						  Mode=22;
						  vflag=0;
						  i=15;
					  }
					  Flag2=0;
					  clearflag=1;
					  LCD_Clear();
				  }
				  if(r=='c')
				  {
					  clearflag=0;
					  Num=0;
					  Flag1=0;
					  Flag2=-1;
					  vflag=0;
				  }
				  
			  }
		  }
		  if(Fch==3)
		  {
			  if(vflag==0)
			  {
				  LCD_SetCursor(0,0);
				  LCD_WriteString("             ");
				  LCD_SetCursor(0,0);
				  LCD_WriteString("Convert To");
				  LCD_SetCursor(1,0);
				  LCD_WriteString("              ");
				  LCD_SetCursor(1,0);
				  LCD_WriteString("1-D  2-B");
				  vflag=1;
			  }
			  if(r!=NO_KEY)
			  {
				  Num=Num*10+(r-'0');
				  if(Num==1||Num==2)
				  {
					   Sch=Num;
					   Num=0;
					   LCD_Clear();
					   LCD_WriteChar(r);
					   if(Sch==1)
					   {
						   Mode=31;
						   vflag=0;
						   i=0;
					   }
					   if(Sch==2)
					   {
						   Mode=32;
						   vflag=0;
						   i=0;
					   }
					   Flag2=0;
					   clearflag=1;
					   LCD_Clear();
				  }
				   if(r=='c')
				   {
					   clearflag=0;
					   Num=0;
					   Flag1=0;
					   Flag2=-1;
					   vflag=0;
				   }
				 
			  }
		  }
		}
			
		while(Mode==11)  // FROM DEC TO BIN
		{
			r=KEYPAD_GetKey();
			if(vflag==0)
			{
				LCD_SetCursor(0,0);
				LCD_WriteString("D:");
				LCD_SetCursor(1,0);
				LCD_WriteString("B:");
				vflag=1;
			}
			if(r!=NO_KEY)
			{
				if(clearflag==1)
				{
				    LCD_SetCursor(0,2);
					LCD_WriteString("                       ");
					LCD_SetCursor(0,2);
					clearflag=0;
				}
				if(clearflag==0)
				{
					if(r>='0'&&r<='9')
					{
						LCD_WriteChar(r);
						Num=Num*10+(r-'0');
					}
					if(r=='=')
					{
						LCD_SetCursor(1,2);
						LCD_WriteString("                   ");
						LCD_SetCursor(1,2);
						Convert_DecToBinary(Num);
						clearflag=1;
						Num=0;
					}
					if(r=='c')
					{
						Mode=0;
						Flag1=0;
						vflag=0;
						i=0;
						break;
					}
				}
			}
			
		}
		while(Mode==12)  // FROM DEC TO HEX
		{
			r=KEYPAD_GetKey();
			if(vflag==0)
			{
				LCD_SetCursor(0,0);
				LCD_WriteString("D:");
				LCD_SetCursor(1,0);
				LCD_WriteString("H:");
				vflag=1;
			}
			if(r!=NO_KEY)
			{
				if(clearflag==1)
				{
					 LCD_SetCursor(0,2);
					 LCD_WriteString("                       ");
					 LCD_SetCursor(0,2);
					clearflag=0;
				}
				if(clearflag==0)
				{
					if(r>='0'&&r<='9')
					{
						LCD_WriteChar(r);
						Num=Num*10+(r-'0');
						
					}
					if(r=='=')
					{
						LCD_SetCursor(1,2);
						LCD_WriteString("                     ");
						LCD_SetCursor(1,2);
						if(Num>32767)
						{
							Convert_DecToHex2((u16)Num);   // cast from u32 to u16
						}
						else
						{
							Convert_DecToHex(Num);
						}
						
						clearflag=1;
						Num=0;
					}
					if(r=='c')
					{
						Mode=0;
						Flag1=0;
						vflag=0;
						i=0;
						break;
					}
				}
			}
         }
		 while(Mode==21)  // FROM BIN TO DEC
		 {
			 r=KEYPAD_GetKey();
			 if(vflag==0)
			 {
				 LCD_SetCursor(0,0);
				 LCD_WriteString("B:");
				 LCD_SetCursor(1,0);
				 LCD_WriteString("D:");
				 vflag=1;
			 }
			 if(r!=NO_KEY)
			 {
				 if(clearflag==1)
				 {
					 LCD_SetCursor(0,2);
					 LCD_WriteString("                       ");
					 LCD_SetCursor(0,2);
					 clearflag=0;
				 }
				 if(clearflag==0)
				 {
					 if(r=='0'||r=='1')
					 {
						 LCD_WriteChar(r);
						 r=r-'0';
						 if(r==0)
						 {
							 CLR_BIT(Num,i);
						 }
						 if(r==1)
						 {
							 SET_BIT(Num,i);
						 }
	                     i--;
					 }
					 if(r=='=')
					 {
						 LCD_SetCursor(1,2);
						 LCD_WriteString("                       ");
						 LCD_SetCursor(1,2);
						 Convert_BinaryToDec(Num);
						 clearflag=1;
						 Num=0;
						 i=15;
					 }
					 if(r=='c')
					 {
						 Mode=0;
						 Flag1=0;
						 vflag=0;
						 i=0;
						 break;
					 }
				 }
			 }
		 }
		 while(Mode==22)  // FROM BIN TO HEX
		 {
			 r=KEYPAD_GetKey();
			 if(vflag==0)
			 {
				 LCD_SetCursor(0,0);
				 LCD_WriteString("B:");
				 LCD_SetCursor(1,0);
				 LCD_WriteString("H:");
				 vflag=1;
			 }
			 if(r!=NO_KEY)
			 {
				 if(clearflag==1)
				 {
					 LCD_SetCursor(0,2);
					 LCD_WriteString("                       ");
					 LCD_SetCursor(0,2);
					 clearflag=0;
				 }
				 if(clearflag==0)
				 {
					 if(r=='0'||r=='1')
					 {
						 LCD_WriteChar(r);
						 r=r-'0';
						 if(r==0)
						 {
							 CLR_BIT(Num,i);
						 }
						 if(r==1)
						 {
							 SET_BIT(Num,i);
						 }
						 i--;
					 }
					 if(r=='=')
					 {
						 LCD_SetCursor(1,2);
						 LCD_WriteString("                      ");
						 LCD_SetCursor(1,2);
						 if(Num>32767)
						 {
							 Convert_BinaryToHex2(Num);
						 }
						 else
						 {
							 Convert_BinaryToHex(Num);
						 }
						 clearflag=1;
						 Num=0;
						 i=15;
					 }
					 if(r=='c')
					 {
						 Mode=0;
						 Flag1=0;
						 vflag=0;
						 break;
					 }
				 }
			 }
		 }
		 while(Mode==31)  // FROM HEX TO DEC
		 {
			 r=KEYPAD_GetKey();
			 if(vflag==0)
			 {
				 LCD_SetCursor(0,0);
				 LCD_WriteString("H:");
				 LCD_SetCursor(1,0);
				 LCD_WriteString("D:");
				 vflag=1;
			 }
			 if(r!=NO_KEY)
			 {
				 if(clearflag==1)
				 {
					 LCD_SetCursor(0,2);
					 LCD_WriteString("                       ");
					 LCD_SetCursor(0,2);
					 clearflag=0;
				 }
				 if(clearflag==0)
				 {
					 
					 if(r>='0'&&r<='9')
					 {
						 if(NNflag==0)
						 {
							 LCD_SetCursor(0,2);
							 LCD_WriteChar(' ');
							 LCD_SetCursor(0,2);
						 }
						 else if(NNflag==1)
						 {
							 LCD_SetCursor(0,3);
							 LCD_WriteChar(' ');
							 LCD_SetCursor(0,3);
						 }
						  else if(NNflag==2)
						  {
							  LCD_SetCursor(0,4);
							  LCD_WriteChar(' ');
							  LCD_SetCursor(0,4);
						  }
						  else if(NNflag==3)
						  {
							  LCD_SetCursor(0,5);
							  LCD_WriteChar(' ');
							  LCD_SetCursor(0,5);
						  }
						 LCD_WriteChar(r);
						 if(i==0)
						 {
							HN=r-'0';
						 }
						 else if(i==1)
						 {
							HN2=r-'0';  
						 }
						 else if(i==2)
						 {
							LN=r-'0';
						 }
						 else if(i==3)
						 {
							LN2=r-'0';
						 }
					 }
					 else if(r=='+')
					 {
						i++;
						NNflag++;
						C=0;
					 }
					 else if(r=='A')
					 {
						
						C++;
						r=r+(C-1);
						if(NNflag==0)
						{
						    LCD_SetCursor(0,2);
						    LCD_WriteChar(' ');
						    LCD_SetCursor(0,2);
						}
					    if(NNflag==1)
					    {
						    LCD_SetCursor(0,3);
						    LCD_WriteChar(' ');
						    LCD_SetCursor(0,3);
					    }
						if(NNflag==2)
						{
							LCD_SetCursor(0,4);
							LCD_WriteChar(' ');
							LCD_SetCursor(0,4);
						}
						if(NNflag==3)
						{
							LCD_SetCursor(0,5);
							LCD_WriteChar(' ');
							LCD_SetCursor(0,5);
						}
						LCD_WriteChar(r);
					    if(i==0)
					    {
						    r=10+(r-'A');
						    HN=r;
					    }
					    if(i==1)
					    {
						    r=10+(r-'A');
						    HN2=r;
					    }
						 if(i==2)
						 {
							 r=10+(r-'A');
							 LN=r;
						 }
						 if(i==3)
						 {
							 r=10+(r-'A');
							 LN2=r;
						 }
					    if(C==6)
					    { 
						 C=0;
					    }
					}
					 else if(r=='=')
					 {
						 LCD_SetCursor(1,2);
						 LCD_WriteString("                      ");
						 LCD_SetCursor(1,2);
						 HN=(HN<<4)|HN2;
						 LN=(LN<<4)|LN2;
 						 Convert_HexToDec(HN,LN);
						 clearflag=1;
						 HN=0;
						 LN=0;
						 HN2=0;
						 LN2=0;
						 C=0;
						 NNflag=0;
						 i=0;
					 }
					 else if(r=='c')
					 {
						 Mode=0;
						 Flag1=0;
						 vflag=0;
						 NNflag=0;
						 HN=0;
						 LN=0;
						 HN2=0;
						 LN2=0;
						 C=0;
						 i=0;
						 break;
					 }
				 }
			 }
		 }
		 while(Mode==32)  // FROM HEX TO BIN
		 {
			 r=KEYPAD_GetKey();
			 if(vflag==0)
			 {
				 LCD_SetCursor(0,0);
				 LCD_WriteString("H:");
				 LCD_SetCursor(1,0);
				 LCD_WriteString("B:");
				 vflag=1;
			 }
			 if(r!=NO_KEY)
			 {
				 if(clearflag==1)
				 {
					 LCD_SetCursor(0,2);
					 LCD_WriteString("                       ");
					 LCD_SetCursor(0,2);
					 clearflag=0;
				 }
				 if(clearflag==0)
				 {
					 
					 if(r>='0'&&r<='9')
					 {
						 if(NNflag==0)
						 {
							 LCD_SetCursor(0,2);
							 LCD_WriteChar(' ');
							 LCD_SetCursor(0,2);
						 }
						 else if(NNflag==1)
						 {
							 LCD_SetCursor(0,3);
							 LCD_WriteChar(' ');
							 LCD_SetCursor(0,3);
						 }
						  else if(NNflag==2)
						  {
							  LCD_SetCursor(0,4);
							  LCD_WriteChar(' ');
							  LCD_SetCursor(0,4);
						  }
						  else if(NNflag==3)
						  {
							  LCD_SetCursor(0,5);
							  LCD_WriteChar(' ');
							  LCD_SetCursor(0,5);
						  }
						 LCD_WriteChar(r);
						 if(i==0)
						 {
							 HN=r-'0';
						 }
						 else if(i==1)
						 {
							 HN2=r-'0';
						 }
						 else if(i==2)
						 {
							 LN=r-'0';
						 }
						 else if(i==3)
						 {
							 LN2=r-'0';
						 }
					 }
					 else if(r=='+')
					 {
						 i++;
						 NNflag++;
						 C=0;
					 }
					 else if(r=='A')
					 {
						 
						 C++;
						 r=r+(C-1);
						 if(NNflag==0)
						 {
							 LCD_SetCursor(0,2);
							 LCD_WriteChar(' ');
							 LCD_SetCursor(0,2);
						 }
						 else if(NNflag==1)
						 {
							 LCD_SetCursor(0,3);
							 LCD_WriteChar(' ');
							 LCD_SetCursor(0,3);
						 }
						 else if(NNflag==2)
						 {
							 LCD_SetCursor(0,4);
							 LCD_WriteChar(' ');
							 LCD_SetCursor(0,4);
						 }
						 else if(NNflag==3)
						 {
							 LCD_SetCursor(0,5);
							 LCD_WriteChar(' ');
							 LCD_SetCursor(0,5);
						 }
						 LCD_WriteChar(r);
						 if(i==0)
						 {
							 r=10+(r-'A');
							 HN=r;
						 }
						 if(i==1)
						 {
							 r=10+(r-'A');
							 HN2=r;
						 }
						 if(i==2)
						 {
							 r=10+(r-'A');
							 LN=r;
						 }
						 if(i==3)
						 {
							 r=10+(r-'A');
							 LN2=r;
						 }
						 if(C==6)
						 {
							 C=0;
						 }
					 }
					 else if(r=='=')
					 {
						 LCD_SetCursor(1,2);
						 LCD_WriteString("                         ");
						 LCD_SetCursor(1,2);
						 HN=(HN<<4)|HN2;
						 LN=(LN<<4)|LN2;
						 Convert_HexToBinary(HN,LN);
						 clearflag=1;
						 HN=0;
						 LN=0;
						 HN2=0;
						 LN2=0;
						 C=0;
						 NNflag=0;
						 i=0;
					 }
					 else if(r=='c')
					 {
						 Mode=0;
						 Flag1=0;
						 vflag=0;
						 NNflag=0;
						 HN=0;
						 LN=0;
						 HN2=0;
						 LN2=0;
						 C=0;
						 i=0;
						 break;
					 }
				 }
			 }
		 }
		 
		 
		 
   }
}
