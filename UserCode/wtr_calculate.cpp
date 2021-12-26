//
// Created by stdcat on 12/25/21.
//
#include "wtr_calculate.h"

void PID_Calc(PID_t *pid){
	pid->cur_error = pid->ref - pid->fdb;
	pid->output += pid->KP * (pid->cur_error - pid->error[1]) + pid->KI * pid->cur_error + pid->KD * (pid->cur_error - 2 * pid->error[1] + pid->error[0]);
	pid->error[0] = pid->error[1];
	pid->error[1] = pid->ref - pid->fdb;
	/*设定输出上限*/
	if(pid->output > pid->outputMax) pid->output = pid->outputMax;
	if(pid->output < -pid->outputMax) pid->output = -pid->outputMax;

}

void P_Calc(PID_t *pid){
	pid->cur_error = pid->ref - pid->fdb;
	pid->output = pid->KP * pid->cur_error;
	/*设定输出上限*/
	if(pid->output > pid->outputMax) pid->output = pid->outputMax;
	if(pid->output < -pid->outputMax) pid->output = -pid->outputMax;

}