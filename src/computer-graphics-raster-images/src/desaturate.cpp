#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int i = 0; i < rgb.size(); i += 3) {
    double r = rgb[i] / 255.;
    double g = rgb[i + 1] / 255.;
    double b = rgb[i + 2] / 255.;

    double h;
    double s;
    double v;

    // understanding the difference between saturate and desaturate
    // https://helpx.adobe.com/photoshop-elements/key-concepts/saturation-desaturation.html
    rgb_to_hsv(r, g, b, h, s, v);
    s *= (1 - factor);
    hsv_to_rgb(h, s, v, r, g, b);

    desaturated[i] = r * 255.;
    desaturated[i + 1] = g * 255.;
    desaturated[i + 2] = b * 255.;
  }
  ////////////////////////////////////////////////////////////////////////////
}
