#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <SPI.h>

/* Include header files for the Adafruit BME280 library */
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "types.h"

/* Ambient definitions */
#define SEALEVELPRESSURE_HPA (1013.25)

/* Pins for the BME280 sensor */
#define PIN_BME_CSB   SS

bool sensor_initiate(sensor_data &data);
void sensor_read(sensor_data &data);
uint32_t sensor_id();

#endif
