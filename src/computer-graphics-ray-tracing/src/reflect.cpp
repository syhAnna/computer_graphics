#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // consider equation from: Fundamentals of Computer Graphics; p87, (4.5)
  Eigen::Vector3d out = (in - 2 * (in.dot(n)) * n).normalized();
  return out;
  ////////////////////////////////////////////////////////////////////////////
}
