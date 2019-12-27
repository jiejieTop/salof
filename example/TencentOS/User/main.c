#include "stm32f10x.h"
#include "bsp_usart.h"
#include "tos.h"
#include "salof.h"

k_task_t task1;
k_task_t task2;
k_stack_t task_stack1[1024];
k_stack_t task_stack2[1024];

void test_task1(void *Parameter)
{
  while (1)
  {
    LOG_INFO("Task1 Running\r\n");
    LOG_ERR("Task1 Running\r\n");  
    tos_task_delay(1000);   /* 延时1000个tick */
  }
}

void test_task2(void *Parameter)
{
  while (1)
  {
    LOG_WARN("Task2 Running\r\n");  
    LOG_DEBUG("Task2 Running\r\n");
    tos_task_delay(1000);   /* 延时1000个tick */
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
    
    /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
    USART_Config();

    printf("Welcome to TencentOS tiny\r\n");

    tos_knl_init(); // TOS Tiny kernel initialize
    
    tos_robin_config(TOS_ROBIN_STATE_ENABLED, (k_timeslice_t)500u);
    
    salof_init();
    
    printf("create task1\r\n");
    err = tos_task_create(&task1, 
                          "task1", 
                          test_task1,
                          NULL, 
                          3, 
                          task_stack1,
                          1024,
                          20);
    if(err != K_ERR_NONE)
        printf("TencentOS Create task1 fail! code : %d \r\n",err);
    
    printf("create task2\r\n");
    err = tos_task_create(&task2, 
                          "task2", 
                          test_task2,
                          NULL, 
                          4, 
                          task_stack2,
                          1024,
                          20);
    if(err != K_ERR_NONE)
        printf("TencentOS Create task2 fail! code : %d \r\n",err);
    
    tos_knl_start(); // Start TOS Tiny

}

