#include <Arduino.h>

#include "format.h"

#define NFB_SIZE 16
#define FB_SIZE  32

static char nfb[NFB_SIZE];
static char fb[FB_SIZE];

const char* format_value(float value) {
  dtostrf(value, 0, 1, nfb);
  sprintf(fb, "%s", nfb);
  return fb;
}

const char* format_temperature(float temperature) {
  dtostrf(temperature, 0, 1, nfb);
  sprintf(fb, "%s C", nfb);
  return fb;
}

const char* format_pressure(float pressure) {
  dtostrf(pressure, 0, 1, nfb);
  sprintf(fb, "%s inHg", nfb);
  return fb;
}

const char* format_humidity(float humidity) {
  dtostrf(humidity, 0, 1, nfb);
  sprintf(fb, "%s %%", nfb);
  return fb;
}
