#include "serialdebug.h"
#include "secrets.h"

void serial_debug_initiate(long baud) {
  Serial.begin(baud);
  while(!Serial);
  Serial.println("Indoor Ambient Monitoring");
  Serial.println("Copyright 2024 Geirmundur Orri Sigurdsson");
}

void serial_debug_wifi_connecting() {
  Serial.print("Connecting to WiFi ");
}

void serial_debug_wifi_connection_success(const IPAddress& ip) {
  Serial.println("");
  Serial.print("Connected to WiFi with IP: ");
  Serial.println(ip);
}

void serial_debug_wifi_lost_connection() {
  Serial.println("Lost connection to WiFi, reconnecting...");
}

void serial_debug_wifi_reestablished_connection(const IPAddress& ip) {
  Serial.println("");
  Serial.print("Re-established connection to WiFi with IP: ");
  Serial.println(ip);
}

void serial_debug_mqtt_connecting() {
  Serial.println("Connecting to MQTT broker " MQTT_SERVER " with client " MQTT_CLIENT);
}

void serial_debug_mqtt_lost_connection() {
  Serial.println("Lost connection to MQTT broker");
}

void serial_debug_mqtt_reestablished_connection() {
  Serial.println("Re-established connection to MQTT broker");
}

void serial_debug_mqtt_connection_success() {
  Serial.println("Connected to MQTT broker");
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