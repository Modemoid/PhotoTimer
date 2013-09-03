/*
 * UV_lighter.c
 *
 * Created: 21.03.2012 16:46:53
 *  Author: Pavel Kartsev 
 *  Sorry my stupid code.
Описание ЛЦД-библиотеки смотеть http://maxembedded.wordpress.com/2011/06/16/lcd-interfacing-with-avr/ и http://homepage.hispeed.ch/peterfleury/avr-lcd44780.html
 */ 


#define F_CPU 1000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/delay.h>



#define BlueLed  0b00001000
#define GreenLed 0b00000100
//Когда ножка настроена на вход, то если PORTxy=0, то вывод в режиме Hi-Z. Если PORTxy=1 то вывод в режиме PullUp с подтяжкой резистором в 100к до питания.




#include "lcd.h"
//#include "keyboard.h"
//#include "keyboard.c"
char LightState, RunFlag = 0, ledstate = 1;//ledstate say hi level of lo used for control leds 
int LedBlueTimer = 0,LedGreenTimer = 0; //attantion! time variables save in 1/10 sec!

#warning LegBlueTimer and LegGreenTimer save time in 1/10 sec!;
//unsigned int TicTimerCounter;
char KeyRead()
{
	char btn,n,l1;
	//начало опроса кнопок	
		btn=0;
		n = 0b00000001;
		PORTD = n;
		_delay_ms(5);				/*задержка*/	
		l1 = PIND&0b11110000;
		if (l1==0b00010000){btn=1;}
		if (l1==0b00100000){btn=2;}
		if (l1==0b01000000){btn=3;}
		if (l1==0b10000000){btn=4;}


		n = 0b00000010;
		PORTD = n;
		_delay_ms(5);				/*задержка*/	
		l1 = PIND&0b11110000;
		if (l1==0b00010000){btn=5;}
		if (l1==0b00100000){btn=6;}
		if (l1==0b01000000){btn=7;}
		if (l1==0b10000000){btn=8;}
		
		
		n = 0b00000100;
		PORTD = n;
		_delay_ms(5);				/*задержка*/	
		l1 = PIND&0b11110000;
		if (l1==0b00010000){btn=9;}
		if (l1==0b00100000){btn=10;}
		if (l1==0b01000000){btn=11;}
		if (l1==0b10000000){btn=12;}

		n = 0b000001000;
		PORTD = n;
		_delay_ms(5);				/*задержка*/	
		l1 = PIND&0b11110000;
		if (l1==0b00010000){btn=13;}
		if (l1==0b00100000){btn=14;}
		if (l1==0b01000000){btn=15;}
		if (l1==0b10000000){btn=16;}

	//конец опроса кнопок	
}
ISR(TIMER1_COMPA_vect )// Timer/Counter1 Compare Match A 
	{
	TCNT1H=0xcf;//direct set counter register
	TCNT1L=0x2c;//direct set counter register
	
	if (ledstate == 0)
	{
	if (RunFlag == 1)
		{
			if (LedBlueTimer>0 && LedGreenTimer>0)
			{
				PORTC = PORTC&0b11110011;//pcX to gnd
				LedBlueTimer--;
				LedGreenTimer--;
			}
			if (LedBlueTimer>0 && LedGreenTimer==0)
			{
				PORTC = PORTC&0b11111011;//pcX to gnd
				PORTC = PORTC|0b00001000;//pcX to hi
				//need clear bit
				LedBlueTimer--;
			}
			if (LedBlueTimer==0 && LedGreenTimer>0)
			{
				PORTC = PORTC&0b11110111;//pcX to gnd
				PORTC = PORTC|0b00000100;//pcX to hi
				LedGreenTimer--;
			}
			if (LedBlueTimer==0 && LedGreenTimer==0)
			{
				//need clear bits
				RunFlag=0;
				PORTC = PORTC|0b00001100;//pcX to hi
			}
					        
		}//end of runfalg=1		
		
		if (RunFlag == 2)
		{
			if (LedBlueTimer>0 && LedGreenTimer==0)
			{
				PORTC = PORTC&0b11111011;//pcX to gnd
				PORTC = PORTC|0b00001000;//pcX to hi
				//need clear bit
				LedBlueTimer--;

			}
			if (LedGreenTimer>0)
			{
				PORTC = PORTC&0b11110111;//pcX to gnd
				PORTC = PORTC|0b00000100;//pcX to hi
				LedGreenTimer--;
			}
			if (LedBlueTimer==0 && LedGreenTimer==0)
			{
				RunFlag=0;
				PORTC = PORTC|0b00001100;//pcX to hi
			}
		}
	}
	
	if (ledstate == 1)
	{
	if (RunFlag == 1)
		{
			if (LedBlueTimer>0 && LedGreenTimer>0)
			{
				PORTC = PORTC|0b00001100;//pcX to hi
				LedBlueTimer--;
				LedGreenTimer--;
			}
			if (LedBlueTimer>0 && LedGreenTimer==0)
			{
				PORTC = PORTC|0b00000100;
				PORTC = PORTC&0b11110111;
				//PORTC = PORTC&0b11111011;//pcX to gnd
				//PORTC = PORTC|0b00001000;//pcX to hi
				//need clear bit
				LedBlueTimer--;
			}
			if (LedBlueTimer==0 && LedGreenTimer>0)
			{
				PORTC = PORTC|0b00001000;
				PORTC = PORTC&0b11111011;
				//PORTC = PORTC&0b11110111;//pcX to gnd
				//PORTC = PORTC|0b00000100;//pcX to hi
				LedGreenTimer--;
			}
			if (LedBlueTimer==0 && LedGreenTimer==0)
			{
				//need clear bits
				RunFlag=0;
				PORTC = PORTC&0b11110011;
				//PORTC = PORTC|0b00001100;//pcX to hi
			}
					        
		}//end of runfalg=1		
		
		if (RunFlag == 2)
		{
			if (LedBlueTimer>0 && LedGreenTimer==0)
			{
				PORTC = PORTC|0b00000100;
				PORTC = PORTC&0b11110111;
				//PORTC = PORTC&0b11111011;//pcX to gnd
				//PORTC = PORTC|0b00001000;//pcX to hi
				//need clear bit
				LedBlueTimer--;

			}
			if (LedGreenTimer>0)
			{
				PORTC = PORTC|0b00001000;
				PORTC = PORTC&0b11111011;
				//PORTC = PORTC&0b11110111;//pcX to gnd
				//PORTC = PORTC|0b00000100;//pcX to hi
				LedGreenTimer--;
			}
			if (LedBlueTimer==0 && LedGreenTimer==0)
			{
				RunFlag=0;
				PORTC = PORTC&0b11110011;
				//PORTC = PORTC|0b00001100;//pcX to hi
			}
		}
	}
	
	}		
	//}
	

