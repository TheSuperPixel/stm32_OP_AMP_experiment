#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//使能AFIO时钟
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  // 禁用JTAG-DP使能SW-DPIO，让pb15使用
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_6|GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_15| GPIO_Pin_6);
}
void LED_change(int color){
	if (color==0)
    {
			GPIO_SetBits(GPIOA, GPIO_Pin_8);//??
			GPIO_SetBits(GPIOA, GPIO_Pin_15);//??
			GPIO_SetBits(GPIOA, GPIO_Pin_6);//??
    }
		if (color==1)
    {
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);//??
			GPIO_SetBits(GPIOA, GPIO_Pin_15);//??
			GPIO_SetBits(GPIOA, GPIO_Pin_6);//??
    }
		if (color==2)
    {
			GPIO_SetBits(GPIOA, GPIO_Pin_8);//??
			GPIO_ResetBits(GPIOA, GPIO_Pin_15);//??
			GPIO_SetBits(GPIOA, GPIO_Pin_6);//??
    }
		if (color==3)
    {
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);//??
			GPIO_ResetBits(GPIOA, GPIO_Pin_15);//??
			GPIO_SetBits(GPIOA, GPIO_Pin_6);//??
    }
		if (color==4)
    {
			GPIO_SetBits(GPIOA, GPIO_Pin_8);//??
			GPIO_SetBits(GPIOA, GPIO_Pin_15);//??
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);//??
    }
		if (color==5)
    {
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);//??
			GPIO_SetBits(GPIOA, GPIO_Pin_15);//??
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);//??
    }
		if (color==6)
    {
			GPIO_SetBits(GPIOA, GPIO_Pin_8);//??
			GPIO_ResetBits(GPIOA, GPIO_Pin_15);//??
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);//??
    }
		if (color==7)
    {
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);//??
			GPIO_ResetBits(GPIOA, GPIO_Pin_15);//??
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);//??
    }
}
