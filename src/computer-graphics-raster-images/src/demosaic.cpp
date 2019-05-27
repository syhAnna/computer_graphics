#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // g b g b g b
  // r g r g r g
  // g b g b g b
  // r g r g r g

  for (int i = 0; i < height; i++) { // row
    for (int j = 0; j < width; j++) { // col
      int curPixel = i * width + j;
      int left = i * width + (j - 1);
      int right = i * width + (j + 1);
      int top = (i - 1) * width + j;
      int bottom = (i + 1) * width + j;
      int topLeft = (i - 1) * width + (j - 1);
      int topRight = (i - 1) * width + (j + 1);
      int bottomLeft = (i + 1) * width + (j - 1);
      int bottomRight = (i + 1) * width + (j + 1);

      // corner
      if (i == 0 && j == 0) { // topLeft corner
        // [g] b
        //  r
        rgb[curPixel*3 + 0] = bayer[bottom];
        rgb[curPixel*3 + 1] = bayer[curPixel];
        rgb[curPixel*3 + 2] = bayer[right];

      } else if (i == 0 && j == (width - 1)) { // topRight corner
        if (width % 2 == 0) {
          // g [b]
          // r  g
          rgb[curPixel*3 + 0] = bayer[bottomLeft];
          rgb[curPixel*3 + 1] = (bayer[left] + bayer[bottom]) / 2.;
          rgb[curPixel*3 + 2] = bayer[curPixel];
        } else {
          // b [g]
          //    r
          rgb[curPixel*3 + 0] = bayer[bottom];
          rgb[curPixel*3 + 1] = bayer[curPixel];
          rgb[curPixel*3 + 2] = bayer[left];
        }

      } else if (i == (height - 1) && j == 0) { // bottomLeft corner
        if (height % 2 == 0) {
          //  g  b
          // [r] g
          rgb[curPixel*3 + 0] = bayer[curPixel];
          rgb[curPixel*3 + 1] = (bayer[right] + bayer[top]) / 2.;
          rgb[curPixel*3 + 2] = bayer[topRight];
        } else {
          //  r
          // [g] b
          rgb[curPixel*3 + 0] = bayer[top];
          rgb[curPixel*3 + 1] = bayer[curPixel];
          rgb[curPixel*3 + 2] = bayer[right];
        }

      } else if (i == (height - 1) && j == (width - 1)) { // bottomRight corner
        if (width % 2 == 0 && height % 2 == 0) {
          //    b
          // r [g]
          rgb[curPixel*3 + 0] = bayer[left];
          rgb[curPixel*3 + 1] = bayer[curPixel];
          rgb[curPixel*3 + 2] = bayer[top];
        } else if (width % 2 == 0 && height % 2 == 1) {
          // r  g
          // g [b]
          rgb[curPixel*3 + 0] = bayer[topLeft];
          rgb[curPixel*3 + 1] = (bayer[left] + bayer[top]) / 2.;
          rgb[curPixel*3 + 2] = bayer[curPixel];
        } else if (width % 2 == 1 && height % 2 == 0) {
          // b  g
          // b [r]
          rgb[curPixel*3 + 0] = bayer[curPixel];
          rgb[curPixel*3 + 1] = (bayer[left] + bayer[top]) / 2.;
          rgb[curPixel*3 + 2] = bayer[topLeft];
        } else {
          //    r
          // b [g]
          rgb[curPixel*3 + 0] = bayer[top];
          rgb[curPixel*3 + 1] = bayer[curPixel];
          rgb[curPixel*3 + 2] = bayer[left];
        }
      }

      // edge
      if (i == 0) { // first row
        if (j % 2 == 0 && j > 0 && j < (width - 1)) {
          // g b [g] b
          rgb[curPixel*3 + 0] = bayer[bottom];
          rgb[curPixel*3 + 1] = bayer[curPixel];
          rgb[curPixel*3 + 2] = (bayer[left] + bayer[right]) / 2.;
        } else if (j % 2 == 1 && j > 0 && j < (width - 1)) {
          // g [b] g b
          rgb[curPixel*3 + 0] = (bayer[bottomLeft] + bayer[bottomRight]) / 2.0;
          rgb[curPixel*3 + 1] = (bayer[left] + bayer[right] + bayer[bottom]) / 3.;
          rgb[curPixel*3 + 2] = bayer[curPixel];
        }

      } else if (j == 0) { // first col
        if (i % 2 == 0 && i > 0 && i < (height - 1)) {
          //  g
          //  r
          // [g]
          //  r
          rgb[curPixel*3 + 0] = (bayer[top] + bayer[bottom]) / 2.;
          rgb[curPixel*3 + 1] = bayer[curPixel];
          rgb[curPixel*3 + 2] = bayer[right];
        } else if (i % 2 == 1 && i > 0 && i < (height - 1)) {
          //  g
          // [r]
          //  g
          //  r
          rgb[curPixel*3 + 0] = bayer[curPixel];
          rgb[curPixel*3 + 1] = (bayer[top] + bayer[bottom] + bayer[right]) / 3.;
          rgb[curPixel*3 + 2] = (bayer[topRight] + bayer[bottomRight]) / 2.;
        }

      } else if (i == (height - 1)) { // last row
        if (height % 2 == 0) {
          if (j > 0 && j < (width - 1)) {
            if (j % 2 == 0) {
              // r g [r] g
              rgb[curPixel*3 + 0] = bayer[curPixel];
              rgb[curPixel*3 + 1] = (bayer[top] + bayer[left] + bayer[right]) / 3.;
              rgb[curPixel*3 + 2] = (bayer[topLeft] + bayer[topRight]) / 2.;
            } else {
              // r [g] r g
              rgb[curPixel*3 + 0] = (bayer[left] + bayer[right]) / 2.;
              rgb[curPixel*3 + 1] = bayer[curPixel];
              rgb[curPixel*3 + 2] = bayer[top];
            }
          }

        } else {
          if (j > 0 && j < (width - 1)) {
            if (j % 2 == 0) {
              // g b [g] b
              rgb[curPixel*3 + 0] = bayer[top];
              rgb[curPixel*3 + 1] = bayer[curPixel];
              rgb[curPixel*3 + 2] = (bayer[left] + bayer[right]) / 2.;
            } else {
              // g [b] g b
              rgb[curPixel*3 + 0] = (bayer[topLeft] + bayer[topRight]) / 2.;
              rgb[curPixel*3 + 1] = (bayer[top] + bayer[left] + bayer[right]) / 3.;
              rgb[curPixel*3 + 2] = bayer[curPixel];
            }
          }
        }

      } else if (j == (width - 1)) { // last col
        if (width % 2 == 0) {
          if (i > 0 && i < (height - 1)) {
            if (i % 2 == 0) {
              //  b
              //  g
              // [b]
              //  g
              rgb[curPixel*3 + 0] = (bayer[topLeft] + bayer[bottomLeft]) / 2.;
              rgb[curPixel*3 + 1] = (bayer[top] + bayer[bottom] + bayer[left]) / 3.;
              rgb[curPixel*3 + 2] = bayer[curPixel];
            } else {
              //  b
              // [g]
              //  b
              //  g
              rgb[curPixel*3 + 0] = bayer[left];
              rgb[curPixel*3 + 1] = bayer[curPixel];
              rgb[curPixel*3 + 2] = (bayer[top] + bayer[bottom]) / 2.;
            }
          }

        } else {
          if (i > 0 && i < (height - 1)) {
            if (i % 2 == 0) {
              //  g
              //  r
              // [g]
              //  r
              rgb[curPixel*3 + 0] = (bayer[top] + bayer[bottom]) / 2.;
              rgb[curPixel*3 + 1] = bayer[curPixel];
              rgb[curPixel*3 + 2] = bayer[left];
            } else {
              //  g
              // [r]
              //  g
              //  r
              rgb[curPixel*3 + 0] = bayer[curPixel];
              rgb[curPixel*3 + 1] = (bayer[top] + bayer[bottom] + bayer[left]) / 3.;
              rgb[curPixel*3 + 2] = (bayer[topLeft] + bayer[bottomLeft]) / 2.;
            }
          }
        }
      }

      // center
      if ((i > 0 && i < (height - 1)) && (j > 0 && j < (width - 1))) {
        if (i % 2 == 0 && j % 2 == 0) {
          // g  r  g
          // b [g] b
          // g  r  g
          rgb[curPixel*3 + 0] = (bayer[top] + bayer[bottom]) / 2.0;
          rgb[curPixel*3 + 1] = bayer[curPixel];
          rgb[curPixel*3 + 2] = (bayer[left] + bayer[right]) / 2.0;

        } else if (i % 2 == 0 && j % 2 == 1) {
          // r  g  r
          // g [b] g
          // r  g  r
          rgb[curPixel*3 + 0] = (bayer[topLeft] + bayer[topRight] + bayer[bottomLeft] + bayer[bottomRight]) / 4.0;
          rgb[curPixel*3 + 1] = (bayer[top] + bayer[bottom] + bayer[left] + bayer[right]) / 4.0;
          rgb[curPixel*3 + 2] = bayer[curPixel];

        } else if (i % 2 == 1 && j % 2 == 0) {
          // b  g  b
          // g [r] g
          // b  g  b
          rgb[curPixel*3 + 0] = bayer[curPixel];
          rgb[curPixel*3 + 1] = (bayer[top] + bayer[bottom] + bayer[left] + bayer[right]) / 4.0;
          rgb[curPixel*3 + 2] = (bayer[topLeft] + bayer[topRight] + bayer[bottomLeft] + bayer[bottomRight]) / 4.0;

        } else {
          // g  b  g
          // r [g] r
          // g  b  g
          rgb[curPixel*3 + 0] = (bayer[left] + bayer[right]) / 2.0;
          rgb[curPixel*3 + 1] = bayer[curPixel];
          rgb[curPixel*3 + 2] = (bayer[top] + bayer[bottom]) / 2.0;
        }
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
