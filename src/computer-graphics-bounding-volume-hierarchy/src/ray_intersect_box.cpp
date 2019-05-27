#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Consider equation from book: Fundamentals of Computer Graphics; p302
  double x_min, x_max;
  double y_min, y_max;
  double z_min, z_max;
  double x_e, y_e, z_e;
  double x_d, y_d, z_d;
  double a_x, a_y, a_z;
  double tx_min, tx_max;
  double ty_min, ty_max;
  double tz_min, tz_max;

  x_min = box.min_corner[0]; x_max = box.max_corner[0];
  y_min = box.min_corner[1]; y_max = box.max_corner[1];
  z_min = box.min_corner[2]; z_max = box.max_corner[2];
  x_e = ray.origin[0]; y_e = ray.origin[1]; z_e = ray.origin[2];
  x_d = ray.direction[0]; y_d = ray.direction[1]; z_d = ray.direction[2];

  a_x = 1 / x_d; a_y = 1 / y_d; a_z = 1 / z_d;

  // check x direction
  if (a_x >= 0) {
    tx_min = a_x * (x_min - x_e);
    tx_max = a_x * (x_max - x_e);
  } else {
    tx_min = a_x * (x_max - x_e);
    tx_max = a_x * (x_min - x_e);
  }

  // check y direction
  if (a_y >= 0) {
    ty_min = a_y * (y_min - y_e);
    ty_max = a_y * (y_max - y_e);
  } else {
    ty_min = a_y * (y_max - y_e);
    ty_max = a_y * (y_min - y_e);
  }

  // check z direction
  if (a_z >= 0) {
    tz_min = a_z * (z_min - z_e);
    tz_max = a_z * (z_max - z_e);
  } else {
    tz_min = a_z * (z_max - z_e);
    tz_max = a_z * (z_min - z_e);
  }

  double inf_min = -std::numeric_limits<double> :: infinity();
  double inf_max = std::numeric_limits<double> :: infinity();

  double minimax = fmin(fmin(fmin(tx_max, ty_max), tz_max), inf_max);
  double maximin = fmax(fmax(fmax(tx_min, ty_min), tz_min), inf_min);

  minimax = (minimax > max_t) ? max_t : minimax;
  maximin = (maximin < min_t) ? min_t : maximin;

  if (maximin <= minimax && maximin != inf_max) {
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
