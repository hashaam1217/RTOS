#include "led.h"

#define GPIOAEN			(1U<<0) //the bit we want to enable
#define LED_PIN 		(1U<<5)
void led_init(void)
{
	/*Enable clock access to led port A*/
	// Turning on AHB1 clock bus
	RCC->AHB1ENR |= GPIOAEN;
	/*Set led pin as output pin*/
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);
}

void led_on(void)
{
	/*Setting LED as high PA5*/
	// Using output data register
	GPIOA->ODR |= LED_PIN;
}

void led_off(void)
{
	/*Setting LED as low PA5*/
	GPIOA->ODR &= ~LED_PIN;

}
