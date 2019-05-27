#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int count = 0;  // used to count number of pixel seen
  for (int i = 1; i <= height*width*4; i++) {
    if (i % 4 == 0) {
      count++;
    } else {
      rgb[i - count - 1] = rgba[i - 1];
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
