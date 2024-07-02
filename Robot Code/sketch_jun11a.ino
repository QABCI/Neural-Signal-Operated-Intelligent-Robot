
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> 

                            //car motor 1
#define MOTOA_P 19
#define MOTOA_N 18
                            //car motor 2
#define MOTOB_P 16
#define MOTOB_N 17
                            //light
#define lightA 2            //light front
#define lightB 14           //light left
#define lightC 12           //light right

const char* ssid     = "Your Wifi Name";
const char* password = "Your Wifi Password"; 
const char* host = "here.should.be.your.server.ip";
const int httpPort = 8976;

bool lightA_,lightB_,lightC_; //state of each light

void light1(){ 
  digitalWrite(lightA, (lightA_)?HIGH:LOW);
  lightA_=!lightA_;
}

void light2(){
  digitalWrite(lightB, (lightB_)?HIGH:LOW);
  lightB_=!lightB_;
}

void light3(){
  digitalWrite(lightC, (lightC_)?HIGH:LOW);
  lightC_=!lightC_;
}


const double interval1 = 54 * 1;  //delay interval
const double interval2 = 44 * 1;
const double interval3 = 37 * 1;

TaskHandle_t TASK_Handle1 = NULL; //Task handle for light
TaskHandle_t TASK_Handle2 = NULL;
TaskHandle_t TASK_Handle3 = NULL;
TaskHandle_t TASK_net = NULL;     //Task handle for network
void setup() {
  //set pinMode for each pin
  pinMode(MOTOA_P, OUTPUT);
  pinMode(MOTOA_N, OUTPUT);
  
  pinMode(MOTOB_P, OUTPUT);
  pinMode(MOTOB_N, OUTPUT);


  pinMode(lightA, OUTPUT);
  pinMode(lightB, OUTPUT);
  pinMode(lightC, OUTPUT);
  //setup the serial port
  Serial.begin(115200);
  
  //setup the wifi
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);  
    Serial.println("Connecting to WiFi..");  
  }  
  
  Serial.println("Connected to WiFi");  
  Serial.print("IP Address: ");  
  Serial.println(WiFi.localIP());
  
  //create the network task
  xTaskCreate(
                    net,
                    "net",
                    24*1024,
                    NULL,
                    4,
                    &TASK_net);
  //create the light task
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

//car ctrl
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

void net(void* param) {
  //get data from server
  while(1){
    delayMicroseconds(3000000);//each 3 second, the python script will update a SSVEP data
    vTaskDelay(100);
    HTTPClient http;
    http.begin(host, httpPort, "/s");//get data from server

    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        int value = doc["value"];
        switch(value) {
          case 0:
            stop();
            break;
          case 1://👆
            for(int k = 0; k < 20;k++){//using the PWM to control the motor
              
              front();
              delayMicroseconds(16000);
              stop();
              delayMicroseconds(16000);
            }
            stop();
            delayMicroseconds(1000000);
            break;
          case 2://👈
            for(int k = 0; k < 9;k++){//using the PWM to control the motor
              
              left();
              delayMicroseconds(16000);
              stop();
              delayMicroseconds(16000);
            }
            delayMicroseconds(1500000);
            break;
          case 3://👉
            for(int k = 0; k < 9;k++){//using the PWM to control the motor
              
              right();
              delayMicroseconds(16000);
              stop();
              delayMicroseconds(16000);
            }
            delayMicroseconds(1500000);
            break;
          default:
            //ERROR
            break;
        }
      } else {
        stop();
      }
      HTTPClient http1;
      http1.begin(host, httpPort, "/a");
      http1.addHeader("Content-Type", "application/x-www-form-urlencoded");
      http1.POST("{ button: 0 }"); //reset the server data
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
  //make sure the Arduino will run
}