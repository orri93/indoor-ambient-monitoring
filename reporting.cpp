#include "reporting.h"
#include "format.h"
#include "convert.h"
#include "secrets.h"

/* The MQTT client instance */
static PubSubClient* psclient;

/* Reporting global variables */
static const char* ftb;
static float v;

void report_initiate(PubSubClient* psc) {
  psclient = psc;
}

void report_sensor_data(const sensor_data& sensordata) {
  ftb = format_value(sensordata.temperature);
  psclient->publish(REPORTING_TOPIC DEVICE_ID "/temperature", ftb);

  v = patoinhg(sensordata.pressure);
  ftb = format_value(v);
  psclient->publish(REPORTING_TOPIC DEVICE_ID "/pressure", ftb);

  ftb = format_value(sensordata.humidity);
  psclient->publish(REPORTING_TOPIC DEVICE_ID "/humidity", ftb);
}