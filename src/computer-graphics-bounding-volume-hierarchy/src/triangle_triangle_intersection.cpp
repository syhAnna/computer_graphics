#include "triangle_triangle_intersection.h"
#include "Ray.h"
#include "ray_intersect_triangle.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // .norm() -> the sqr of the distance
  double min_t = 0;
  double rayA01_max_t = sqrt((A1 - A0).norm());
  double rayA02_max_t = sqrt((A2 - A0).norm());
  double rayA12_max_t = sqrt((A2 - A1).norm());

  double rayB01_max_t = sqrt((B1 - B0).norm());
  double rayB02_max_t = sqrt((B2 - B0).norm());
  double rayB12_max_t = sqrt((B2 - B0).norm());

  // define the ray object from each point
  // ray(origin, direction)
  Ray rayA01(A0, (A1 - A0));
  Ray rayA02(A0, (A2 - A0));
  Ray rayA12(A1, (A2 - A1));

  Ray rayB01(B0, (B1 - B0));
  Ray rayB02(B0, (B2 - B0));
  Ray rayB12(B1, (B2 - B1));

  double t;

  // check whether triangles intersects, i.e.: ray intersect
  // ray_intersect_triangle: check whether a ray intersect a triangle
  bool rayA01_hit_B = ray_intersect_triangle(rayA01, B0, B1, B2, min_t, rayA01_max_t, t);
  bool rayA02_hit_B = ray_intersect_triangle(rayA02, B0, B1, B2, min_t, rayA02_max_t, t);
  bool rayA12_hit_B = ray_intersect_triangle(rayA12, B0, B1, B2, min_t, rayA12_max_t, t);

  bool rayB01_hit_A = ray_intersect_triangle(rayB01, A0, A1, A2, min_t, rayB01_max_t, t);
  bool rayB02_hit_A = ray_intersect_triangle(rayB02, A0, A1, A2, min_t, rayB02_max_t, t);
  bool rayB12_hit_A = ray_intersect_triangle(rayB12, A0, A1, A2, min_t, rayB12_max_t, t);

  return rayA01_hit_B || rayA02_hit_B || rayA12_hit_B || rayB01_hit_A || rayB02_hit_A || rayB12_hit_A;
  ////////////////////////////////////////////////////////////////////////////
}
