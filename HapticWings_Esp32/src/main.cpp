#include <Arduino.h>
#include "AirPump.h"
#include <ESP32Servo.h> // 引入ESPServo库
#include <Communication.h>

// --------------------- 其他部分 ---------------------

Servo frontMyServo1;
Servo frontMyServo2;
Servo backMyServo;
Servo upperMyMiniServo1;
Servo upperMyMiniServo2;

const int frontServoPin1 = 18; // 定义舵机连接的引脚
const int frontServoPin2 = 5;  // 定义气泵连接的引脚
const int backServoPin = 19;   // 定义气阀连接的引脚
const int upperMiniServoPin1 = 21;
const int upperMiniServoPin2 = 22;

bool test = true;

void setup()
{
    Serial.begin(115200);
    Serial.println("Hello World!");
    pinMode(airPumpPin, OUTPUT);            // 设置引脚输出
    pinMode(airValvePin, OUTPUT);           // 设置引脚输出
    digitalWrite(airPumpPin, airPumpOFF);   // 初始状态 关闭气泵 停止充气
    digitalWrite(airValvePin, airValveOFF); // 初始状态 气阀打开 开启放气

    frontMyServo1.attach(frontServoPin1);
    frontMyServo2.attach(frontServoPin2);
}

void loop()
{
    if (test)
    {
        for (int angle = 0; angle <= 180; angle += 1)
        {                               // 从0度转到180度
            frontMyServo1.write(angle); // 设置舵机角度
            frontMyServo2.write(angle); // 设置舵机角度
            delay(15);                  // 等待15毫秒
        }
        for (int angle = 180; angle >= 0; angle -= 1)
        {                               // 从180度转回到0度
            frontMyServo1.write(angle); // 设置舵机角度
            frontMyServo2.write(angle); // 设置舵机角度
            delay(15);                  // 等待15毫秒
        }
    }
    else
    {
        long *Command = SerialReceive();
        if (Command[0] == 0 || Command[0] == 1)
        {
            frontMyServo1.write(Command[1]);
            frontMyServo2.write(Command[2]);
            backMyServo.write(Command[3]);
            upperMyMiniServo1.write(Command[4]);
            upperMyMiniServo2.write(Command[5]);
            if (Command[0] == 0)
            {
                
            }
            if (Command[0] == 1)
            {

            }
        }
    }
}
