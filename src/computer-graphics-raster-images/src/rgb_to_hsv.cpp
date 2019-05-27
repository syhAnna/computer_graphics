#include "rgb_to_hsv.h"
#include <cmath>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  h = 0;
  s = 0;
  v = 0;

  // Converting algorithm from wikipedia:
  // https://en.wikipedia.org/wiki/HSL_and_HSV#Conversion_RGB_to_HSL/HSV_used_commonly_in_software_programming
  double max = fmax(fmax(r, g), b);
  double min = fmin(fmin(r, g), b);

  if (max == min) {
    h = 0;
  } else if (max == r) {
    h = 60 * (0 + (g - b) / (max - min));
  } else if (max == g) {
    h = 60 * (2 + (b - r) / (max - min));
  } else if (max == b) {
    h = 60 * (4 + (r - g) / (max - min));
  }

  if (h < 0) {
    h = h + 360;
  }

  s = (max == 0) ? 0 : (max - min) / max;
  v = max;
  ////////////////////////////////////////////////////////////////////////////
}
