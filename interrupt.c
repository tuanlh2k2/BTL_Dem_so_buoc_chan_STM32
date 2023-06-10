#include "stm32f10x.h"

void EXTI0_Init(void) {
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO -> EXTICR[0] &=~ (0xFUL << 0);
	EXTI -> IMR |= (1UL << 0);
	EXTI -> RTSR &=~ (1UL << 0);
	EXTI -> FTSR |= (1UL << 0);
	
	//
	__NVIC_SetPriority(EXTI0_IRQn, 0); // muc yeu tien ngat = 0(cao nhat).
	__NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI1_Init(void) {
	//RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	//AFIO -> EXTICR[1] |= (1 << 0);
	//EXTI -> IMR |= (1UL << 4);
	//EXTI -> RTSR &=~ (1UL << 4);
	//EXTI -> FTSR |= (1UL << 4);
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO -> EXTICR[0] &=~ (0xFUL << 4);
	EXTI -> IMR |= (1UL << 1);
	EXTI -> RTSR &=~ (1UL << 1);
	EXTI -> FTSR |= (1UL << 1);
	
	//
	__NVIC_SetPriority(EXTI1_IRQn, 0); // muc yeu tien ngat = 0(cao nhat).
	__NVIC_EnableIRQ(EXTI1_IRQn);
}