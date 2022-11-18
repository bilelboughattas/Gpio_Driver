#include "gpio.h"
#define GPIOx_Moder_Offset (uint32_t)0x00  
#define GPIOx_Typer_Offset (uint32_t)0x01

void GPIO_Clock_Enable(uint32_t *GPIOx)
{
  assert(GPIOx == GPIOA || GPIOx == GPIOB || GPIOx == GPIOC || GPIOx == GPIOD);
  uint16_t *RCC_AHB1 = (uint16_t *)(0x40023830);
  *RCC_AHB1 = 0x00000000;
  if (GPIOx == GPIOA)
  {
    *RCC_AHB1 |= (1<<0);
  }
  else  if (GPIOx == GPIOB)
  {
    *RCC_AHB1 |= (1<<1);
  }
   else  if (GPIOx == GPIOC)
  {
    *RCC_AHB1 |= (1<<2);
  }
  
   else  if (GPIOx == GPIOD)
  {
    *RCC_AHB1 |= (1<<3);
  }
}
 void GPIO_Config(uint32_t *GPIOx, uint8_t Pin, uint8_t Mode, uint8_t Type)
 {
   assert(GPIOx == GPIOA || GPIOx == GPIOB || GPIOx == GPIOC || GPIOx == GPIOD);
   assert(Pin >= PIN0 && Pin <= PIN15);
   assert(Mode == INPUT || Mode == OUTPUT || Mode == ALTERNATE || Mode == ANALOG_INPUT);
   assert(Type == OUTPUT_PUSH_PULL || Type == OUTPUT_OPEN_DRAIN);
    
   *(GPIOx + GPIOx_Moder_Offset) &= ~(1<<Pin*2);  ;
   *(GPIOx + GPIOx_Typer_Offset) &= ~(1<<Pin);
  *(GPIOx + GPIOx_Moder_Offset) |= (Mode<< Pin*2) ;

  *(GPIOx + GPIOx_Typer_Offset) |= (Type<< Pin) ;


 }
 
