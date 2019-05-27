#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // image center directly in front of 'eye' point
  // image pixel's index (i, j) stored as matrix:
  // ------------------------->
  // | (0, 0), (0, 1), (0, 2)
  // | (1, 0), (1, 1), (1, 2)
  // | (2, 0), (2, 1), (2, 2)
  // | (3, 0), (3, 1), (3, 2)
  // V

  double u = camera.width * j / width - camera.width / 2.;
  double v = (camera.height / 2.) - camera.height * i / height;

  ray.origin = camera.e;
  ray.direction = u * camera.u + v * camera.v + (-1) * camera.d * camera.w;
  // wired! normalization influence inside-a-sphere
  // ray.direction /= ray.direction.norm();
  ////////////////////////////////////////////////////////////////////////////
}