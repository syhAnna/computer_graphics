#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // light far away from the object, consider as the parallel light
  max_t = std::numeric_limits<double>::infinity();
  d = -this->d.normalized();
  ////////////////////////////////////////////////////////////////////////////
}

