/** synchronous asynchronous log output framework */

#include <salof.h>
#include <format.h>
#include <fifo.h>
#include <stdio.h>

#ifndef SALOF_BUFF_SIZE
    #define     DOS_SALOF_BUFF_SIZE     (256U)
#endif 
#ifndef SALOF_FIFO_SIZE
    #define     DOS_SALOF_FIFO_SIZE     (2048U)
#endif 

#if USE_SALOF
fifo_t salof_fifo = NULL;
#endif


char buff[SALOF_BUFF_SIZE];
 
void salof_task(void *parm);
 
 
void salof_init(void)
{
    salof_tcb task;
    
#if USE_SALOF
    salof_fifo = fifo_create(SALOF_FIFO_SIZE);
 #endif
    
    task = salof_task_create("salof_task", salof_task, NULL, 1024, 1, 20);
    if(task == NULL)
    {
        printf("salof task create fail\n");
    }
    
}


void salof(const char *fmt, ...)
{
    va_list args;
    int len;
    // char buff[DOS_SALOF_BUFF_SIZE];
    va_start(args, fmt);

    len = format_nstr(buff, SALOF_BUFF_SIZE - 1, fmt, args);

    if(len > SALOF_BUFF_SIZE)
        len = SALOF_BUFF_SIZE - 1;

#if USE_SALOF
    fifo_write(salof_fifo, buff, len, 100);
#else
    salof_out(buff, len);
#endif

  va_end(args);
}

int salof_out(char *buf, int len)
{
    return send_buff(buf, len);
}

void salof_task(void *parm)
{
#if USE_SALOF
    #include <string.h>
    int len;
    char buff[256];
#endif
    while(1)
    {
#if USE_SALOF
        len = fifo_read(salof_fifo, buff, sizeof(buff), 0);
        if(len > 0)
        {
            salof_out((char *)buff, len);
            memset(buff, 0, len);
        }
#endif
    } 
}




