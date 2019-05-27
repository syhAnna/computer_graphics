#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // according to the function from the formula from the lecture slide
  double nominator = normal.dot((point - ray.origin));
  double denominator = normal.dot(ray.direction);

  if (denominator == 0) {
    // ray is parallel to the plane
    return false;
  }

  t = (double) nominator / denominator;

  if (t < min_t) {
    return false;
  } else {
    n = normal;
  }

  return true;
  ////////////////////////////////////////////////////////////////////////////
}