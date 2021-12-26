//
// Created by stdcat on 12/25/21.
//

#ifndef SERIAL2MOTOR_WTR_DEFINITION_H
#define SERIAL2MOTOR_WTR_DEFINITION_H

#include "DJI.h"

#include "usart.h"
#include "gpio.h"
#include "can.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* C CODE BEGIN */


extern uint8_t CanReceiveData[8];
extern uint8_t uart6ReceiveData[30];
/* C CODE END */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //SERIAL2MOTOR_WTR_DEFINITION_H


//#ifdef __cplusplus
//extern "C" {
//#endif /* __cplusplus */
//
///* C CODE BEGIN */
//
///* C CODE END */
//
//#ifdef __cplusplus
//}
//#endif /* __cplusplus */
