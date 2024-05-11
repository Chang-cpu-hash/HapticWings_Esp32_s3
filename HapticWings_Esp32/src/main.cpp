#include <Arduino.h>

// put function declarations here:
#define LED_PIN 9

void setup() {
  // 设置LED引脚为输出模式
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Hello World!");
}

void loop() {
  // 打开LED
  digitalWrite(LED_PIN, HIGH);
  delay(1000); // 等待一秒
  // 关闭LED
  digitalWrite(LED_PIN, LOW);
  delay(1000); // 等待一秒
}