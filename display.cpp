#include <Arduino.h>
#include <SPI.h>

/* Include header files for the DOGS102 Display library */
#include <dog_1701.h>

#include "display.h"
#include "constdef.h"
#include "convert.h"
#include "format.h"
#include "fonts.h"
#include "logo.h"

/* The DOG Display instance */
static dog_1701 dog;

/* Display global variables */
static char buffer[32];
static const char* ftb;
static float v;

void display_initiate() {
  /* Initalization of the DOG display instance */
  /* Parameter order is CS, SI, CLK, A0, RES */
  dog.initialize(PIN_DOG_CS, PIN_DOG_SI, PIN_DOG_SCK, PIN_DOG_A0, PIN_DOG_RST, DOGS102);
  dog.contrast(DISPLAY_CONTRAST);
}

void display_wifi_connecting() {
  dog.clear();
  dog.string(0, 0, font_6x8, "Connecting...");
}

void display_wifi_connection_success(const IPAddress& ip) {
  dog.clear();
  dog.string(0, 0, font_6x8, ip.toString().c_str());
}

void display_update(
  const int& wifi_status,
  const int& mqtt_status,
  const IPAddress& ip,
  const sensor_data& sensordata) {

  dog.clear();

  buffer[0] = 0x00;

  if (wifi_status == CONNECTION_STATUS_CONNECTED) {
    strcpy(buffer, ip.toString().c_str());
    if (mqtt_status == CONNECTION_STATUS_CONNECTED) {
      strcat(buffer, " Up");
    } else {
      strcat(buffer, " Down");
    }
  } else {
    strcpy(buffer, "Offline");
  }
  dog.string(0, 0, font_6x8, buffer);

  ftb = format_temperature(sensordata.temperature);
  dog.string(0, 2, font_8x16, ftb);

  v = patoinhg(sensordata.pressure);
  ftb = format_pressure(v);
  dog.string(0, 4, font_8x16, ftb);

  ftb = format_humidity(sensordata.humidity);
  dog.string(0, 6, font_8x16, ftb);
}
