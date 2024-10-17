#ifndef CONFIG_H
    #define CONFIG_H

    #include <WiFi.h>

    // ! เปลี่ยน Pin ด้วยความระวัง มันอ่อนไหวมาก
    // กำหนดขา HSPI ที่ใช้สำหรับ W5500
    #define HSPI_SCK  14  // SCK บน HSPI
    #define HSPI_MISO 12  // MISO บน HSPI
    #define HSPI_MOSI 13  // MOSI บน HSPI
    #define HSPI_CS   15  // CS (Chip Select) บน HSPI
    #define W5500_RST 4   // ขา RST สำหรับ W5500
    
    const int switchSensor = 34;
    const int relay_A = 22;
    const int relay_B = 23;
    const int relay_P = 21;

    const int clockPin = 18;  // SCK เชื่อมต่อกับขา GPIO 18 บน ESP32
    const int dataPin = 19;   // DOUT เชื่อมต่อกับขา GPIO 19 บน ESP32

    const int serial_baudrate = 115200;

#endif