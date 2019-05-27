#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int dimension = 3;

  for (int i = 0; i < dimension; i++) { // for each dimension
      double dim_min = fmin(fmin(a[i], b[i]), c[i]);
      double dim_max = fmax(fmax(a[i], b[i]), c[i]);

      if (dim_min < B.min_corner[i]) {
          B.min_corner[i] = dim_min;
      }
      if (dim_max > B.max_corner[i]) {
          B.max_corner[i] = dim_max;
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}


