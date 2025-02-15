#include "reporting.h"
#include "format.h"
#include "secrets.h"

/* The MQTT client instance */
static PubSubClient* psclient;

/* Reporting global variables */
static const char* ftb;

void report_initiate(PubSubClient* psc) {
  psclient = psc;
}

void report_sensor_data(const sensor_data& sensordata) {
  ftb = format_value(sensordata.temperature);
  psclient->publish(REPORTING_TOPIC DEVICE_ID "/temperature", ftb);

  ftb = format_value(sensordata.pressure);
  psclient->publish(REPORTING_TOPIC DEVICE_ID "/pressure", ftb);

  ftb = format_value(sensordata.humidity);
  psclient->publish(REPORTING_TOPIC DEVICE_ID "/humidity", ftb);
}