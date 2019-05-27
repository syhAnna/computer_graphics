#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  // consider the algorithm from the online source:
  // https://stackoverflow.com/questions/5254838/calculating-distance-between-a-point-and-a-rectangular-box-nearest-point
  double p_x; double p_y; double p_z;
  double d_x; double d_y; double d_z;
  double sqr_distance;

  p_x = query(0); p_y = query(1); p_z = query(2);

  d_x = fmax(fmax(box.min_corner[0] - p_x, 0), p_x - box.max_corner[0]);
  d_y = fmax(fmax(box.min_corner[1] - p_y, 0), p_y - box.max_corner[1]);
  d_z = fmax(fmax(box.min_corner[2] - p_z, 0), p_z - box.max_corner[2]);

  sqr_distance = d_x * d_x + d_y * d_y + d_z * d_z;
  return sqr_distance;
  ////////////////////////////////////////////////////////////////////////////
}
