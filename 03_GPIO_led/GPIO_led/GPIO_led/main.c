/*
 * GPIO_led_final.c
 *
 * 동작: 
 * - 스위치 PC5를 누르면 -> LED PB5 켜짐 (PC3 꺼짐)
 * - 스위치 PC4를 누르면 -> LED PC3 켜짐 (PB5 꺼짐)
 * - 두 LED는 동시에 켜지지 않음 (상호 배제)
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // --- 1. 포트 입출력 방향 설정 (DDR) ---
    
    // LED 설정 (출력: 1)
    DDRB |= (1<<PB5); // PB5 LED 출력 설정
    DDRC |= (1<<PC3); // PC3 LED 출력 설정
    
    // 스위치 설정 (입력: 0)
    DDRC &= ~(1<<PC5); // PC5 스위치 입력
    DDRC &= ~(1<<PC4); // PC4 스위치 입력
    
    // --- 2. 초기 상태 설정 (PORT) ---
    
    // 스위치 풀업 저항 활성화 (입력 핀에 1 쓰기)
    // 주의: PC3(LED)는 건드리지 않고 PC4, PC5만 1로 설정해야 함
    PORTC |= (1<<PC5);
    PORTC |= (1<<PC4);
    
    // 처음에는 LED를 모두 꺼둠 (선택 사항)
    PORTB &= ~(1<<PB5);
    PORTC &= ~(1<<PC3);
	
	// PUD 비트 클리어 (풀업 활성화, 보통 기본값이 0이라 생략 가능하지만 명시)
	MCUCR &= ~(1<<PUD);

    while (1) 
    {
        // --- 상황 1: PC5 스위치가 눌렸을 때 ---
        if (!(PINC & (1<<PC5))) 
        {
            _delay_ms(20); // 채터링(떨림) 방지
            if (!(PINC & (1<<PC5))) // 진짜 눌린 게 맞다면
            {
                // 동작: PB5 켜고, PC3 끈다 (하나만 켜지게)
                PORTB |= (1<<PB5);  // PB5 ON
                PORTC &= ~(1<<PC3); // PC3 OFF
            }
        }
        
        // --- 상황 2: PC4 스위치가 눌렸을 때 ---
        else if (!(PINC & (1<<PC4))) 
        {
            _delay_ms(20); // 채터링 방지
            if (!(PINC & (1<<PC4))) 
            {
                // 동작: PC3 켜고, PB5 끈다
                PORTC |= (1<<PC3);  // PC3 ON
                PORTB &= ~(1<<PB5); // PB5 OFF
            }
        }
    }
    
    return 0;
}