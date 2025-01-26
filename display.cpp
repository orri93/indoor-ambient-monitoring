#include <Arduino.h>
#include <SPI.h>

/* Include header files for the DOGS102 Display library */
#include <dog_1701.h>

#include "display.h"
#include "convert.h"
#include "format.h"
#include "fonts.h"
#include "logo.h"

/* The DOG Display instance */
static dog_1701 dog;

/* Display global variables */
static const char* ftb;
static float v;

void display_initiate() {
  /* Initalization of the DOG display instance */
  /* Parameter order is CS, SI, CLK, A0, RES */
  dog.initialize(PIN_DOG_CS, PIN_DOG_SI, PIN_DOG_SCK, PIN_DOG_A0, PIN_DOG_RST, DOGS102);
  dog.contrast(DISPLAY_CONTRAST);
  dog.clear();
  //dog.picture(0, 0, logo_sun);
  dog.string(0, 0, font_8x16, "Connecting to WiFi");
}

void display_update(const sensor_data& sensordata) {
  ftb = format_temperature(sensordata.temperature);
  dog.string(0, 2, font_8x16, ftb);

  v = patoinhg(sensordata.pressure);
  ftb = format_pressure(v);
  dog.string(0, 4, font_8x16, ftb);

  ftb = format_humidity(sensordata.humidity);
  dog.string(0, 6, font_8x16, ftb);
}
