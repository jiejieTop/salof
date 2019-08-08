#ifndef _SALOF_CONFIG_H_
#define _SALOF_CONFIG_H_
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define salof_mutex SemaphoreHandle_t
#define salof_tcb   TaskHandle_t


#define         DOS_ALIGN_SIZE                  (4U)

#define         DOS_MEM_HEAP_SIZE               (1024*30)
#define         DOS_HEAP_TO_MEMP                (1U)    /** memory heap to create memory pool */

#define         DOS_IPC_QUEUQ                   (1U)

#define         LOG_LEVEL                   DOS_DEBUG_LEVEL
#define         LOG_COLOR                   (1U)
#define         LOG_TS                      (1U)
#define         LOG_TAR                     (1U)

#define         USE_LOG                     (1U)
#define         USE_SALOF                   (1U)


#define         SALOF_BUFF_SIZE             (256U)
#define         SALOF_FIFO_SIZE             (1024*4U)


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

