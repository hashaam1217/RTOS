#include "uart.h"


#define GPIOAEN			(1U<<0) //the bit we want to enable
#define UART2EN	        (1U<<17)
#define CR1_TE			(1U<<3) //Enables TX in USART
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)

#define SYS_FREQ 		16000000 // 16 MHz
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE   115200

static uint32_t compute_uart_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void set_uart_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void uart_write(int ch);

int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}

void uart_tx_init(void)
{
	//enable clock access
	RCC->AHB1ENR |= GPIOAEN;
	//Finding GPIO Pins for USART2

	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |=  (1U<<5);
	//Set alternate function type to AF7 (UART2_TX)
	GPIOA->AFR[0] |=  (1U<<8);
	GPIOA->AFR[0] |=  (1U<<9);
	GPIOA->AFR[0] |=  (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);
	//Enable clock access to UART
	RCC->APB1ENR |= UART2EN;
	//Configure baudrate
	set_uart_baudrate(APB1_CLK, UART_BAUDRATE);

	//Configure the transfer direction
	USART2->CR1 = CR1_TE;

	//Enable UART module
	USART2->CR1 |= CR1_UE;
}



static void uart_write(int ch)
{
	//Ensuring clear TX Register
	while (!(USART2->SR & SR_TXE)){}

	//TX
	USART2->DR = (ch & 0xFF);
}

static void set_uart_baudrate(uint32_t periph_clk, uint32_t baudrate)
{
	USART2->BRR = compute_uart_baudrate(APB1_CLK, UART_BAUDRATE);
}

static uint32_t compute_uart_baudrate(uint32_t periph_clk, uint32_t baudrate)
{
	return (periph_clk + (baudrate/2U))/baudrate;
}
