/**
  ******************************************************************************
  * @file           : common.h
  * @brief          : Header for common.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_H
#define __COMMON_H

#ifdef __cplusplus
  extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
    
/* Private typedef -----------------------------------------------------------*/
struct __FILE {
  int handle;
  /* Whatever you require here. If the only file you are using is */
  /* standard output using printf() for debugging, no file handling */
  /* is required. */
};


/* Private defines -----------------------------------------------------------*/
#define GPIO_IDR_Offset         (uint16_t)0x0010
#define GPIO_ODR_Offset         (uint16_t)0x0014
#define GPIO_BSRR_Offset        (uint16_t)0x0018


/* Private macro -------------------------------------------------------------*/
#define GET_PERIPH_BB_ADDR(addr, periphOffset, wordOffset)      (PERIPH_BB_BASE + ((addr + periphOffset) * 32U) + (wordOffset * 4U))
#define SET_PERIPH_BB_VAL(addr, periphOffset, wordOffset, key)  (*(uint32_t*)(GET_PERIPH_BB_ADDR(addr, periphOffset, wordOffset)) = key)
#define GET_PERIPH_BB_VAL(addr, periphOffset, wordOffset)       (*(uint32_t*)(GET_PERIPH_BB_ADDR(addr, periphOffset, wordOffset)))

#define GET_SRAM_BB_ADDR(addr, offset)                          (SRAM_BB_BASE + (addr * 32U) + (offset * 4U))
#define SET_SRAM_BB_VAL(addr, offset, key)                      (*(uint32_t*)(GET_SRAM_BB_ADDR(addr, offset)) = key)
#define GET_SRAM_BB_VAL(addr, offset)                           (*(uint32_t*)(GET_SRAM_BB_ADDR(addr, offset)))

/* Exported macro ------------------------------------------------------------*/
#define FLAG_SET(registry, flag)                                SET_SRAM_BB_VAL((uint32_t)&registry, flag, 1)
#define FLAG_CLR(registry, flag)                                SET_SRAM_BB_VAL((uint32_t)&registry, flag, 0)
#define FLAG_CHECK(registry, flag)                              (GET_SRAM_BB_VAL((uint32_t)&registry, flag))

#define PIN_H(port, pinSource)                                  SET_PERIPH_BB_VAL((uint32_t)port, GPIO_BSRR_Offset, pinSource, 1)
#define PIN_L(port, pinSource)                                  SET_PERIPH_BB_VAL((uint32_t)port, GPIO_BSRR_Offset, (pinSource + 16U), 1)
#define PIN_LEVEL(port, pinSource)                              (GET_PERIPH_BB_VAL((uint32_t)port, GPIO_IDR_Offset, pinSource))

#define PREG_SET(registry, key)                                 SET_PERIPH_BB_VAL((uint32_t)&registry, 0, key, 1)
#define PREG_CLR(registry, key)                                 SET_PERIPH_BB_VAL((uint32_t)&registry, 0, key, 0)
#define PREG_CHECK(registry, key)                               (GET_PERIPH_BB_VAL((uint32_t)&registry, 0, key))

#define BIT_2_0(per)        (per * 2U)
#define BIT_2_1(per)        (per * 2U + 1U)
#define BIT_4_0(per)        (per * 4U)
#define BIT_4_1(per)        (per * 4U + 1U)
#define BIT_4_2(per)        (per * 4U + 2U)
#define BIT_4_3(per)        (per * 4U + 3U)


/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void LED_Blink(GPIO_TypeDef* port, uint16_t pinSource);



#ifdef __cplusplus
}
#endif

#endif /* __COMMON_H */