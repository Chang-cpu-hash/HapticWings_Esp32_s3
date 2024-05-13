#include "AirPump.h"

void startInflation(unsigned long time) {
    digitalWrite(airPumpPin, airPumpON);  // 开启充气
    digitalWrite(airValvePin, airValveOFF); // 关闭放气
    startTime = millis();  // 记录开始充气的时间
    inflationDuration = time;  // 设置充气时间长度
    isOperating = true;  // 标记为正在操作
    airVolume += time / 1000; // 假设每秒钟充气增加1单位气体量
}

void startDeflation(unsigned long time) {
    digitalWrite(airPumpPin, airPumpOFF);  // 关闭充气
    digitalWrite(airValvePin, airValveON);  // 开启放气
    startTime = millis();  // 记录开始放气的时间
    deflationDuration = time;  // 设置放气时间长度
    isOperating = true;  // 标记为正在操作
    airVolume -= time / 1000; // 假设每秒钟放气减少1单位气体量
}

int getCurrentAirVolume() {
    return airVolume;
}

void updateOperations() {
    unsigned long currentMillis = millis();

    if (isOperating && startTime + inflationDuration <= currentMillis && inflationDuration != 0) {
        digitalWrite(airPumpPin, airPumpOFF);  // 时间到，停止充气
        inflationDuration = 0;  // 重置充气时间
        isOperating = false;  // 更新状态
    }

    if (isOperating && startTime + deflationDuration <= currentMillis && deflationDuration != 0) {
        digitalWrite(airValvePin, airValveOFF);  // 时间到，停止放气
        deflationDuration = 0;  // 重置放气时间
        isOperating = false;  // 更新状态
    }
}