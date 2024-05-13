// ServoControl.h
#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Servo.h>

class ServoControl {
public:
    ServoControl(int pin1, int pin2); // 构造函数声明
    void setAngle(int servoNumber, int angle); // 设置舵机角度的方法

private:
    Servo servo1;  // 为每个舵机创建一个Servo对象
    Servo servo2;
    int _pin1, _pin2; // 舵机的引脚
};

#endif
