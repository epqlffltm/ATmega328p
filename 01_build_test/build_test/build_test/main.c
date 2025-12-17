/*
 * build_test.c
 *
 * Created: 2025-12-17 오후 6:55:35
 * 빌드 테스트
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<5);

	while (1)
	{
		PORTB |= (1<<5);
		_delay_ms(100);

		PORTB &= ~(1<<5);
		_delay_ms(100);
	}
}
