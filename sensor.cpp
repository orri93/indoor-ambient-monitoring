#include <Arduino.h>
#include <SPI.h>

#include "sensor.h"

/* The BME280 sensor instance */
static Adafruit_BME280 bme(PIN_BME_CSB, &SPI);

bool sensor_initiate(sensor_data &data) {
  /* Initalize sensor data */
  data.temperature = 0.0F;
  data.pressure = 0.0F;
  data.humidity = 0.0F;
  /* Initalization of the BME280 sensor instance */
  pinMode(PIN_BME_CSB, OUTPUT);
  return bme.begin();
}

void sensor_read(sensor_data &data) {
  /* Read sensor data */
  data.temperature = bme.readTemperature(); /* °C*/
  data.pressure = bme.readPressure(); /* Pa */
  data.humidity = bme.readHumidity(); /* % */
}

uint32_t sensor_id() {
  return bme.sensorID();
}
