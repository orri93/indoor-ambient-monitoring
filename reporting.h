#ifndef REPORTING_H
#define REPORTING_H

#define REPORTING_TOPIC "iam/"

#include <PubSubClient.h>

#include "types.h"

void report_initiate(PubSubClient* psc);

void report_sensor_data(const sensor_data& sensordata);

#endif /* REPORTING_H */
