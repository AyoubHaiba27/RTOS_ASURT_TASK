/* FreeRTOSConfig.h - STM32F103 (Cortex-M3), FSUK27 RTOS task
 * Place in Core/Inc and add Core/Inc to the include paths.
 * Reference for every option: freertos.org -> Documentation -> Kernel -> Configuration (FreeRTOS-Kernel config options) */
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>
extern uint32_t SystemCoreClock;                 /* defined by CMSIS system_stm32f1xx.c */

/* ---- Scheduler ---- */
#define configUSE_PREEMPTION                     1
#define configUSE_TIME_SLICING                   1
#define configCPU_CLOCK_HZ                       ( SystemCoreClock )
#define configTICK_RATE_HZ                       ( ( TickType_t ) 1000 )   /* tick = 1 ms (requirement) */
#define configMAX_PRIORITIES                     ( 5 )
#define configMINIMAL_STACK_SIZE                 ( ( uint16_t ) 128 )      /* in words */
#define configMAX_TASK_NAME_LEN                  ( 16 )
#define configUSE_16_BIT_TICKS                   0
#define configIDLE_SHOULD_YIELD                  1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION  1

/* ---- Memory ---- */
#define configSUPPORT_DYNAMIC_ALLOCATION         1
#define configSUPPORT_STATIC_ALLOCATION          0
#define configTOTAL_HEAP_SIZE                    ( ( size_t ) ( 10 * 1024 ) )   /* heap_4.c, STM32F103C8 has 20 KB RAM */

/* ---- Features used by the task ---- */
#define configUSE_MUTEXES                        1     /* mutex on "shared" */
#define configUSE_COUNTING_SEMAPHORES            0
#define configUSE_RECURSIVE_MUTEXES              0
#define configQUEUE_REGISTRY_SIZE                0
#define configUSE_TIMERS                         1     /* REQUIRED by xEventGroupSetBitsFromISR (daemon task) */
#define configTIMER_TASK_PRIORITY                ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH                 10
#define configTIMER_TASK_STACK_DEPTH             ( configMINIMAL_STACK_SIZE * 2 )

/* ---- Hooks / debug (kept off for simplicity) ---- */
#define configUSE_IDLE_HOOK                      0
#define configUSE_TICK_HOOK                      0
#define configUSE_MALLOC_FAILED_HOOK             0
#define configCHECK_FOR_STACK_OVERFLOW           0
#define configUSE_TRACE_FACILITY                 0
#define configGENERATE_RUN_TIME_STATS            0
#define configUSE_APPLICATION_TASK_TAG           0
#define configUSE_CO_ROUTINES                    0

/* ---- API functions to include ---- */
#define INCLUDE_vTaskDelay                       1
#define INCLUDE_vTaskDelayUntil                  1
#define INCLUDE_xTaskGetSchedulerState           1
#define INCLUDE_xEventGroupSetBitFromISR         1     /* REQUIRED by xEventGroupSetBitsFromISR */
#define INCLUDE_xTimerPendFunctionCall           1     /* REQUIRED by xEventGroupSetBitsFromISR */
#define INCLUDE_vTaskPrioritySet                 0
#define INCLUDE_uxTaskPriorityGet                0
#define INCLUDE_vTaskDelete                      0
#define INCLUDE_vTaskSuspend                     1     /* needed for portMAX_DELAY blocking (mutex) */

/* ---- Interrupt priorities (Cortex-M3 has 4 priority bits -> shifted by 4) ---- */
#define configPRIO_BITS                          4
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY          15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY     5
#define configKERNEL_INTERRUPT_PRIORITY          ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY     ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )

/* ---- Assert ---- */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* ---- Map the FreeRTOS port handlers onto the Cortex-M vector table names ---- */
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
