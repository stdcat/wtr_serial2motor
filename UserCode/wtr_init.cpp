//
// Created by stdcat on 12/25/21.
//
#include "wtr_init.h"

#include "wtr_can.h"
#include "wtr_definition.hpp"

void wtr_init(){
    CANFilterInit(&hcan1);
    HAL_UART_Receive_DMA(&huart6, uart6ReceiveData, 22);

    // all led turn off
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_SET);
    //uart led: green ok red error
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);


    // own driver init
    for (int i = 0; i < 4; ++i) {
        hDJI[i].motorType = M3508;
    }
    for (int i = 4; i < 8; ++i) {
        hDJI[i].motorType = M2006;
    }
    DJI_Init();
    for (int i = 0; i < 8; ++i) {
        djiFsm[i] = new DJIFSM(i);
    }

    // variables init
}