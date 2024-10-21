#ifndef TIMEBASE_H_
#define TIMEBASE_H_
#include "stm32f446xx.h"
#include <stdint.h>

void delay(uint32_t delay);
void timebase_init(void);
#endif
