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
#define GPIO_IDR_Offset             (uint16_t)0x0008
#define GPIO_ODR_Offset             (uint16_t)0x000c
#define GPIO_BSRR_Offset            (uint16_t)0x0010
#define GPIO_BRR_Offset             (uint16_t)0x0014

#define NVIC_PRIORITYGROUP_0        ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority, 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1        ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority, 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2        ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority, 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3        ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority, 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4        ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority, 0 bit  for subpriority */

#define GPIO_PIN_0                  GPIO_BSRR_BS_0 /*!< Select pin 0 */
#define GPIO_PIN_0_Pos              0
#define GPIO_PIN_0_Mask             0x0000000f
#define GPIO_PIN_1                  GPIO_BSRR_BS_1 /*!< Select pin 1 */
#define GPIO_PIN_1_Pos              1
#define GPIO_PIN_1_Mask             0x000000f0
#define GPIO_PIN_2                  GPIO_BSRR_BS_2 /*!< Select pin 2 */
#define GPIO_PIN_2_Pos              2
#define GPIO_PIN_2_Mask             0x00000f00
#define GPIO_PIN_3                  GPIO_BSRR_BS_3 /*!< Select pin 3 */
#define GPIO_PIN_3_Pos              3
#define GPIO_PIN_3_Mask             0x0000f000
#define GPIO_PIN_4                  GPIO_BSRR_BS_4 /*!< Select pin 4 */
#define GPIO_PIN_4_Pos              4
#define GPIO_PIN_4_Mask             0x000f0000
#define GPIO_PIN_5                  GPIO_BSRR_BS_5 /*!< Select pin 5 */
#define GPIO_PIN_5_Pos              5
#define GPIO_PIN_5_Mask             0x00f00000
#define GPIO_PIN_6                  GPIO_BSRR_BS_6 /*!< Select pin 6 */
#define GPIO_PIN_6_Pos              6
#define GPIO_PIN_6_Mask             0x0f000000
#define GPIO_PIN_7                  GPIO_BSRR_BS_7 /*!< Select pin 7 */
#define GPIO_PIN_7_Pos              7
#define GPIO_PIN_7_Mask             0xf0000000
#define GPIO_PIN_8                  GPIO_BSRR_BS_8 /*!< Select pin 8 */
#define GPIO_PIN_8_Pos              8
#define GPIO_PIN_8_Mask             0x0000000f
#define GPIO_PIN_9                  GPIO_BSRR_BS_9 /*!< Select pin 9 */
#define GPIO_PIN_9_Pos              9
#define GPIO_PIN_9_Mask             0x000000f0
#define GPIO_PIN_10                 GPIO_BSRR_BS_10 /*!< Select pin 10 */
#define GPIO_PIN_10_Pos             10
#define GPIO_PIN_10_Mask            0x00000f00
#define GPIO_PIN_11                 GPIO_BSRR_BS_11 /*!< Select pin 11 */
#define GPIO_PIN_11_Pos             11
#define GPIO_PIN_11_Mask            0x0000f000
#define GPIO_PIN_12                 GPIO_BSRR_BS_12 /*!< Select pin 12 */
#define GPIO_PIN_12_Pos             12
#define GPIO_PIN_12_Mask            0x000f0000
#define GPIO_PIN_13                 GPIO_BSRR_BS_13 /*!< Select pin 13 */
#define GPIO_PIN_13_Pos             13
#define GPIO_PIN_13_Mask            0x00f00000
#define GPIO_PIN_14                 GPIO_BSRR_BS_14 /*!< Select pin 14 */
#define GPIO_PIN_14_Pos             14
#define GPIO_PIN_14_Mask            0x0f000000
#define GPIO_PIN_15                 GPIO_BSRR_BS_15 /*!< Select pin 15 */
#define GPIO_PIN_15_Pos             15
#define GPIO_PIN_15_Mask            0xf0000000
#define GPIO_PIN_ALL                (uint16_t)0xffff /*!< Select all pins */

#define _GPO_PP                     0b0000 // General purpose output push-pull
#define _GPO_OD                     0b0100 // General purpose output open drain
#define _IOS_2                      0b0010 // I/O speed is 2 MHz
#define _IOS_10                     0b0001 // I/O speed is 10 MHz
#define _IOS_50                     0b0011 // I/O speed is 50 MHz
#define _AF_PP                      0b1000 // Alterhative function push-pull
#define _AF_OD                      0b1100 // Alterhative function open drain
#define _IN_AN                      0b0000 // Input analog
#define _IN_FL                      0b0100 // Input floating point
#define _IN_PD                      0b1000 // correspondent ODR register pin has to be 0
#define _IN_PU                      0b1000 // correspondent ODR register pin has to be 1

#define IWDG_KEY_RELOAD             0x0000aaaa               /*!< IWDG Reload Counter Enable   */
#define IWDG_KEY_ENABLE             0x0000cccc               /*!< IWDG Peripheral Enable       */
#define IWDG_KEY_WR_ACCESS_ENABLE   0x00005555               /*!< IWDG KR Write Access Enable  */



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
// #define PIN_LEVEL(port, pinSource)                              (GET_PERIPH_BB_VAL((uint32_t)port, GPIO_IDR_Offset, pinSource))
#define PIN_LEVEL(port, pinSource)                               (Get_BitBandVal(GET_PERIPH_BB_ADDR((uint32_t)port, GPIO_IDR_Offset, pinSource)))

#define PREG_SET(registry, key)                                 SET_PERIPH_BB_VAL((uint32_t)&registry, 0, key, 1)
#define PREG_CLR(registry, key)                                 SET_PERIPH_BB_VAL((uint32_t)&registry, 0, key, 0)
// #define PREG_CHECK(registry, key)                               (GET_PERIPH_BB_VAL((uint32_t)&registry, 0, key))
#define PREG_CHECK(registry, key)                               (Get_BitBandVal(GET_PERIPH_BB_ADDR((uint32_t)&registry, 0, key)))

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