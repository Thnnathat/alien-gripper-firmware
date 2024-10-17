#ifndef PRESSURE_SENSOR_H
    #define PRESSURE_SENSOR_H
    class HX710B {
      private:
        // สามารถเพิ่มตัวแปรภายในคลาสได้ที่นี่
      public:
        long readHX710B();  // ประกาศฟังก์ชันสำหรับอ่านข้อมูลจากเซนเซอร์
        long pressure(long rawValue);
    };

#endif