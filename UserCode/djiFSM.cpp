//
// Created by stdcat on 12/25/21.
//

#include "djiFSM.h"

void DJIFSM::ledOff() {

    switch (id) {
        case 0:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_SET);
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET);
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_SET);
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_SET);
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
            break;
        case 6:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
            break;
        case 7:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_SET);
            break;
    }
}

void DJIFSM::ledOn() {
    switch (id) {
        case 0:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_RESET);
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET);
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_RESET);
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_RESET);
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);
            break;
        case 6:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET);
            break;
        case 7:
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_RESET);
            break;
    }
}

void DJIFSM::fsmInit() {
    fsm.on( state_disable, cmd_enable ) = [&]( const fsm::args &args ){
        running = true;
        ledOn();
        fsm.set(state_speedServo);
    };

    fsm.on( state_disable, cmd_tick ) = [&]( const fsm::args &args ){
        djiHandle->speedPID.output = 0;
    };

    fsm.on( state_speedServo, cmd_disable ) = [&]( const fsm::args &args ){
        running = false;
        ledOff();
        fsm.set(state_disable);
    };

    fsm.on( state_speedServo, cmd_toPos ) = [&]( const fsm::args &args ){
        fsm.set(state_posServo);
    };

    fsm.on( state_speedServo, cmd_tick ) = [&]( const fsm::args &args ){
        djiHandle->speedPID.fdb = djiHandle->FdbData.rpm;
        djiHandle->speedPID.ref = servoValue;
        PID_Calc(&djiHandle->speedPID);
    };

    fsm.on( state_posServo, cmd_disable ) = [&]( const fsm::args &args ){
        running = false;
        ledOff();
        fsm.set(state_disable);
    };

    fsm.on( state_posServo, cmd_toSpeed ) = [&]( const fsm::args &args ){
        fsm.set(state_speedServo);
    };

    fsm.on( state_posServo, cmd_tick ) = [&]( const fsm::args &args ){
        djiHandle->posPID.fdb = djiHandle->AxisData.AxisAngle_inDegree;
        djiHandle->posPID.ref = servoValue;
        P_Calc(&djiHandle->posPID);
        djiHandle->speedPID.fdb = djiHandle->FdbData.rpm;
        djiHandle->speedPID.ref = djiHandle->posPID.output;
        PID_Calc(&djiHandle->speedPID);
    };
}