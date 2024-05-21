#include "CommunicationEsp.h"
#include <Arduino.h>
#include <ArduinoJson.h>

// 传递以下五个变量：
// 前端舵机1的角度，前端舵机2的角度，
// 后端舵机1的角度，上端小型舵机1的角度，上端小型舵机2的角度

// 示例 JSON 消息格式：
// {"Mode": "Run", "Servos": [{"Angle1": 90, "Angle2": 90}, {"Angle3": 90}, {"Angle4": 180, "Angle5": 180}]}
// {"Mode": "Run", "Servos": [{"Angle1": 0, "Angle2": 0}, {"Angle3": 0}, {"Angle4": 180, "Angle5": 180}]}
// {"Mode": "Init", "Servos": [{"Angle1": 30, "Angle2": 30}, {"Angle3": 45}, {"Angle4": 0, "Angle5": 0}]}


