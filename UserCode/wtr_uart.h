//
// Created by stdcat on 12/25/21.
//

#ifndef SERIAL2MOTOR_WTR_UART_H
#define SERIAL2MOTOR_WTR_UART_H

#include "wtr_definition.hpp"

typedef union {
    uint8_t raw[11];
    struct {
        uint8_t header[2];              // 0x55 0xaa
        uint8_t cmdID;                  // 0x5a init uart
        union {
            uint8_t data[8];
            struct {                    // cmdID 0x01
                uint8_t DJI_ENABLE[8];  // 2 off 1 on
            }__attribute__((packed)) Pack_Enable;
            struct {                    // cmdID 0x02
                uint8_t DJI_MODE[8];    // 2 speed 1 pos
            }__attribute__((packed)) Pack_Mode;
            struct {                    // cmdID 0x10+motorID(0~7)
                float servoValue;       // speed or pos servo value
                uint8_t zeros[4];       // unused data
            }__attribute__((packed)) Pack_Servo;
        };
    }__attribute__((packed));
}__attribute__((packed)) RecvBag_t;

typedef union {
    uint8_t raw[34];
    struct {
        uint8_t header[2];
        struct {
            int16_t motorSpeed[8];
            int16_t motorPos[8];
        }__attribute__((packed));
    }__attribute__((packed));
}__attribute__((packed)) SendBag_t;


#endif //SERIAL2MOTOR_WTR_UART_H
