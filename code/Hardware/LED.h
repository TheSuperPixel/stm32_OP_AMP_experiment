#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"                  // Device header

void LED_Init(void);
void LED_change(int color);
#endif
