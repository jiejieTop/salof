/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
/* 开发板硬件bsp头文件 */
#include "bsp_usart.h"

#include "salof.h"

/**************************** 任务句柄 ********************************/
/* 
 * 任务句柄是一个指针，用于指向一个任务，当任务创建好之后，它就具有了一个任务句柄
 * 以后我们要想操作这个任务都需要通过这个任务句柄，如果是自身的任务操作自己，那么
 * 这个句柄可以为NULL。
 */
static TaskHandle_t AppTaskCreate_Handle = NULL;/* 创建任务句柄 */
static TaskHandle_t Task1_Handle = NULL;/* Task1任务句柄 */
static TaskHandle_t Task2_Handle = NULL;/* Task2任务句柄 */


/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
static void AppTaskCreate(void);/* 用于创建任务 */

static void Task1(void* pvParameters);/* Task1任务实现 */
static void Task2(void* pvParameters);/* Task2任务实现 */

static void BSP_Init(void);/* 用于初始化板载相关资源 */

/*****************************************************************
  * @brief  主函数
  * @param  无
  * @retval 无
  * @note   第一步：开发板硬件初始化 
            第二步：创建APP应用任务
            第三步：启动FreeRTOS，开始多任务调度
  ****************************************************************/
int main(void)
{	
    BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */

    /* 开发板硬件初始化 */
    BSP_Init();
    
    /* salof框架初始化 */
    salof_init();

    /* 创建AppTaskCreate任务 */
    xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* 任务入口函数 */
                        (const char*    )"AppTaskCreate",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )1, /* 任务的优先级 */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);/* 任务控制块指针 */ 
    /* 启动任务调度 */           
    if(pdPASS == xReturn)
    vTaskStartScheduler();   /* 启动任务，开启调度 */
    else
    return -1;  

    while(1);   /* 正常不会执行到这里 */    
}


/***********************************************************************
  * @ 函数名  ： AppTaskCreate
  * @ 功能说明： 为了方便管理，所有的任务创建函数都放在这个函数里面
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  **********************************************************************/
static void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
  
  taskENTER_CRITICAL();           //进入临界区
  
  /* 创建Task1任务 */
  xReturn = xTaskCreate((TaskFunction_t )Task1, /* 任务入口函数 */
                        (const char*    )"Task1",/* 任务名字 */
                        (uint16_t       )512,   /* 任务栈大小 */
                        (void*          )NULL,	/* 任务入口函数参数 */
                        (UBaseType_t    )3,	    /* 任务的优先级 */
                        (TaskHandle_t*  )&Task1_Handle);/* 任务控制块指针 */
  if(pdPASS == xReturn)
    LOG_INFO("Create Task1 successfully!\r\n");
  /* 创建Task2任务 */
  xReturn = xTaskCreate((TaskFunction_t )Task2,  /* 任务入口函数 */
                        (const char*    )"Task2",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )4, /* 任务的优先级 */
                        (TaskHandle_t*  )&Task2_Handle);/* 任务控制块指针 */ 
  if(pdPASS == xReturn)
    printf("Create Task2 successfully!!\r\n");
  
  vTaskDelete(AppTaskCreate_Handle); //删除AppTaskCreate任务
  
  taskEXIT_CRITICAL();            //退出临界区
}



/**********************************************************************
  * @ 函数名  ： Task1
  * @ 功能说明： Task1任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void Task1(void* parameter)
{	
  while (1)
  {
    LOG_INFO("Task1 Running\r\n");
    LOG_ERR("Task1 Running\r\n");  
    vTaskDelay(1000);   /* 延时1000个tick */
  }
}

/**********************************************************************
  * @ 函数名  ： Task1
  * @ 功能说明： Task1任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void Task2(void* parameter)
{	
  while (1)
  {
    LOG_WARN("Task2 Running\r\n");  
    LOG_DEBUG("Task2 Running\r\n");
    vTaskDelay(1000);   /* 延时1000个tick */
  }
}

/***********************************************************************
  * @ 函数名  ： BSP_Init
  * @ 功能说明： 板级外设初始化，所有板子上的初始化均可放在这个函数里面
  * @ 参数    ：   
  * @ 返回值  ： 无
  *********************************************************************/
static void BSP_Init(void)
{
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	
	/* 串口初始化	*/
	USART_Config();
  
}

/********************************END OF FILE****************************/
