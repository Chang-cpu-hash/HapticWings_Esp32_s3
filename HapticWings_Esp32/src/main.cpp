#include <Arduino.h>

// --------------------- 关于气泵 ---------------------
// 气泵引脚和宏的相关参数
#define airPumpPin    5                    // 控制气泵充气 引脚
#define airValvePin   6                    // 控制气阀放气 引脚
#define airPumpON     HIGH                 // 气泵打开 开启充气
#define airPumpOFF  !airPumpON             // 气泵关闭 停止充气
#define airValveON     HIGH                // 气阀打开 开启放气
#define airValveOFF  !airValveON           // 气阀关闭 停止放气

// 初始化以及系统状态参数
#define initializeTime    5000             // 初始化放气 加载时间（1秒 = 1000毫秒）  *可调*
unsigned long runRecordTime = 0;           // 运行记录时间
#define inflatableTime    500              // 充气时间（1秒 = 1000毫秒）       *可调*
#define deflationTime     240              // 放气时间（1秒 = 1000毫秒）       *可调*
uint8_t systemRunState = 0x00;             // 系统运行状态

// 全局变量记录气体总时间
unsigned long totalInflatableTime = 0;
unsigned long lastInflationStartTime = 0;
unsigned long startTime = 0;
unsigned long inflationDuration = 0;
unsigned long deflationDuration = 0;
bool isOperating = false; // 是否正在充气或放气
int airVolume = 0; // 初始气体量为0，单位假设


// 函数
// 开始充气，参数为充气时间（毫秒）
void startInflation(unsigned long time);
// 开始放气，参数为放气时间（毫秒）
void startDeflation(unsigned long time);
// 停止充放气，维持当前状态
int getCurrentAirVolume();
// 获取已充气的总时间（毫秒）
void updateOperations();

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
