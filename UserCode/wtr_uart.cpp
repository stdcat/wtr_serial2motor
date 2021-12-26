//
// Created by stdcat on 12/25/21.
//

#include "wtr_uart.h"
uint8_t uart6ReceiveData[30];

uint8_t uartOK = 0;
uint8_t uartGoNext = 0;

void UART6Decode(){

    if(!uartOK){
        if(uartGoNext){
            uartGoNext = 0;
            uartOK = 1;
            HAL_UART_Receive_DMA(&huart6, uart6ReceiveData, 11);
            return;
        }
        for (int i = 0; i < 11; ++i) {
            RecvBag_t tempBag = *(RecvBag_t*) (void *) (&(uart6ReceiveData[i]));
            if( tempBag.header[0] == 0x55 && tempBag.header[1] == 0xaa && tempBag.cmdID == 0x5a ){
                if(i == 0){
                    uartOK = 1;
                    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);

                    HAL_UART_Receive_DMA(&huart6, uart6ReceiveData, 11);
                    return;
                }
                else{
                    uartGoNext = 1;
                    HAL_UART_Receive_DMA(&huart6, uart6ReceiveData, i);
                }
            }
        }
    }

    RecvBag_t tempBag = *(RecvBag_t*) (void *) (&(uart6ReceiveData[0]));
    if( tempBag.header[0] == 0x55 && tempBag.header[1] == 0xaa ){
        uartOK = 1;
        //led uartOK gree on red off
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);


        if( tempBag.cmdID == 0x01 ){//enable motor
            for (int j = 0; j < 8; ++j) {
                if(tempBag.Pack_Enable.DJI_ENABLE[j] == 0x01){
                    djiFsm[j]->fsm.command(cmd_enable);
                }
                if(tempBag.Pack_Enable.DJI_ENABLE[j] == 0x02){
                    djiFsm[j]->fsm.command(cmd_disable);
                }
            }
        }
        if( tempBag.cmdID == 0x02 ){//change mode
            for (int j = 0; j < 8; ++j) {
                if(tempBag.Pack_Enable.DJI_ENABLE[j] == 0x01){
                    djiFsm[j]->fsm.command(cmd_toPos);
                }
                if(tempBag.Pack_Enable.DJI_ENABLE[j] == 0x02){
                    djiFsm[j]->fsm.command(cmd_toSpeed);
                }
            }
        }
        if( tempBag.cmdID >= 0x10 && tempBag.cmdID < 0x18 ){//set value
            int id = tempBag.cmdID - 0x10;
            djiFsm[id]->setValue(tempBag.Pack_Servo.servoValue);
        }
        HAL_UART_Receive_DMA(&huart6, uart6ReceiveData, 11);
    }
    else{
        uartOK = 0;
        //led uartError gree off red on
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
        HAL_UART_Receive_DMA(&huart6, uart6ReceiveData, 22);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

    if(huart->Instance == huart6.Instance){
        UART6Decode();
        ;
    }
}
