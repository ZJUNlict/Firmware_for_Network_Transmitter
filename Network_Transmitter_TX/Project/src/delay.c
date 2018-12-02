#include "main.H"

extern __IO uint32_t SysTickTimer;

/*******************************************************************************
* Function Name  : SysTick_Configuration
* Description    : Configure a SysTick Base time to 10 ms.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Configuration(void)
{
  /* Setup SysTick Timer for 10 msec interrupts  */
  if (SysTick_Config(SystemCoreClock / 1200))
  { 
    /* Capture error */ 
    while (1);
  }
  
 /* Configure the SysTick handler priority */
  NVIC_SetPriority(SysTick_IRQn, 0x0);
}

void delay_ms(u16 nms)
{
    u32 LocalTimer;
    LocalTimer = SysTickTimer + nms;
    while(LocalTimer != SysTickTimer);
}  

#if 0
void Delay_ARMJISHU(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--);
}
#endif

