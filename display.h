#ifndef DISPLAY_H
#define DISPLAY_H

#include "types.h"

/* Display definitions */
#define DISPLAY_CONTRAST 8

/* Pins for the DOGS102 Display */
#define PIN_DOG_SI    13
#define PIN_DOG_SCK   14
#define PIN_DOG_CS    15
#define PIN_DOG_A0    16
#define PIN_DOG_RST   17

void display_initiate();
void display_update(const sensor_data& sensordata);

#endif
