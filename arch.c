#include <salof_config.h>


void *salof_alloc(unsigned int size)
{
#if (SALOF_OS == USE_FREERTOS)
    return pvPortMalloc(size);
#elif (SALOF_OS == USE_RTT)

#elif (SALOF_OS == USE_UCOSIII)

#elif (SALOF_OS == USE_TENCENTOS)
    return tos_mmheap_alloc(size);
#else
    #error "not supported OS type"
#endif
}


void salof_free(void *mem)
{
#if (SALOF_OS == USE_FREERTOS)
    vPortFree(mem);
#elif (SALOF_OS == USE_RTT)

#elif (SALOF_OS == USE_UCOSIII)

#elif (SALOF_OS == USE_TENCENTOS)
    tos_mmheap_free(mem);
#else
    #error "not supported OS type"
#endif
}

salof_mutex salof_mutex_create(void)
{
#if (SALOF_OS == USE_FREERTOS)
    return xSemaphoreCreateMutex();
#elif (SALOF_OS == USE_RTT)

#elif (SALOF_OS == USE_UCOSIII)

#elif (SALOF_OS == USE_TENCENTOS)
    salof_mutex mutex;
    mutex = tos_mmheap_alloc(sizeof(k_mutex_t));
	tos_mutex_create((k_mutex_t*)mutex);	
    return mutex;
#else
    #error "not supported OS type"
#endif 
}


salof_tcb salof_task_create(const char *name,
                            void (*task_entry)(void *param),
                            void * const param,
                            unsigned int stack_size,
                            unsigned int priority,
                            unsigned int tick)
{
    salof_tcb task;
    
#if (SALOF_OS == USE_FREERTOS)
    (void)tick;
    xTaskCreate(task_entry, name, stack_size, param, priority, &task);
#elif (SALOF_OS == USE_RTT)

#elif (SALOF_OS == USE_UCOSIII)

#elif (SALOF_OS == USE_TENCENTOS)
    k_err_t err;
    k_stack_t *task_stack;
    task = tos_mmheap_alloc(sizeof(k_task_t));
    task_stack = tos_mmheap_alloc(stack_size);
    err = tos_task_create(task, 
                          (char*)name, 
                          task_entry,
                          param, 
                          priority, 
                          task_stack,
                          stack_size,
                          tick);
    if(err != K_ERR_NONE)
    {
        tos_mmheap_free(task);
        tos_mmheap_free(task_stack);
    }
#else
    #error "not supported OS type"
#endif
    return task;
}

void salof_mutex_delete(salof_mutex mutex)
{
#if (SALOF_OS == USE_FREERTOS)
    vSemaphoreDelete(mutex);
#elif (SALOF_OS == USE_RTT)

#elif (SALOF_OS == USE_UCOSIII)

#elif (SALOF_OS == USE_TENCENTOS)
	tos_mutex_destroy((k_mutex_t*)mutex);
    tos_mmheap_free(mutex);
#else
    #error "not supported OS type"
#endif 
}


int salof_mutex_pend(salof_mutex mutex, unsigned int timeout)
{
#if (SALOF_OS == USE_FREERTOS)
    if(xSemaphoreTake(mutex, timeout) != pdPASS)
        return -1;
#elif (SALOF_OS == USE_RTT)

#elif (SALOF_OS == USE_UCOSIII)

#elif (SALOF_OS == USE_TENCENTOS)
    if(tos_mutex_pend_timed((k_mutex_t*)mutex, timeout) != K_ERR_NONE)
        return -1;
#else
    #error "not supported OS type"
#endif 
    return 0;
}

int salof_mutex_post(salof_mutex mutex)
{
#if (SALOF_OS == USE_FREERTOS)
    if(xSemaphoreGive(mutex) != pdPASS)
        return -1;
#elif (SALOF_OS == USE_RTT)

#elif (SALOF_OS == USE_UCOSIII)

#elif (SALOF_OS == USE_TENCENTOS)
    if(tos_mutex_post((k_mutex_t*)mutex) != K_ERR_NONE)
        return -1;
#else
    #error "not supported OS type"
#endif 
    return 0;
}

unsigned int salof_get_tick(void)
{
#if (SALOF_OS == USE_FREERTOS)
    return xTaskGetTickCount();
#elif (SALOF_OS == USE_RTT)

#elif (SALOF_OS == USE_UCOSIII)

#elif (SALOF_OS == USE_TENCENTOS)
    return tos_systick_get();
#else
    #error "not supported OS type"
#endif 
    
}

char *salof_get_task_name(void)
{
#if (SALOF_OS == USE_FREERTOS)
    return pcTaskGetName(xTaskGetCurrentTaskHandle());
#elif (SALOF_OS == USE_RTT)

#elif (SALOF_OS == USE_UCOSIII)

#elif (SALOF_OS == USE_TENCENTOS)
    return k_curr_task->name;
#else
    #error "not supported OS type"
#endif 
}

