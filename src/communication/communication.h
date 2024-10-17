#ifndef COMMUNICATION_H
    #define COMMUNICATION_H
    #include <ArduinoJson.h>
    #include <WebSocketsServer.h>
    class Communication{
        private:
        public:
            WebSocketsServer webSocket;
            Communication(uint16_t port) : webSocket(port) {}

    // ฟังก์ชันสำหรับการเริ่มต้น WebSocket
            void begin() {
                webSocket.begin();
                webSocket.onEvent([this](uint8_t client_num, WStype_t type, uint8_t * payload, size_t length) {
                    webSocketEvent(client_num, type, payload, length);
                });
            }

            JsonDocument messageJson;
            void webSocketEvent(uint8_t client_num, WStype_t type, uint8_t * payload, size_t length);
            JsonDocument parseJson(String string);
            void send(int presureValue, int switchValue);
    };
#endif