//
// Created by stdcat on 12/25/21.
//
#include "wtr_thread.h"
#include "cmsis_os.h"
#include "wtr_definition.hpp"
#include "wtr_uart.h"

static void DJITask(void* argument);
static TaskHandle_t DJITaskHandle;

static void SerialTask(void* argument);
static TaskHandle_t SerialTaskHandle;


void wtr_AddThreads(void)
{
	BaseType_t xReturn = pdPASS;
	/* 创建线程1----------------------------------------------*/
	xReturn = xTaskCreate((TaskFunction_t )DJITask,
												(const char*    )"DJI",
												(uint16_t			  )1024,
												(void*          )NULL,
												(UBaseType_t    )5,
												(TaskHandle_t*  )&DJITaskHandle);
	if(xReturn==pdPASS){
    ;
	}/* 任务创建成功	*/
	else
		while(1);
		/*-------------------------------------------------------*/
    xReturn = pdFAIL;
//	/* 创建线程2----------------------------------------------*/
	xReturn = xTaskCreate((TaskFunction_t )SerialTask,
												(const char*    )"Serial",
												(uint16_t			  )1024,
												(void*          )NULL,
												(UBaseType_t    )5,
												(TaskHandle_t*  )&SerialTaskHandle);
	if(xReturn==pdPASS){
    ;
	}/* 任务创建成功	*/
	else
		while(1);
	/*-------------------------------------------------------*/
}

void DJITask(void* argument)
{
    vTaskDelay(100);
    while (1){
        for (int i = 0; i < 8; ++i) {
            djiFsm[i]->fsm.command(cmd_tick);
        }
        CanTransmit_DJI_1234(&hcan1,
                             hDJI[0].speedPID.output,
                             hDJI[1].speedPID.output,
                             hDJI[2].speedPID.output,
                             hDJI[3].speedPID.output);
        CanTransmit_DJI_5678(&hcan1,
                             hDJI[4].speedPID.output,
                             hDJI[5].speedPID.output,
                             hDJI[6].speedPID.output,
                             hDJI[7].speedPID.output);
        vTaskDelay(1);
    }
}

static void SerialTask(void* argument){
    vTaskDelay(500);
    while (1){
        SendBag_t sendBag;
        sendBag.header[0] = 0xff;
        sendBag.header[1] = 0x6a;

        for (int i = 0; i < 8; ++i) {
            sendBag.motorSpeed[i] = (int16_t) hDJI[i].FdbData.rpm;
            sendBag.motorPos[i] = (int16_t) hDJI[i].AxisData.AxisAngle_inDegree;
        }
        HAL_UART_Transmit_IT(&huart6,(uint8_t*) sendBag.raw,34);

        vTaskDelay(50);
    }
}
