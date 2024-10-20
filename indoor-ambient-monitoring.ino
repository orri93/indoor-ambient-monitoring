#include <Arduino.h>

/* Other include header files for miscellaneous libraries */
#include <gatltick.h>

/* Local include header files */
#include "types.h"
#include "sensor.h"
#include "display.h"

/* Interval definitions */
#define INTERVAL_SENSOR 1000

/* ESP32-WROOM-32 SPI Pins

  Pins defined in the esp32 code
  ------------------------------
  MISO:  37
  MOSI:  35
  SCK:   36
  SS/CS: 34

  SPI for flash memory
  --------------------
  SCK/CLK:  GPIO  6
  SDO/SD0:  GPIO  7
  SDI/SD1:  GPIO  8
  SHD/SD2:  GPIO  9
  SWP/SD3:  GPIO 10
  CSC/CMD:  GPIO 11

  +------+---------+---------+---------+---------+
  | SPI  | MISO    | MOSI    | CLK     | CS      |
  +------+---------+---------+---------+---------+
  | HSPI | GPIO 12 | GPIO 13 | GPIO 14 | GPIO 15 |
  | VSPI | GPIO 19 | GPIO 23 | GPIO 18 | GPIO 5  |
  +------+---------+---------+---------+---------+
*/

/* Wiring
   ======


  Arduino Nano ESP32
  ------------------

    MCU             | Device
    ----------------+---------------------
    MOSI D5  GPIO8  | DOGS102 SDA/SI    24
    SCKL D6  GPIO9  | DOGS102 SCK/SCL   25
    CS   D7  GPIO10 | DOGS102 CS0/CS    28
         D8  GPIO17 | DOGS102 CD/A0     26
         D9  GPIO18 | DOGS102 RST/RESET 27
    MOSI D11 GPIO38 | BME280  SDI        3
    MISO D12 GPIO47 | BME280  SDO        5
    SCKL D13 GPIO48 | BME280  SCK        4
    CS   D10 GPIO21 | BME280  CSB        2


  ESP32 Dev Kit C 32UE
  --------------------

    MCU          | Device
    -------------+---------------------
    MOSI GPIO 13 | DOGS102 SDA/SI    24
    SCKL GPIO 14 | DOGS102 SCK/SCL   25
    CS   GPIO 15 | DOGS102 CS0/CS    28
         GPIO 16 | DOGS102 CD/A0     26
         GPIO 17 | DOGS102 RST/RESET 27
    MOSI GPIO 23 | BME280  SDI        3
    MISO GPIO 19 | BME280  SDO        5
    SCKL GPIO 18 | BME280  SCK        4
    CS   GPIO  5 | BME280  CSB        2


  ESP32 WROOM 32UE N4
  -------------------

    MCU               | Device
    ------------------+---------------------
    MOSI GPIO 13 (20) | DOGS102 SDA/SI    24
    SCKL GPIO 14 (17) | DOGS102 SCK/SCL   25
    CS   GPIO 15 (21) | DOGS102 CS0/CS    28
         GPIO 16 (25) | DOGS102 CD/A0     26
         GPIO 17 (27) | DOGS102 RST/RESET 27
    MOSI GPIO 23 (36) | BME280  SDI        3
    MISO GPIO 19 (38) | BME280  SDO        5
    SCKL GPIO 18 (35) | BME280  SCK        4
    CS   GPIO  5 (34) | BME280  CSB        2

*/

/* Serial Speed (if undefined no serial output will be generated) */
#define SERIAL_BAUD 9600

/* Serial Debugging include header file */
#ifdef SERIAL_BAUD
#include "serialdebug.h"
#endif

/* Tick instances */
::gos::atl::Tick<> tick_sensor(INTERVAL_SENSOR);

/* Sensor ambient value variables */
sensor_data sensordata;

/* General global variables */
unsigned long current;

void setup() {
  /* Initalize general global variables */
  current = 0;

#ifdef SERIAL_BAUD
  serial_debug_initiate(SERIAL_BAUD);
#endif

  /* Initalization of the DOG display instance */
  display_initiate();

  /* Initalization of the BME280 sensor instance */
  if (sensor_initiate()) {
#ifdef SERIAL_BAUD
    serial_debug_sensor_success(sensor_id());
#endif
  } else {
    uint32_t sensorid = sensor_id();
#ifdef SERIAL_BAUD
    serial_debug_sensor_failure(sensorid);
#endif
  }
}

void loop() {
  current = millis();

  if (tick_sensor.is(current)) {
    sensor_read(sensordata);

    display_update(sensordata);

#ifdef SERIAL_BAUD
    serial_debug_sensor_data(sensordata);
#endif
  }
}
