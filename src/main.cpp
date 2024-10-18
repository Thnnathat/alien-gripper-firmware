// กำหนดขา TX และ RX สำหรับ Serial1
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WebSocketsServer.h>
#include <WiFi.h>

#include "config.h"

#include "pressureSensor/pressure_sensor.h"
#include "relayControl/relay_control.h"
#include "communication/communication.h"
#include "gripperControl/gripper_control.h"

void init();
void task();
void wifiDHCP();
void wifiStatic();

HX710B hx710b;
Communication com = Communication(81);
RelayControl relay;
GripperControl alien = GripperControl(relay);



const char* ssid = "mi10tpro";  // เปลี่ยนเป็น SSID ของคุณ
const char* password = "33333333"; // เปลี่ยนเป็น Password ของคุณ

void setup() {
  init();
  delay(1000);
}

void loop() {
  com.webSocket.loop();
  task();
}

void init() {
  Serial.begin(serial_baudrate);

  pinMode(switchSensor, INPUT);
  pinMode(relay_A, OUTPUT);
  pinMode(relay_B, OUTPUT);
  pinMode(relay_P, OUTPUT);

  digitalWrite(relay_A, HIGH);
  digitalWrite(relay_B, HIGH);
  digitalWrite(relay_P, HIGH);

  // กำหนด Clock pin เป็น OUTPUT
  pinMode(clockPin, OUTPUT);
  
  // กำหนด Data pin เป็น INPUT
  pinMode(dataPin, INPUT);

  // Wifi connection
  wifiDHCP();

  Serial.println("Connected to WiFi");
  Serial.print("Ip: ");
  Serial.println(WiFi.localIP()); // แสดง IP Address
  com.begin();
}

void wifiDHCP(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void wifiStatic() {
  IPAddress local_IP(192, 168, 8, 166);    // IP Address ของ ESP32
  IPAddress gateway(192, 168, 8, 142);       // Gateway ของเครือข่าย
  IPAddress subnet(255, 255, 255, 0);      // Subnet Mask
  IPAddress primaryDNS(8, 8, 8, 8);        // Primary DNS (Google Public DNS)
  IPAddress secondaryDNS(8, 8, 4, 4);      // Secondary DNS (Google Public DNS)

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

void task() {
  static unsigned long lastSendTime = 0;
  unsigned long currentMillis = millis();

  alien.action(com.messageJson);

  if (currentMillis - lastSendTime >= 100) {  // ส่งข้อมูลทุก 100 ms ปรับให้ช้าลงถ้าคิวเกิน
    lastSendTime = currentMillis;

    // อ่านค่าจากเซ็นเซอร์ (เช่น HX710B)
    float pressureValue = hx710b.readHX710B();  // สมมติว่าเป็นการอ่านค่าแรงดัน
    int switchValue = digitalRead(switchSensor);

    com.send(pressureValue, switchValue);
  }
}