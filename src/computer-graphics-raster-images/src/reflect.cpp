#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      for (int k = 0; k < num_channels; k++) {
        reflected[k + 3 * (width * i + j - 1)] = input[k + 3 * ((width - j - 1) + width * i)];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
