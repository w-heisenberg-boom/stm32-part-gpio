#ifndef GPIO_PART_H
#define GPIO_PART_H

#include <stdint.h>
#include <stdlib.h>

#include <stm32f407xx.h>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_gpio.h>


#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#endif

typedef struct 
{
	GPIO_TypeDef *port;
	uint32_t pin;
    uint32_t mode;
	uint32_t active;
	uint32_t pull;
    uint32_t alter;
} GPIO_Pin_t;

int GPIO_Pin_begin(const GPIO_Pin_t *gpio);


#endif // GPIO_PART_H