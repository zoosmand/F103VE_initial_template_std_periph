/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Global variables ---------------------------------------------------------*/
uint32_t sysQuantum       = 0;
uint32_t millis           = 0;
uint32_t seconds          = 0;
uint32_t minutes          = 0;
uint32_t _EREG_           = 0;
uint32_t delay_tmp        = 0;
uint32_t check            = 0;
uint32_t SystemCoreClock  = 16000000;

/* Private variables ---------------------------------------------------------*/
static uint32_t millis_tmp    = 100;
static uint32_t seconds_tmp   = 1000;
static uint32_t minutes_tmp   = 60;

/* Private function prototypes -----------------------------------------------*/
static void CronSysQuantum_Handler(void);
static void CronMillis_Handler(void);
static void CronSeconds_Handler(void);
static void CronMinutes_Handler(void);
static void Flags_Handler(void);









////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void) { 

  Delay(500);

  while (1) {
    Delay_Handler(0);
    Cron_Handler();
    Flags_Handler();
  }
}







/********************************************************************************/
/*                                     CRON                                     */
/********************************************************************************/
void Cron_Handler() {
  $CronStart:
  if (SysTick->CTRL & (1 << SysTick_CTRL_COUNTFLAG_Pos)) { 
    sysQuantum++;
    CronSysQuantum_Handler();
  }

  if (sysQuantum >= millis_tmp) {
    millis++;
    millis_tmp = sysQuantum + 100;
    CronMillis_Handler();
  }
  
  if (millis >= seconds_tmp) {
    seconds++;
    seconds_tmp += 1000;
    CronSeconds_Handler();
  }
  
  if (seconds >= minutes_tmp) {
    minutes++;
    minutes_tmp += 60;
    CronMinutes_Handler();
  }

  while (sysQuantum < delay_tmp) {
    goto $CronStart;
  }
  // !!!!!!!!! The bug!!!!!!!!
  delay_tmp = 0;
  FLAG_CLR(_EREG_, _DELAYF_);
}






/********************************************************************************/
/*                             CRON EVENTS HANDLERS                             */
/********************************************************************************/
// ---- System Quantum ---- //
static void CronSysQuantum_Handler(void) {
  //
}

// ---- Milliseconds ---- //
static void CronMillis_Handler(void) {
  //
}

// ---- Seconds ---- //
static void CronSeconds_Handler(void) {
  //
  // LL_IWDG_ReloadCounter(IWDG);
  printf("test\n");
}

// ---- Minutes ---- //
static void CronMinutes_Handler(void) {
  //
}







/********************************************************************************/
/*                                     FLAGS                                    */
/********************************************************************************/
void Flags_Handler(void){
  if (FLAG_CHECK(_EREG_, _BT7F_)) {
    // BasicTimer_FromIT_Handler(TIM7);
    FLAG_CLR(_EREG_, _BT7F_);
  }
}









/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void) {

  #if (PREFETCH_ENABLE != 0)
    // FLASH->ACR |= FLASH_ACR_PRFTBE;
    PREG_SET(FLASH->ACR, FLASH_ACR_PRFTBE_Pos);
  #else
    PREG_CLR(FLASH->ACR, FLASH_ACR_PRFTBE_Pos);
  #endif /* PREFETCH_ENABLE */

  __NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    /* SysTick */
  SysTick->CTRL     = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;
  SysTick->LOAD     = 720U - 1U;
  SysTick->VAL      = 0;
  SysTick->CTRL     |= SysTick_CTRL_ENABLE_Msk;

  /* SysTick interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(SysTick_IRQn);

  /* SysCfg */
  PREG_SET(RCC->APB2ENR, RCC_APB2ENR_AFIOEN_Pos);
  check = 0;
  while (!check) {
    check = PREG_CHECK(RCC->APB2ENR, RCC_APB2ENR_AFIOEN_Pos);
  }

  /* PWR */
  PREG_SET(RCC->APB1ENR, RCC_APB1ENR_PWREN_Pos);
  check = 0;
  while (!check) {
    check = PREG_CHECK(RCC->APB1ENR, RCC_APB1ENR_PWREN_Pos);
  }

  /* FLASH_IRQn interrupt configuration */
  NVIC_SetPriority(FLASH_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(FLASH_IRQn);

  /* RCC_IRQn interrupt configuration */
  NVIC_SetPriority(RCC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(RCC_IRQn);

  /* Flash */
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_1);
  if (READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_1) {
    Error_Handler();
  }

  /* JTAG-DP disabled and SW-DP enabled */
  CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_SWJ_CFG);
  SET_BIT(AFIO->MAPR, AFIO_MAPR_SWJ_CFG_JTAGDISABLE);

  /* HSE enable and wait until it runs */
  PREG_SET(RCC->CR, RCC_CR_HSEON_Pos);
  check = 0;
  while (!check) {
    check = PREG_CHECK(RCC->CR, RCC_CR_HSERDY_Pos);
  }

  /* LSI enable and wait until it runs */
  PREG_SET(RCC->CSR, RCC_CSR_LSION_Pos);
  check = 0;
  while (!check) {
    check = PREG_CHECK(RCC->CR, RCC_CSR_LSIRDY_Pos);
  }

  /* Enable backup registers access */
  PREG_SET(PWR->CR, PWR_CR_DBP_Pos);

  /* Force backup domain reset */
  PREG_SET(RCC->BDCR, RCC_BDCR_BDRST_Pos);
  PREG_CLR(RCC->BDCR, RCC_BDCR_BDRST_Pos);

  /* LSE enable and wait until it runs */
  PREG_SET(RCC->BDCR, RCC_BDCR_LSEON_Pos);
  check = 0;
  while (!check) {
    check = PREG_CHECK(RCC->CR, RCC_BDCR_LSERDY_Pos);
  }

  /* RTC Source is LSE */
  MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSEL, RCC_BDCR_RTCSEL_0);

  /* Enable RTC */
  PREG_SET(RCC->BDCR, RCC_BDCR_RTCEN_Pos);

  /* PLL confugure domain clock */
  RCC->CFGR |= RCC_CFGR_PLLMULL9; // mutiprexing pll on 9
  PREG_SET(RCC->CFGR, RCC_CFGR_PLLSRC_Pos); // PLL is the clock source

  /* PLL enable and wait until it runs*/
  PREG_SET(RCC->CR, RCC_CR_PLLON_Pos);
  check = 0;
  while (!check) {
    check = PREG_CHECK(RCC->CR, RCC_CR_PLLRDY_Pos);
  }

  /* AHB clock isn't divided */
  /* APB1 clock divided by 2 */
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV2);
  /* APB2 clock isn't divided */

  /* set PLL as sysclock source and wait until it runs */
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
  while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);


  SystemCoreClock = 72000000;
}

