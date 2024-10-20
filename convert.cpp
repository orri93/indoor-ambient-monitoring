#include "convert.h"

// Temperature
float ctof(float c) {
  // Celsius to Fahrenheit
  return c * 9.0F / 5.0F + 32.0F;
}

// Pressure
float patohpa(float pa) {
  // Pa to hPa
  return pa / 100.0F;
}
float patoatm(float pa) {
  // Pa to atm
  return pa / 101325.0F;
}
float patombar(float pa) {
  // Pa to mbar
  return pa / 100.0F;
}
float patopsi(float pa) {
  // Pa to psi
  return pa / 6894.757F;
}
float patoinhg(float pa) {
  // Pa to inHg
  return pa / 3386.389F;
}
float patommhg(float pa) {
  // Pa to mmHg
  return pa / 133.3224F;
}
