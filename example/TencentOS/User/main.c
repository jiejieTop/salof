/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   GPIO输出--使用固件库点亮LED灯
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 STM32 F429 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "stm32l4xx.h"
#include "tos.h"
#include "salof.h"

k_task_t task1;
k_task_t task2;
k_stack_t task_stack1[1024];
k_stack_t task_stack2[1024];

void test_task1(void *Parameter)
{
    while(1)
    {
        LOG_INFO("task1 running\r\n");
        LOG_ERR("task1 running\r\n");  
        tos_task_delay(1000);
    }
}

void test_task2(void *Parameter)
{
    while(1)
    {
        LOG_WARN("task2 running\r\n");  
        LOG_DEBUG("task2 running\r\n");
        tos_task_delay(1000);
    }
}
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    k_err_t err;
    
    BSP_Init();
    
    tos_knl_init(); // TOS Tiny kernel initialize
    
    salof_init();
    
    LOG_INFO("Welcome to TencentOS tiny\r\n");
    tos_robin_config(TOS_ROBIN_STATE_ENABLED, (k_timeslice_t)500u);
    err = tos_task_create(&task1, 
                          "task1", 
                          test_task1,
                          NULL, 
                          3, 
                          task_stack1,
                          1024,
                          20);
    
    err = tos_task_create(&task2, 
                          "task2", 
                          test_task2,
                          NULL, 
                          4, 
                          task_stack2,
                          1024,
                          20);
    if(err != K_ERR_NONE)
        printf("TencentOS Create task fail! code : %d \r\n",err);
    
    tos_knl_start(); // Start TOS Tiny



}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
