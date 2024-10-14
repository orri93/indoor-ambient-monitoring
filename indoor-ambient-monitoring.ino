#include <Arduino.h>
#include <SPI.h>

/* Include header files for the Adafruit BME280 library */
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

/* Include header files for the DOGS102 Display library */
#include <dog_1701.h>

/* Other include header files for miscellaneous libraries */
#include <gatltick.h>

/* Local include header files */
#include "fonts.h"
#include "logo.h"

/* Interval definitions */
#define INTERVAL_SENSOR 1000

/* Ambient definitions */
#define SEALEVELPRESSURE_HPA (1013.25)

#define ESP32WROOM_TEST_PIN HSPI

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

/* Pins for the BME280 sensor */
#define PIN_BME_CSB   SS

/* Pins for the DOGS102 Display */
#define PIN_DOG_SI    13
#define PIN_DOG_SCK   14
#define PIN_DOG_CS    15
#define PIN_DOG_A0    16
#define PIN_DOG_RST   17

/* Serial Speed (if undefined no serial output will be generated) */
#define SERIAL_BAUD 9600

/* Other definitions */
#define NFB_SIZE      16

/* The BME280 sensor instance */
Adafruit_BME280 bme(PIN_BME_CSB, &SPI);

/* The DOG Display instance */
dog_1701 dog;

/* Tick instances */
::gos::atl::Tick<> tick_sensor(INTERVAL_SENSOR);

/* Sensor ambient value variables */
float sensor_temperature, sensor_pressure, sensor_humidity;

/* General global variables */
static char nfb[NFB_SIZE];
unsigned long current;

void setup() {
  /* Initalize general global variables */
  current = 0;

#ifdef SERIAL_BAUD
  Serial.begin(SERIAL_BAUD);
  while(!Serial);
  Serial.println("Indoor Ambient Monitoring");
  Serial.println("Copyright 2024 Geirmundur Orri Sigurdsson");
#endif

  /* Initalization of the DOG display instance */
  /* Parameter order is CS, SI, CLK, A0, RES */
  dog.initialize(PIN_DOG_CS, PIN_DOG_SI, PIN_DOG_SCK, PIN_DOG_A0, PIN_DOG_RST, DOGS102);
  dog.clear();
  dog.picture(0, 0, logo);

  /* Initalization of the BME280 sensor instance */
  pinMode(PIN_BME_CSB, OUTPUT);
  if (bme.begin()) {
#ifdef SERIAL_BAUD
    Serial.print("A valid BME280 sensor found with SensorID: 0x");
    Serial.println(bme.sensorID(), 16);
#endif
  } else {
#ifdef SERIAL_BAUD
    Serial.println("Could not find a valid BME280 sensor!");
    Serial.print("SensorID: 0x");
    Serial.println(bme.sensorID(), 16);
#endif
  }
}

void loop() {
  current = millis();

  if (tick_sensor.is(current)) {
    sensor_temperature = bme.readTemperature(); /* °C*/
    sensor_pressure = bme.readPressure(); /* Pa */
    sensor_humidity = bme.readHumidity(); /* % */

    dtostrf(sensor_temperature, 0, 2, nfb);
    dog.string(0, 4, font_16x32nums, nfb);

#ifdef SERIAL_BAUD
    Serial.print("Temperature = ");
    Serial.print(sensor_temperature);
    Serial.println(" °C");
    Serial.print("Pressure = ");
    Serial.print(sensor_pressure / 100.0F);
    Serial.println(" hPa");
    Serial.print("Humidity = ");
    Serial.print(sensor_humidity);
    Serial.println(" %");
#endif
  }
}
