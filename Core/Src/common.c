/**
  ******************************************************************************
  * @file           : common.c
  * @brief          : Common used routines and printf() supply
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
 
 
/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Private function prototypes -----------------------------------------------*/
__STATIC_INLINE uint32_t ITM_SendCharChannel(uint32_t ch, uint32_t channel);
__STATIC_INLINE void _putc(uint8_t ch);










////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void) {
  while (1) {
    //
  }
}



/**
  * @brief  This function blink a LED.
  * @param  None
  * @retval None
  */
void LED_Blink(GPIO_TypeDef* port, uint16_t pinSource) {
  (PIN_LEVEL(port, pinSource)) ? PIN_L(port, pinSource) : PIN_H(port, pinSource);
}







/********************************************************************************/
/*                         printf() output supply block                         */
/********************************************************************************/
/**
  * @brief  Sends a symbol into ITM channel. It could be cought with SWO pin on an MC. 
  * @param ch: a symbol to be output
  * @param channel: number of an ITM channel
  * @retval the same symbol 
  */
__STATIC_INLINE uint32_t ITM_SendCharChannel(uint32_t ch, uint32_t channel) {
   /* ITM enabled and ITM Port enabled */
  if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) && ((ITM->TER & (1 << channel)) != 0UL)) {
    while (ITM->PORT[channel].u32 == 0UL) {
      __NOP();
    }
    ITM->PORT[channel].u8 = (uint8_t)ch;
  }
  return (ch);
}




/**
  * @brief  Sends a symbol into USART. 
  * @param device: a pointer USART_TypeDef
  * @param ch: a symbol to be output
  * @param check: a pointer to a BitBand check bit
  * @retval none: 
  */
__STATIC_INLINE void _putc(uint8_t ch) {
  if (ch == '\n') _putc('\r');

  #ifdef SWO_ITM
    ITM_SendCharChannel(ch, 0);
  #endif

  #ifdef SWO_USART
    USART1->DR = ch;
    check = 0;
    while (!check) {
      check = PREG_CHECK(USART1->SR, USART_SR_TXE_Pos);
    }
  #endif
}




/**
  * @brief An interpretation of the __weak system _write()
  * @param file: IO file
  * @param ptr: pointer to a char(symbol) array
  * @param len: length oa the array
  * @retval length of the array 
  */
int _write(int32_t file, char *ptr, int32_t len) {
  // static uint32_t check = 0;
  for(int32_t i = 0 ; i < len ; i++) {
    _putc(*ptr++);  
  }
	return len;
}





#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line) { 
  printf("Wrong parameters value: file %s on line %d\n", file, line);
}
#endif /* USE_FULL_ASSERT */
