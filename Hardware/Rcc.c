#include "Rcc.h"
void rcc_init(void)
{
    ErrorStatus status;

    RCC_ClockSecuritySystemCmd(ENABLE);

    RCC_HSEConfig(RCC_HSE_ON);
    status = RCC_WaitForHSEStartUp();

    if (status == SUCCESS)
    {
        FLASH_PrefetchBufferCmd(ENABLE);

        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLKConfig(RCC_HCLK_Div1);

        RCC_PLLConfig(RCC_PLLSource_HSE, RCC_PLLMul_6);
        RCC_PLLCmd(ENABLE);

        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }

        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        while (RCC_GetSYSCLKSource() != 0x08)
        {
        }
    }
}