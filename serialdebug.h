#ifndef SERIALDEBUG_H
#define SERIALDEBUG_H

#include <Arduino.h>

#include "types.h"

void serial_debug_initiate(long baud);
void serial_debug_sensor_success(uint32_t sensorid);
void serial_debug_sensor_failure(uint32_t sensorid);
void serial_debug_sensor_data(const sensor_data& sensordata);

#endif
