#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int i = 0; i < rgb.size(); i += 3) {
    double r = rgb[i] / 255.;
    double g = rgb[i + 1] / 255.;
    double b = rgb[i + 2] / 255.;

    double h;
    double s;
    double v;

    // understand terminology: hue
    // https://en.wikipedia.org/wiki/Hue
    rgb_to_hsv(r, g, b, h, s, v);
    h += shift;
    if (h < 0) {
      h += 360;
    } else if (h >= 360) {
      h -= 360;
    }
    hsv_to_rgb(h, s, v, r, g, b);

    shifted[i] = r * 255.;
    shifted[i + 1] = g * 255.;
    shifted[i + 2] = b * 255.;
  }
  ////////////////////////////////////////////////////////////////////////////
}