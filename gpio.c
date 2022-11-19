#include "gpio.h"
#define GPIOx_TYPER_OFFSET (0x04/4)
#define GPIOx_SPEED_OFFSET (0x08/4)
#define GPIOx_ODR_OFFSET (0x14/4)
#define GPIOx_IDR_OFFSET (0x10/4)
void AssertValid(void)
{
  __asm("NOP");  //assembleur , "no operation"
}
void AssertFailed(void)
{
  while(1){}
}

#define EMB_ASSERT(Exp)  ((Exp) ? AssertValid() : AssertFailed())

void GPIO_Clock_Enable(uint32_t *GPIOx)
{
  EMB_ASSERT(GPIOx == GPIOA || GPIOx == GPIOB || GPIOx == GPIOC || GPIOx == GPIOD);
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
 void GPIO_Config(uint32_t *GPIOx, uint8_t Pin, uint8_t Mode, uint8_t Type, uint8_t Speed)
 {
   EMB_ASSERT(GPIOx == GPIOA || GPIOx == GPIOB || GPIOx == GPIOC || GPIOx == GPIOD);
   EMB_ASSERT(Pin >= PIN0 && Pin <= PIN15);
   EMB_ASSERT(Mode >= INPUT && Mode <= ANALOG_INPUT);
   EMB_ASSERT(Type == OUTPUT_PUSH_PULL || Type == OUTPUT_OPEN_DRAIN);
   EMB_ASSERT(Speed >= LOW_SPEED && Speed <= VERY_HIGH_SPEED);
    
   *GPIOx &= ~(0x3<<Pin*2);    
   *GPIOx |= (Mode<< Pin*2);
   if (Mode == OUTPUT)
   {
   *(GPIOx + GPIOx_TYPER_OFFSET ) &= ~(1<<Pin);
   *(GPIOx + GPIOx_TYPER_OFFSET ) |= (Type<< Pin) ;
   *(GPIOx + GPIOx_SPEED_OFFSET) &= ~(0x3<<Pin*2);
   *(GPIOx + GPIOx_SPEED_OFFSET) |= (Speed << Pin*2);
   
   }
   else
   {
   } 
 }
void GPIO_Write_Port(uint32_t *GPIOx, uint16_t PortValue)
{
   EMB_ASSERT(GPIOx == GPIOA || GPIOx == GPIOB || GPIOx == GPIOC || GPIOx == GPIOD);
   EMB_ASSERT(PortValue >= 0 && PortValue <= 65535);

  *(GPIOx + GPIOx_ODR_OFFSET) = PortValue;
}
void GPIO_Write_Pin(uint32_t *GPIOx, uint8_t Pin, uint8_t PinValue)
{
  EMB_ASSERT(GPIOx == GPIOA || GPIOx == GPIOB || GPIOx == GPIOC || GPIOx == GPIOD);
  EMB_ASSERT(Pin >= PIN0 && Pin <= PIN15);
  EMB_ASSERT(PinValue == 0 || PinValue == 1);
  *(GPIOx + GPIOx_ODR_OFFSET) &= ~(1<<Pin);
  *(GPIOx + GPIOx_ODR_OFFSET) |= (PinValue<<Pin);
}
uint16_t GPIO_Read_Port(uint32_t *GPIOx)
{
  EMB_ASSERT(GPIOx == GPIOA || GPIOx == GPIOB || GPIOx == GPIOC || GPIOx == GPIOD);
  
  return (*(GPIOx + GPIOx_IDR_OFFSET));
}
uint8_t GPIO_Read_Pin(uint32_t *GPIOx, uint8_t Pin)
{
  EMB_ASSERT(GPIOx == GPIOA || GPIOx == GPIOB || GPIOx == GPIOC || GPIOx == GPIOD);
  EMB_ASSERT(Pin >= PIN0 && Pin <= PIN15);
  return ((*(GPIOx + GPIOx_IDR_OFFSET) >> Pin) & 1 );
}
