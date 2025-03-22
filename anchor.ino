/*

For ESP32 UWB or ESP32 UWB Pro

*/

#include <SPI.h> // ใช้ SPI.h สำหรับการสื่อสารผ่าน SPI ระหว่าง ESP32 และ DW1000
#include "DW1000Ranging.h" // library ที่ช่วยให้จัดการกับ DW1000

#define ANCHOR_ADD "86:17:5B:D5:A9:9A:E2:9C"

#define SPI_SCK 18 // Clock
#define SPI_MISO 19 // Master In, Slave Out
#define SPI_MOSI 23 // Master Out, Slave In
#define DW_CS 4 // Chip Select

// connection pins
const uint8_t PIN_RST = 27; // reset pin
const uint8_t PIN_IRQ = 34; // irq pin
const uint8_t PIN_SS = 4;   // spi select pin

void setup()
{
    Serial.begin(115200);
    delay(1000);
    //init the configuration
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    // ตั้งค่าการสื่อสารระหว่าง ESP32 และ DW1000
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin 
    //define the sketch as anchor. It will be great to dynamically change the type of module

    // ตั้งค่าฟังก์ชัน newRange() สำหรับการรับค่าระยะทางจาก Tag
    DW1000Ranging.attachNewRange(newRange);
    // ตั้งค่าฟังก์ชัน newBlink() เพื่อเพิ่มอุปกรณ์ใหม่ที่ส่งสัญญาณเข้ามา
    DW1000Ranging.attachBlinkDevice(newBlink);
    // ตั้งค่าฟังก์ชัน inactiveDevice() เพื่อลบอุปกรณ์ที่ไม่ได้ส่งสัญญาณ
    DW1000Ranging.attachInactiveDevice(inactiveDevice);
    //Enable the filter to smooth the distance
    //DW1000Ranging.useRangeFilter(true);

    //we start the module as an anchor
    // DW1000Ranging.startAsAnchor("82:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);

    // กำหนดให้ ESP32 เป็น Anchor โดยใช้ UWB Long-Range Mode
    // ANCHOR_ADD คือ Address ของ Anchor ในรูปแบบ MAC Address
    // DW1000.MODE_LONGDATA_RANGE_LOWPOWER: ใช้โหมดที่เน้นการประหยัดพลังงานและระยะทางไกล
    DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false); 

    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_SHORTDATA_FAST_LOWPOWER);
    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_FAST_LOWPOWER);
    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_SHORTDATA_FAST_ACCURACY);
    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_FAST_ACCURACY);
    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_RANGE_ACCURACY);
}

void loop()
{
    // รอรับข้อมูลจาก Tag ที่ส่งสัญญาณมา
    // คำนวณระยะทางและพิมพ์ข้อมูลลง Serial Monitor
    DW1000Ranging.loop(); 
}

void newRange()
{
    Serial.print("from: ");
    Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
    Serial.print("\t Range: ");
    Serial.print(DW1000Ranging.getDistantDevice()->getRange()); // คืนค่าระยะทางที่คำนวณได้ (หน่วยเป็น เมตร)
    Serial.print(" m");
    Serial.print("\t RX power: ");
    Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); // แสดงพลังงานของสัญญาณที่รับเข้ามา (dBm)
    Serial.println(" dBm");
}

// เมื่อมีอุปกรณ์ใหม่ที่ส่งสัญญาณเข้ามา
// ถูกเรียกเมื่อมี Tag ใหม่ที่ยังไม่ได้จับคู่เข้ามา
// ใช้เพื่อระบุว่าอุปกรณ์ Tag ไหนเพิ่งส่งสัญญาณมา
void newBlink(DW1000Device *device)
{
    Serial.print("blink; 1 device added ! -> ");
    Serial.print(" short:");
    Serial.println(device->getShortAddress(), HEX);
}

// ลบอุปกรณ์ที่ไม่ได้ส่งสัญญาณ
void inactiveDevice(DW1000Device *device)
{
    Serial.print("delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
}
