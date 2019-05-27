#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int i = 0; i < height; i++) { // row
    for (int j = 0; j < width; j++) { // col
      int k = i * width + j;

      if (i % 2 == 1 && j % 2 == 0) { // red
        bayer[k] = rgb[0 + 3 * k];
      } else if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) { // green
        bayer[k] = rgb[1 + 3 * k];
      } else if (i % 2 == 0 && j % 2 == 1) { // blue
        bayer[k] = rgb[2 + 3 * k];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}