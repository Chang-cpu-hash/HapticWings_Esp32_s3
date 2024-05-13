#include <Arduino.h>
#include "AirPump.h"
#include "ServoControl.h"

// --------------------- 其他部分 ---------------------
#define LED_PIN 13

ServoControl servoControl(9, 10); // 创建一个舵机控制对象，指定引脚

void setup()
{
    // 设置LED引脚为输出模式
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
    Serial.println("Hello World!");
    pinMode(airPumpPin, OUTPUT);            // 设置引脚输出
    pinMode(airValvePin, OUTPUT);           // 设置引脚输出
    digitalWrite(airPumpPin, airPumpOFF);   // 初始状态 关闭气泵 停止充气
    digitalWrite(airValvePin, airValveOFF); // 初始状态 气阀打开 开启放气
}

void loop()
{
    servoControl.setAngle(1, 90); // 设置第一个舵机到90度
    delay(1000);
    servoControl.setAngle(2, 180); // 设置第二个舵机到180度
    delay(1000);
}
