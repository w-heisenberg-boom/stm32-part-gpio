#include "gpio_part.h"


static int GPIO_Enable_Clock(const GPIO_Pin_t *gpio) 
{
    switch ((uint32_t)gpio->port) 
    {
#ifdef GPIOA
    case (uint32_t)GPIOA:
        __HAL_RCC_GPIOA_CLK_ENABLE();
    break;
#endif // GPIOA

#ifdef GPIOB
    case (uint32_t)GPIOB:
        __HAL_RCC_GPIOB_CLK_ENABLE();
    break;
#endif // GPIOB

#ifdef GPIOC
    case (uint32_t)GPIOC:
        __HAL_RCC_GPIOC_CLK_ENABLE();
    break;
#endif // GPIOC

#ifdef GPIOD
    case (uint32_t)GPIOD:
        __HAL_RCC_GPIOD_CLK_ENABLE();
    break;
#endif // GPIOD

#ifdef GPIOE
    case (uint32_t)GPIOE:
        __HAL_RCC_GPIOE_CLK_ENABLE();
    break;
#endif // GPIOE

    default:
        return -1;
    break;
    }

    return 0;
}

static void GPIO_Make_Struct(GPIO_InitTypeDef *_struct, const GPIO_Pin_t *gpio) 
{
    _struct->Pin = gpio->pin;

#ifdef GPIO_SPEED_FREQ_VERY_HIGH
    _struct->Speed = GPIO_SPEED_FREQ_VERY_HIGH;
#else 
    _struct->Speed = GPIO_SPEED_FREQ_HIGH;
#endif // GPIO_SPEED_FREQ_VERY_HIGH

    _struct->Mode = gpio->mode;
    _struct->Pull = gpio->pull;

#ifndef STM32F1
    _struct->Alternate = gpio->alter;
#endif // STM32F1
}



int GPIO_Pin_begin(const GPIO_Pin_t *gpio) 
{
    int err = 0;

    err = GPIO_Enable_Clock(gpio);
    if (err < 0) 
    {
        return err;
    }

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_Make_Struct(&GPIO_InitStructure, gpio);

    HAL_GPIO_Init(gpio->port, &GPIO_InitStructure);

#ifndef STM32F1
    if (!gpio->alter)
    {
#endif // STM32F1
        if ((GPIO_PinState)gpio->active == GPIO_PIN_SET)
        {
            HAL_GPIO_WritePin(gpio->port, gpio->pin, GPIO_PIN_RESET);
        }
        else if ((GPIO_PinState)gpio->active == GPIO_PIN_RESET) 
        {
            HAL_GPIO_WritePin(gpio->port, gpio->pin, GPIO_PIN_SET);
        }
#ifndef STM32F1
    }
#endif // STM32F1
    
    return 0;
}