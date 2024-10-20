#include "serialdebug.h"

void serial_debug_initiate(long baud) {
  Serial.begin(baud);
  while(!Serial);
  Serial.println("Indoor Ambient Monitoring");
  Serial.println("Copyright 2024 Geirmundur Orri Sigurdsson");
}

void serial_debug_sensor_success(uint32_t sensorid) {
  Serial.print("A valid BME280 sensor found with SensorID: 0x");
  Serial.println(sensorid, 16);
}

void serial_debug_sensor_failure(uint32_t sensorid) {
  Serial.println("Could not find a valid BME280 sensor!");
  Serial.print("SensorID: 0x");
  Serial.println(sensorid, 16); 
}

void serial_debug_sensor_data(const sensor_data& sensordata) {
  Serial.print("Temperature = ");
  Serial.print(sensordata.temperature);
  Serial.println(" °C");
  Serial.print("Pressure = ");
  Serial.print(sensordata.pressure / 100.0F);
  Serial.println(" hPa");
  Serial.print("Humidity = ");
  Serial.print(sensordata.humidity);
  Serial.println(" %");
}