//
// Created by stdcat on 12/25/21.
//

#ifndef SERIAL2MOTOR_DJIFSM_H
#define SERIAL2MOTOR_DJIFSM_H
#include "fsm.hpp"
#include "DJI.h"
#include "wtr_calculate.h"

typedef enum{
    state_speedServo,
    state_posServo,
    state_disable,

    cmd_enable,
    cmd_disable,
    cmd_toSpeed,
    cmd_toPos,
    cmd_tick

}DJI_FSM_e;

class DJIFSM{
private:
    int id;
    bool running;//似乎没有用上
    DJI_t *djiHandle;
    int16_t servoValue;

    void fsmInit();
    void ledOn();
    void ledOff();

public:

    fsm::stack fsm;

    // dji_id: 0~7
    DJIFSM(int dji_id){
        if(dji_id > 7) dji_id = 7;
        if(dji_id < 0) dji_id = 0;

        id = dji_id;
        djiHandle = &hDJI[dji_id];
        running = false;
        servoValue = 0;

        fsmInit();

        fsm.set(state_disable);
    }

    void setValue( float _v ){
        servoValue = (int16_t)( int(_v) );
    }
};

#endif //SERIAL2MOTOR_DJIFSM_H
