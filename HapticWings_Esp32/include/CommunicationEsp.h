// AirPump.h
#ifndef COMMUNICATION_ESP_H
#define COMMUNICATION_ESP_H
#include "Arduino.h"
#include <ArduinoJson.h>

// --------------------- 关于气泵 ---------------------
// 气泵引脚和宏的相关参数
String buff = "";

// const size_t capacity = JSON_OBJECT_SIZE(3) + 2*JSON_ARRAY_SIZE(2) + 4*JSON_OBJECT_SIZE(2); // 修改为适当的 JSON 容量，以适应舵机和步进电机的信息
const size_t capacity = 512;
StaticJsonDocument<capacity> jb;

long* MySerialReceive(){
    static long Command[6];
    if (Serial.available()) {
        String buff;
        char inChar = '\0'; // 初始化字符
        while (inChar != '\n') {
            while (!Serial.available()); // 等待数据
            inChar = (char)Serial.read();
            if (inChar == '\n') {
                Serial.println(buff);
                StaticJsonDocument<200> jb; // 调整大小根据实际需求
                DeserializationError err = deserializeJson(jb, buff);
                if (err) {
                    Serial.print(F("deserializeJson() failed: "));
                    Serial.println(err.c_str());
                }

                String mode = jb["Mode"];
                if (mode == "Init") {
                    Command[0] = 0;
                } else if (mode == "Run") {
                    Command[0] = 1;
                }

                JsonArray servoDataArray = jb["Servos"];
                JsonObject frontServos = servoDataArray[0];
                JsonObject rearServo = servoDataArray[1];
                JsonObject upperServos = servoDataArray[2];

                if (!frontServos.isNull()) {
                    Command[1] = frontServos["Angle1"];
                    Command[2] = frontServos["Angle2"];
                }
                if (!rearServo.isNull()) {
                    Command[3] = rearServo["Angle3"];
                }
                if (!upperServos.isNull()) {
                    Command[4] = upperServos["Angle4"];
                    Command[5] = upperServos["Angle5"];
                }

                buff = "";
            } else {
                buff += inChar;
            }
        }
    } else {
        for (int i = 0; i < 6; i++) {
            Command[i] = 99; // 默认值，表示没有新的指令
        }
        return Command;
    }
    return Command;
}


#endif