int main(void) 
{
	char btn,n,l1;
	//char n,btn,LedBlueTimer;
	//char l1,n;//опрос строчек
	char buffer[15],bb; //для дисплея - чтоб переводить в строковую переменную
	unsigned char keyResult;
	
	//configuring ports
	DDRC = 0xff; //direction 1-out 0-in
	if (ledstate == 0){
	PORTC = 0b11111100 ; // pull-up 0-off 1-on
	}
	if (ledstate == 1){
	PORTC = 0b11000000 ; // pull-up 0-off 1-on
	}
		
	DDRD = 0b00001111 ;//direction 1-out 0-in
	PORTD = 0; // pull-up 0-off 1-on
	//end configuring ports
	
	//timer set up
	TCCR1A=0b00000000; //add wgm12=1 wgm13=0 update ocra1 on compare mach, count to ocr1a
	TCCR1B=0b00001010; //timer use 1/8 clock
	OCR1AH=0x30;//timer top set
	OCR1AL=0xd4;//timer top set
	TCNT1H=0xcf;//direct set counter register
	TCNT1L=0x2c;//direct set counter register
	TIMSK=0b00010000;//enabling ocr1a on compare interupt
	//end timer set up
	
	sei();
	lcd_init(LCD_DISP_ON);  //потом вЫключить //инициализация дисплея, курсора не видно 
								 // другие опции см в lcd_init(), view lcd.h file
	
    //KEYB_Init(); // иниуиализауия клавиатуры
	while(1)                     // бесконечный цикл 
    {
		//начало опроса кнопок	
		btn=0;
		n = 0b00000001;
		PORTD = n;
		_delay_ms(5);				/*задержка*/	
		l1 = PIND&0b11110000;
		if (l1==0b00010000){btn=1;}
		if (l1==0b00100000){btn=2;}
		if (l1==0b01000000){btn=3;}
		if (l1==0b10000000){btn=4;}


		n = 0b00000010;
		PORTD = n;
		_delay_ms(5);				/*задержка*/	
		l1 = PIND&0b11110000;
		if (l1==0b00010000){btn=5;}
		if (l1==0b00100000){btn=6;}
		if (l1==0b01000000){btn=7;}
		if (l1==0b10000000){btn=8;}
		
		
		n = 0b00000100;
		PORTD = n;
		_delay_ms(5);				/*задержка*/	
		l1 = PIND&0b11110000;
		if (l1==0b00010000){btn=9;}
		if (l1==0b00100000){btn=10;}
		if (l1==0b01000000){btn=11;}
		if (l1==0b10000000){btn=12;}

		n = 0b000001000;
		PORTD = n;
		_delay_ms(5);				/*задержка*/	
		l1 = PIND&0b11110000;
		if (l1==0b00010000){btn=13;}
		if (l1==0b00100000){btn=14;}
		if (l1==0b01000000){btn=15;}
		if (l1==0b10000000){btn=16;}

	//конец опроса кнопок	
//btn= KeyRead();
		

//show all on lcd.
lcd_clrscr();

lcd_gotoxy(0,0);
bb = LedBlueTimer/10;
itoa(bb,buffer,10); //LedBlueTimer
lcd_puts(buffer);
lcd_puts(".");
bb = LedBlueTimer%10;
itoa(bb,buffer,10); //LedBlueTimer
lcd_puts(buffer);
lcd_gotoxy(6,0);
lcd_puts("B");
///////////////////////распутать все на дисплее в первой строке
lcd_gotoxy(9,0);
bb = LedGreenTimer/10;
itoa(bb,buffer,10);
lcd_puts(buffer);
lcd_puts(".");
bb = LedGreenTimer%10;
itoa(bb,buffer,10);
lcd_puts(buffer);
lcd_gotoxy(14,0);
lcd_puts("G");

switch(btn)
	{
		case 1:
			{
				
				if (LedBlueTimer >= 50)//if <50 step =1, else 10
				{
					LedBlueTimer = LedBlueTimer + 10;
				}
				if (LedBlueTimer < 50)
				{
					LedBlueTimer++;
				}
		
		
			break;
			}
		case 2:
			{
				if (LedGreenTimer >= 50)//if <50 step =1, else 10
				{
					LedGreenTimer = LedGreenTimer + 10;
				}
				if (LedGreenTimer < 50)
				{
					LedGreenTimer++;
				}
			break;
			}
		case 3://Clear Blue and green timer
			{
			LedBlueTimer = 25;
			LedGreenTimer = 30;
			break;
			}
		case 4://turn on&off red into enliger
			{
			PORTC = PORTC^0b000010000;
			break;
			}
		case 5:
			{
				if (LedBlueTimer>0){
			LedBlueTimer--;//decrease BlueLed timer
				}			
			break;
			}
		case 6:
			{
				if (LedGreenTimer>0){
			LedGreenTimer--;//decrease GreenLed Timer
				}			
			break;
			}
		case 7:// run timer
			{
				RunFlag = 1;
			break;
			}
		case 8://turn on&off room red light
			{
			PORTC = PORTC^0b000100000;
			break;
			}
		case 9://blue light
			{
				PORTC = PORTC^0b000000100;
			break;
			}
		case 10://green light
			{
				PORTC = PORTC^0b000001000;
			break;
			}
		case 11://run Green, then Blue
			{
				RunFlag = 2;
				
			break;
			}	
		case 12:// MotorCW
			{
				PORTC = PORTC&0b11111110;//pc0 to gnd
				PORTC = PORTC|0b00000010;//pc1 to hi
				
				
				//PORTC = PORTC^0b00000001;
			break;
			}	
		case 13://
			{
			break;
			}
		case 14://
			{
			break;
			}
		case 15://
			{
				
			break;
			}
		case 16:// MotorCCW
			{	
				//PORTC = PORTC|0b00000010;
				PORTC = PORTC&0b11111101;//pc1 to gnd
				PORTC = PORTC|0b00000001;//pc0 to hi
				
			break;
			}
		case 0:
			{
				PORTC = PORTC&0b11111100;//pc0 and pc1 to gnd
				break;
			}
			break;
	}
//показываем все на мониторчик

{
	n=PORTC;
if (n&0b000010000)	
	{
	lcd_gotoxy(5,1);
	lcd_puts("r");
	//lcd_gotoxy(0,1);
    }
	else
	{
	lcd_gotoxy(5,1);
	lcd_puts("R");
	}
if (n&0b000100000)	//room Light
	{
	lcd_gotoxy(6,1);
	lcd_puts("y");
	//lcd_gotoxy(0,1);
    }
	else
	{
	lcd_gotoxy(6,1);
	lcd_puts("Y");
	}
if (n&0b000000100)	
	{
	lcd_gotoxy(7,0);
	lcd_puts("-");
	///////lcd_gotoxy(0,1);
    }
	else
	{
	lcd_gotoxy(7,0);
	lcd_puts("+");
	}
if (n&0b000001000)	
	{
	lcd_gotoxy(15,0);
	lcd_puts("-");
	//lcd_gotoxy(0,1);
    }
	else
	{
	lcd_gotoxy(15,0);
	lcd_puts("+");
	}

if (RunFlag == 1)
	{
	lcd_gotoxy(9,1);
	lcd_puts("RUN G+B");	
	}
if (RunFlag == 2)
	{
	lcd_gotoxy(9,1);
	lcd_puts("RUN G>B");	
	}
}//end show all on lcd	

	
				
//всякая тестовая фигня.		
	//	itoa(tc1,buffer, 2);           //обновить буфер int,char[15],разрядность преобразования
	//	lcd_gotoxy(0,0);          //поставить курсор pos,line
    //	lcd_puts(buffer);

		lcd_gotoxy(0,1);// show into start of second line number of pressed button
		itoa(btn,buffer, 10);           //обновить буфер int,char[15],разрядность преобразования
		lcd_puts(buffer);
		
		
		/* lcd_gotoxy(9,1); // it work! in show portd on screen
		n= PORTD;
		itoa(n,buffer, 2);           //обновить буфер int,char[15],разрядность преобразования
		lcd_puts(buffer);
*/

//	PORTC= PORTC 0b000000100;
	_delay_ms(200);				/*задержка*/	
	
//	PORTC = 0b000001000;
//	_delay_ms(100);				/*задержка*/	

	}	
	
	



    
		
	
}