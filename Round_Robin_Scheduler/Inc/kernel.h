#ifndef KERNEL_H_
#define KERNEL_H_
#include "stm32f446xx.h"
#include <stdint.h>
uint8_t kernel_add_threads(void(*task0)(void), void(*task1)(void), void(*task2)(void), void(*task3)(void), void(*task4)(void), void(*task5)(void), void(*task6)(void), void(*task7)(void), void(*task8)(void), void(*task9)(void));
void kernel_init(void);
void kernel_launch(uint32_t quanta);
#endif
