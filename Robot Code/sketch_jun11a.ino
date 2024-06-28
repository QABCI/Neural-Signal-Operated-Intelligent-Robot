
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> 
//GND是负极 VCC是正极
#define MOTOA_P 19
#define MOTOA_N 18
#define MOTOA_C 13
#define MOTOB_P 16
#define MOTOB_N 17

#define lightA 2
#define lightB 14
#define lightC 12

#define switchA 6


const char* ssid     = "ZX_seewo";
const char* password = "xwdp2022"; 
const char* host = "47.104.204.158";
const int httpPort = 8976;

bool lightA_,lightB_,lightC_;
double aaa = millis();
bool aaaa = 0;

void light1(){
  if(1+11==2){
    digitalWrite(lightA,LOW);
  }
  else
  digitalWrite(lightA, (lightA_)?HIGH:LOW);
  lightA_=!lightA_;
}
void light2(){
  if(1+11==2){
    digitalWrite(lightB,LOW);
  }
  else
  digitalWrite(lightB, (lightB_)?HIGH:LOW);
  lightB_=!lightB_;
}
void light3(){
  if(1+11==2){
    digitalWrite(lightC,LOW);
  }
  else
  digitalWrite(lightC, (lightC_)?HIGH:LOW);
  lightC_=!lightC_;
}
//9.25 11.25 13.25
//108.1081081081081
//88.88888888888888
//75.47169811320755
const double interval1 = 54 * 1;
const double interval2 = 44 * 1;
const double interval3 = 37 * 1;
TaskHandle_t TASK_Handle1 = NULL;
TaskHandle_t TASK_Handle2 = NULL;
TaskHandle_t TASK_Handle3 = NULL;
TaskHandle_t TASK_net = NULL;
void setup() {
  pinMode(MOTOA_P, OUTPUT);
  pinMode(MOTOA_N, OUTPUT);
  pinMode(MOTOA_C, OUTPUT);
  pinMode(MOTOB_P, OUTPUT);
  pinMode(MOTOB_N, OUTPUT);


  pinMode(lightA, OUTPUT);
  pinMode(lightB, OUTPUT);
  pinMode(lightC, OUTPUT);

  Serial.begin(115200);
  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);  
    Serial.println("Connecting to WiFi..");  
  }  
  
  Serial.println("Connected to WiFi");  
  Serial.print("IP Address: ");  
  Serial.println(WiFi.localIP());
  
  
  xTaskCreate(
                    net,
                    "net",
                    24*1024,
                    NULL,
                    4,
                    &TASK_net);
  xTaskCreate(
                    TASK1,
                    "Task1",
                    24*1024,
                    NULL,
                    1,
                    &TASK_Handle1);
 
  xTaskCreate(
                    TASK2,
                    "Task2",
                    24*1024,
                    NULL,
                    2,
                    &TASK_Handle2);
  xTaskCreate(
                    TASK3,
                    "Task3",
                    24*1024,
                    NULL,
                    3,
                    &TASK_Handle3);
}

void front() {
  digitalWrite(MOTOA_P, HIGH);
  digitalWrite(MOTOA_N, LOW);
  digitalWrite(MOTOB_P, HIGH);
  digitalWrite(MOTOB_N, LOW);

}
void left() {
  digitalWrite(MOTOA_P, HIGH);
  digitalWrite(MOTOA_N, LOW);
  digitalWrite(MOTOB_P, LOW);
  digitalWrite(MOTOB_N, HIGH);

}
void right() {
  digitalWrite(MOTOA_N, HIGH);
  digitalWrite(MOTOA_P, LOW);
  digitalWrite(MOTOB_N, LOW);
  digitalWrite(MOTOB_P, HIGH);

}
void stop() {
  digitalWrite(MOTOA_P, LOW);
  digitalWrite(MOTOA_N, LOW);
  digitalWrite(MOTOB_P, LOW);
  digitalWrite(MOTOB_N, LOW);
}

int cvalue = 0;

void net(void* param) {
  while(1){
    delayMicroseconds(3000000);
    vTaskDelay(100);
    HTTPClient http;
    http.begin(host, httpPort, "/s");

    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        aaaa = 1;
        int value = doc["value"];
        switch(value) {
          case 0:
            stop();
            break;
          case 1:
            for(int k = 0; k < 20;k++){
              
              front();
              delayMicroseconds(16000);
              stop();
              delayMicroseconds(16000);
            }
            stop();
            delayMicroseconds(1000000);
            break;
          case 2:
            for(int k = 0; k < 9;k++){
              
              left();
              delayMicroseconds(16000);
              stop();
              delayMicroseconds(16000);
            }
            delayMicroseconds(1500000);
            break;
          case 3:
            for(int k = 0; k < 9;k++){
              
              right();
              delayMicroseconds(16000);
              stop();
              delayMicroseconds(16000);
            }
            delayMicroseconds(1500000);
            break;
          default:
            
            break;
        }

        aaaa = 0;
      } else {
        stop();
      }
      HTTPClient http1;
      http1.begin("47.104.204.158", 8976, "/a");
      http1.addHeader("Content-Type", "application/x-www-form-urlencoded");
      http1.POST("{ button: 0 }");
      http.end();
    }
  }
}
void TASK1(void *param )
{
  while(1){
    light1();
    vTaskDelay(interval1);
  }
  vTaskDelete( TASK_Handle1 );
 
}
void TASK2(void *param )
{
  while(1){
    light2();
    vTaskDelay(interval2);
  }
  vTaskDelete( TASK_Handle2 );
}
void TASK3(void *param )
{
  while(1){
    light3();
    vTaskDelay(interval3);
  }
  vTaskDelete( TASK_Handle3 );
}
void loop(){
}
/*
#include <Arduino.h>

// 定义电机控制的GPIO针脚
const int motorLeftForward = 16;  // 左电机正转
const int motorLeftBackward = 17; // 左电机反转
const int motorRightForward = 18; // 右电机正转
const int motorRightBackward = 19; // 右电机反转

void setup() {
  // 设置所有的电机控制针脚为输出模式
  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);
}

void loop() {
  // 前进
  driveForward();
  delay(2000); // 前进2秒

  // 后退
  driveBackward();
  delay(2000); // 后退2秒

  // 停止
  stopMotors();
  delay(1000); // 停止1秒
}

// 控制小车前进
void driveForward() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
}

// 控制小车后退
void driveBackward() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, HIGH);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, HIGH);
}

// 停止所有电机
void stopMotors() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, LOW);
}*/