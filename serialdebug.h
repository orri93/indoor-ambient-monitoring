#ifndef SERIALDEBUG_H
#define SERIALDEBUG_H

#include <Arduino.h>

#include "types.h"

void serial_debug_initiate(long baud);
void serial_debug_wifi_connecting();
void serial_debug_wifi_connection_success(const IPAddress& ip);
void serial_debug_wifi_lost_connection();
void serial_debug_wifi_reestablished_connection(const IPAddress& ip);
void serial_debug_mqtt_connecting();
void serial_debug_mqtt_connection_success();
void serial_debug_mqtt_lost_connection();
void serial_debug_mqtt_reestablished_connection();
void serial_debug_sensor_success(uint32_t sensorid);
void serial_debug_sensor_failure(uint32_t sensorid);
void serial_debug_sensor_data(const sensor_data& sensordata);

#endif
