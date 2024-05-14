// AirPump.h
#ifndef AIRPUMP_SENSOR_H
#define AIRPUMP_SENSOR_H
#include "Arduino.h"
#include <ArduinoJson.h>

// --------------------- 关于气泵 ---------------------
// 气泵引脚和宏的相关参数
String buff = "";

// const size_t capacity = JSON_OBJECT_SIZE(3) + 2*JSON_ARRAY_SIZE(2) + 4*JSON_OBJECT_SIZE(2); // 修改为适当的 JSON 容量，以适应舵机和步进电机的信息
const size_t capacity = 512;
StaticJsonDocument<capacity> jb;

long *SerialReceive();

#endif