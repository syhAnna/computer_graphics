#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int i = 0; i < height*width; i++) {
    int r = 0 + i * 3;
    int g = 1 + i * 3;
    int b = 2 + i * 3;

    // The parameters needed to covert from rgb to grayscale image from wikipedia:
    // https://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale
    gray[i] = 0.2126 * rgb[r] + 0.7152 * rgb[g] + 0.0722 * rgb[b];
  }
  ////////////////////////////////////////////////////////////////////////////
}


