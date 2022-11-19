/**
  ******************************************************************************
  * @file    main.c
  * @author  Bilel Boughattas
  * @brief   GPIO DRIVER 
  * @version V1.0.0
  * @date    14-11-2022
  *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/*----------------Private Functions Prototype---------------------------------*/
//static void delay(unsigned int delay);

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

int main()
{ 
  GPIO_Clock_Enable(GPIOD);
  GPIO_Config(GPIOD,PIN12,OUTPUT,OUTPUT_PUSH_PULL,VERY_HIGH_SPEED);
  GPIO_Config(GPIOD,PIN10,INPUT,OUTPUT_PUSH_PULL,VERY_HIGH_SPEED);

  GPIO_Write_Port(GPIOD,8);
  GPIO_Write_Pin(GPIOD,PIN12,SET);
  GPIO_Write_Pin(GPIOD,PIN12,RESET);
  uint8_t ReadGpioPin = GPIO_Read_Pin(GPIOD,PIN9);
  
  while(1)
  {
   
  }
}



/**************************************END OF FILE**************************************/
