#include "hsv_to_rgb.h"
#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  r = 0;
  g = 0;
  b = 0;

  // Converting algorithm from wikipedia:
  // https://en.wikipedia.org/wiki/HSL_and_HSV#From_HSV
  double chroma = v * s;
  double x = chroma * (1 - fabs(fmod(h / 60., 2) - 1));

  if (0 <= h && h < 60) {
    r = chroma;
    g = x;
    b = 0;
  } else if (60 <= h && h < 120) {
    r = x;
    g = chroma;
    b = 0;
  } else if (120 <= h && h < 180) {
    r = 0;
    g = chroma;
    b = x;
  } else if (180 <= h && h < 240) {
    r = 0;
    g = x;
    b = chroma;
  } else if (240 < h && h <= 300) {
    r = x;
    g = 0;
    b = chroma;
  } else if (300 < h && h <= 360) {
    r = chroma;
    g = 0;
    b = x;
  } else {
    r = 0;
    g = 0;
    b = 0;
  }

  double m = v - chroma;
  r = r + m;
  g = g + m;
  b = b + m;
  ////////////////////////////////////////////////////////////////////////////
}
