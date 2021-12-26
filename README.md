# WTR Serial2Motor

*author: Siqi Liang*

使用手册参考：[WTR Serial2Motor.md](WTR Serial2Motor.md)

## Environment

- Ubuntu 18.04
- STM32CubeIDE C/C++混编

## STM32

- Robomaster  A型开发板 STM32f427IIHx

## Third Parties

- 有限状态机FSM [r-lyeh-archived/fsm](https://github.com/r-lyeh-archived/fsm)

## Intro

- 通过从 `uart6` 接受串口数据命令来发送CAN数据包控制电机运行，可以选择的操作有 速度伺服和位置伺服
- 板载LED灯会根据当前状态亮起提示串口的工作状态和电机是否使能
- 使用有限状态机整理逻辑 开发时感觉更加方便