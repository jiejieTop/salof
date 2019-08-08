#ifndef _SALOF_CONFIG_H_
#define _SALOF_CONFIG_H_

#define         USE_RTT             0
#define         USE_UCOSIII         1
#define         USE_FREERTOS        2
#define         USE_TENCENTOS       3


#define         LOG_LEVEL                   DEBUG_LEVEL
#define         LOG_COLOR                   (1U)
#define         LOG_TS                      (1U)
#define         LOG_TAR                     (1U)

#define         USE_LOG                     (1U)
#define         USE_SALOF                   (1U)
#define         USE_RTOS                    USE_FREERTOS
#define         USE_IDLE_HOOK               (1U)

#define         SALOF_BUFF_SIZE             (256U)
#define         SALOF_FIFO_SIZE             (1024*4U)


#if !defined(USE_RTOS)
    #error "USE_RTOS isn't defined in 'cmb_cfg.h'"
#endif

#if (USE_RTOS == USE_FREERTOS)
    #include "FreeRTOS.h"
    #include "task.h"
    #include "semphr.h"
    #define salof_mutex SemaphoreHandle_t
    #define salof_tcb   TaskHandle_t
#elif (USE_RTOS == USE_RTT)


#elif (USE_RTOS == USE_UCOSIII)


#elif (USE_RTOS == USE_TENCENTOS)


#else
    #error "not supported OS type"
#endif



void *salof_alloc(unsigned int size);
void salof_free(void *mem);
salof_tcb salof_task_create(const char *name,
                            void (*task_entry)(void *param),
                            void * const param,
                            unsigned int stack_size,
                            unsigned int priority,
                            unsigned int tick);
salof_mutex salof_mutex_create(void);
void salof_mutex_delete(salof_mutex mutex);
int salof_mutex_pend(salof_mutex mutex, unsigned int timeout);
int salof_mutex_post(salof_mutex mutex);
unsigned int salof_get_tick(void);
char *salof_get_task_name(void);

#endif // !_SALOF_CONFIG_H_

