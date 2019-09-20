#include "tos.h"

#if TOS_CFG_PWR_MGR_EN > 0u

static int pm_device_uart_init(void)
{
    return 0;
}

static int pm_device_uart_suspend(void)
{
    return 0;
}

static int pm_device_uart_resume(void)
{
    HAL_Init();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    __HAL_RCC_USART1_CLK_ENABLE(); //使能 USART1 时钟
    __HAL_RCC_GPIOA_CLK_ENABLE(); //使能 GPIOA 时钟

    return 0;
}

k_pm_device_t pm_device_uart = {
    .name       = "uart",
    .init       = pm_device_uart_init,
    .suspend    = pm_device_uart_suspend,
    .resume     = pm_device_uart_resume,
};

#endif

