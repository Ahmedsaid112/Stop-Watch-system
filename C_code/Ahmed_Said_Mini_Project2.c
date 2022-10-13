/*
 * Ahmed_Said_Mini_Project2.c
 *
 *  Created on: Sep 19, 2022
 *      Author: Ahmed Said
 */
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
unsigned char sec1, sec2;
unsigned char min1, min2;
unsigned char hours1, hours2;
void INT0_Init(void)
{
	DDRD &= ~(1<<2);
	PORTD |= (1<<2);
	MCUCR |= (1<<1);
	GICR |= (1<<6);
	SREG |= (1<<7);
}
void INT1_Init(void)
{
	DDRD &= ~(1<<3);
	MCUCR |= (1<<2) | (1<<3);
	GICR |= (1<<7);
	SREG |= (1<<7);
}
void INT2_Init(void)
{
	DDRB &= ~(1<<2);
	PORTB |= (1<<2);
	MCUCSR &= ~(1<<6);
	GICR |= (1<<5);
	SREG |= (1<<7);
}
void Timer1_Init_Compare_Mode(void)
{
	TCNT1 = 0;
	OCR1A = 977;
	TCCR1A |= (1<<3);
	TCCR1B |= (1<<3) | (1<<0) | (1<<2);
	TIMSK |= (1<<4);
}
ISR(INT0_vect)
{
	hours2 = 0;
	hours1 = 0;
	min2 = 0;
	min1 = 0;
	sec2 = 0;
	sec1 = 0;
}
ISR(INT1_vect)
{
	TCCR1B &= 0xF8;
}
ISR(INT2_vect)
{
	TCCR1B |= (1<<0) | (1<<2);
}
ISR(TIMER1_COMPA_vect)
{
	if((hours2 == 9) && (hours1 == 9) && (min2 == 5) && (min1 == 9) && (sec2 == 5) && (sec1 == 9))
	{
		hours2 = 0;
		hours1 = 0;
		min2 = 0;
		min1 = 0;
		sec2 = 0;
		sec1 = 0;
	}
	else
	{
		sec1++;
		if(sec1 == 10)
		{
			sec1 = 0;
			sec2++;
			if(sec2 == 6)
			{
				sec2 = 0;
				min1++;
				if(min1 == 10)
				{
					min1 = 0;
					min2++;
					if(min2 == 6)
					{
						min2 = 0;
						hours1++;
						if(hours1 == 10)
						{
							hours1 = 0;
							hours2++;
						}
					}
				}
			}
		}
	}

}
int main(void)
{
	/*Initialization Code*/
	DDRC |= 0x0F;
	PORTC &= 0xF0;
	DDRA |= 0x3F;
	INT0_Init();
	INT1_Init();
	INT2_Init();
	Timer1_Init_Compare_Mode();
	/*Application Code*/
	while(1)
	{
		PORTA = (1<<0);
		PORTC = (PORTC & 0xF0) | (sec1 & 0x0F);
		_delay_ms(2);
		PORTA = (1<<1);
		PORTC = (PORTC & 0xF0) | (sec2 & 0x0F);
		_delay_ms(2);
		PORTA = (1<<2);
		PORTC = (PORTC & 0xF0) | (min1 & 0x0F);
		_delay_ms(2);
		PORTA = (1<<3);
		PORTC = (PORTC & 0xF0) | (min2 & 0x0F);
		_delay_ms(2);
		PORTA = (1<<4);
		PORTC = (PORTC & 0xF0) | (hours1 & 0x0F);
		_delay_ms(2);
		PORTA = (1<<5);
		PORTC = (PORTC & 0xF0) | (hours2 & 0x0F);
		_delay_ms(2);
	}
}

