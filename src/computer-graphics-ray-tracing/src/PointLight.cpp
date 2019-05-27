#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  // p: direction to light; q: point in space
  // consider: q -> p
  max_t = (p - q).norm();
  d = (p - q) / max_t;
  ////////////////////////////////////////////////////////////////////////////
}
