#include <salof_config.h>


void *salof_alloc(unsigned int size)
{
    return pvPortMalloc(size);
}


void salof_free(void *mem)
{
    vPortFree(mem);
}

salof_mutex salof_mutex_create(void)
{
    salof_mutex mutex;
    
    mutex = xSemaphoreCreateMutex();
    
    return mutex;
}


salof_tcb salof_task_create(const char *name,
                            void (*task_entry)(void *param),
                            void * const param,
                            unsigned int stack_size,
                            unsigned int priority,
                            unsigned int tick)
{
    salof_tcb task;
    
    xTaskCreate(task_entry, name, stack_size, param, priority, &task);
    
    return task;
}

void salof_mutex_delete(salof_mutex mutex)
{
    vSemaphoreDelete(mutex);
}


int salof_mutex_pend(salof_mutex mutex, unsigned int timeout)
{
    BaseType_t err = pdPASS;
    
    err = xSemaphoreTake(mutex, timeout);
    if(err != pdPASS)
        return -1;
    
    return 0;
}

int salof_mutex_post(salof_mutex mutex)
{
    BaseType_t err = pdPASS;
    
    err = xSemaphoreGive(mutex);
    if(err != pdPASS)
        return -1;
    
    return 0;
}

unsigned int salof_get_tick(void)
{
    return xTaskGetTickCount();
}

char *salof_get_task_name(void)
{
    return pcTaskGetName(xTaskGetCurrentTaskHandle());
}

