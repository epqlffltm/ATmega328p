/*
 * GPIO_example.c
 *
 * Created: 2025-12-18 오후 3:57:40
 * 버튼을 이용해 LED제어
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//PB5핀을 출렬으로
	DDRB |= (1<<PB5);//set
	
	//PC5핀을 입력으로
	DDRC &= ~(1<<PC5);//clear
	PORTC |= (1<<PC5);//set -> pull-up 사용
	MCUCR &= ~(1<<PUD);//pull-up disable을 0으로
    while (1) 
    {
		if(!(PINC & (1<<PC5)))
		{
			//PC5의 스위치가 눌렸다면
			PORTB |= (1<<PB5);
		}
		else
		{
			//PC5의 스위치가 눌리지 않았다면
			PORTB &= ~(1<<PB5);
		}
    }
}

