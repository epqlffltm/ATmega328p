/*
 * interrupt_example.c
 *
 * Created: 2025-12-23 오후 1:51:07
 * 인터럽트
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h> // bool, true, false 사용

#define LED1 PC0
#define LED2 PC1
#define LED3 PC2
#define SW PD2

#define set(R,n) R |= (1<<n)
#define clr(R,n) R&= (~(1<<n))
#define toggle(R,n) R ^= (1<<n)

//ISR과 공유하는 변수는 반드시 volatile!
volatile bool flag = true;
volatile int cnt = 0;

ISR(INT0_vect);

int main(void)
{
	sei(); // 전역 인터럽트 켜기
	
	clr(DDRD, SW);
	set(PORTD, SW); // 풀업
	
	// INT0 Falling Edge
	set(EICRA, ISC01);
	clr(EICRA, ISC00);
	set(EIMSK, INT0);
	
	set(DDRC, LED1);
	set(DDRC, LED2);
	set(DDRC, LED3);
	
	// 초기화
	clr(PORTC, LED1);
	clr(PORTC, LED2);
	clr(PORTC, LED3);
	
	while (true)
	{
		if(cnt == 0)
		{
			set(PORTC, LED1); clr(PORTC, LED2); clr(PORTC, LED3);
		}
		else if(cnt == 1)
		{
			clr(PORTC, LED1); set(PORTC, LED2); clr(PORTC, LED3);
		}
		else if(cnt == 2)
		{
			clr(PORTC, LED1); clr(PORTC, LED2); set(PORTC, LED3);
		}
		
		if(flag == true)
		{
			// 2 이상이면(2 포함) 0으로, 아니면 증가
			cnt = (cnt >= 2) ? 0 : cnt + 1;
		}
		else // flag == false
		{
			// 0 이하면(0 포함) 2로, 아니면 감소
			cnt = (cnt <= 0) ? 2 : cnt - 1;
		}
		_delay_ms(25);
	}
}

ISR(INT0_vect)
{
	_delay_ms(10); // 디바운싱
	if(!(PIND & (1<<SW)))
	{
		flag = !flag;
	}
}