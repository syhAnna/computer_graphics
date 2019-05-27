#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  std::ofstream output(filename, std::ios::binary);
  if (!output){
    return false;
  }

  // specifies the different header according to:
  // http://netpbm.sourceforge.net/doc/ppm.html
  if (num_channels == 1) {
    output << "P5" << "\n";
  } else {
    output << "P6" << "\n";
  }

  output << width << " " << height << "\n";
  output << 255 << "\n";
  for (int i = 0; i < width * height * num_channels; i++){
    output << data[i];
  }

  return true;
  ////////////////////////////////////////////////////////////////////////////
}
