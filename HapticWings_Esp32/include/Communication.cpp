#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <ArduinoJson.h>

// 传递以下五个变量：
// 前端舵机1的角度，前端舵机2的角度，
// 后端舵机1的角度，上端小型舵机1的角度，上端小型舵机2的角度

// 示例 JSON 消息格式：
// {"Mode": "Run", "Servos": [{"Angle1": 90, "Angle2": 90}, {"Angle3": 90}, {"Angle4": 180, "Angle5": 180}]}
// {"Mode": "Run", "Servos": [{"Angle1": 0, "Angle2": 0}, {"Angle3": 0}, {"Angle4": 180, "Angle5": 180}]}
// {"Mode": "Init", "Servos": [{"Angle1": 30, "Angle2": 30}, {"Angle3": 45}, {"Angle4": 0, "Angle5": 0}]}

long* SerialReceive() {
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
