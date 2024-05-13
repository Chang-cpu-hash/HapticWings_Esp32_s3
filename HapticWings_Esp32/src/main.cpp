#include <Arduino.h>
#include "AirPump.h"

// --------------------- 其他部分 ---------------------
#define LED_PIN 13

void setup() {
  // 设置LED引脚为输出模式
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Hello World!");

  pinMode(airPumpPin, OUTPUT);             // 设置引脚输出
  pinMode(airValvePin, OUTPUT);            // 设置引脚输出
  digitalWrite(airPumpPin, airPumpOFF);    // 初始状态 关闭气泵 停止充气
  digitalWrite(airValvePin, airValveOFF);  // 初始状态 气阀打开 开启放气
  
}

void loop() {
  
}


