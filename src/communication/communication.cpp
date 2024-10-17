// Callback ฟังก์ชันสำหรับ WebSocket events
#include "communication.h"

void Communication::webSocketEvent(uint8_t client_num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("Client %u disconnected\n", client_num);
      break;

    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(client_num);
      Serial.printf("Client %u connected from %s\n", client_num, ip.toString().c_str());
      break;
    }

    case WStype_TEXT:
      Serial.printf("Message from client %u: %s\n", client_num, payload);
      messageJson = parseJson((char*)payload);

      break;
  }
}

void Communication::send(int pressureValue) {
    // สร้าง JSON object สำหรับส่งข้อมูล
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["id"] = "gripper";
    jsonDoc["sensors"]["pressure"] = pressureValue;

    // แปลง JSON object เป็น string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    // ส่งข้อความไปยัง client ทุกคนที่เชื่อมต่อ
    webSocket.broadcastTXT(jsonString);
}

JsonDocument Communication::parseJson(String string) {
  JsonDocument doc;

  DeserializationError error = deserializeJson(doc, string);

  // Test if parsing succeeded.
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.f_str());
  }

  String id = doc["id"];
  String command = doc["command"];
  
  return doc;
}