#include <math.h>
#include <Arduino.h>
#include "config.h"
#include "pressure_sensor.h"

long HX710B::readHX710B() {
    long count = 0;

    // รอจนกว่าข้อมูลจะพร้อม (DOUT = LOW)
    while (digitalRead(dataPin));

    // เริ่มต้นการอ่าน 24 บิตจาก HX710B
    for (int i = 0; i < 24; i++) {
        digitalWrite(clockPin, HIGH);
        count = count << 1;  // เลื่อนบิตเพื่อเตรียมรับข้อมูล
        digitalWrite(clockPin, LOW);
        
        if (digitalRead(dataPin)) {
            count++;
        }
    }

    // อ่านบิตที่ 25 เพื่อตั้งค่า gain (ขยายสัญญาณ)
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);

    // เปลี่ยนข้อมูลที่อ่านได้เป็นค่า signed (ค่าเป็นบวกหรือลบ)
    count ^= 0x800000;

    return count;
};

long HX710B::pressure(long rawValue) {
    const float maxRawValue = 16777216.0;  // ค่าสูงสุดของค่าดิบ 24 บิต (2^24)
    const float fullScalePressure = 40.0; // ช่วงความดันที่เซ็นเซอร์วัดได้ (40 kPa)

    float pressure = ((rawValue / maxRawValue) * fullScalePressure) * pow(10.0, 3.0);
    return pressure;
}