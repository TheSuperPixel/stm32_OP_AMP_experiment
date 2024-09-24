#include "stm32f10x.h"                  // Device header

void beep_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void beep_change(int sound){
	if (sound==1)
    {
			GPIO_SetBits(GPIOB, GPIO_Pin_6);//??
    }
		if (sound==0)
    {
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);//??
		}
}
