/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @Date: 2020-02-25 06:01:24
 * @LastEditTime: 2020-02-25 09:28:09
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */

#ifndef _SALOF_CONFIG_H_
#define _SALOF_CONFIG_H_

#define         LOG_LEVEL                   DEBUG_LEVEL   //WARN_LEVEL DEBUG_LEVEL

#define         USE_LOG                     (1U)
#define         USE_SALOF                   (1U)
#define         SALOF_OS                    USE_TENCENTOS
#define         USE_IDLE_HOOK               (0U)
#define         LOG_COLOR                   (1U)
#define         LOG_TS                      (1U)
#define         LOG_TAR                     (0U)
#define         SALOF_BUFF_SIZE             (512U)
#define         SALOF_FIFO_SIZE             (1024*4U)
#define         SALOF_TASK_STACK_SIZE       (2048U)
#define         SALOF_TASK_TICK             (50U)

#endif /* _SALOF_CONFIG_H_ */
