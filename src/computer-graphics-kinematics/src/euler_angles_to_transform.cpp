#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::Affine3d A;
  Eigen::Matrix3d transform;
  transform = Eigen::AngleAxisd(xzx[2] / 180 * M_PI, Eigen::Vector3d::UnitX()) *
              Eigen::AngleAxisd(xzx[1] / 180 * M_PI, Eigen::Vector3d::UnitZ()) *
              Eigen::AngleAxisd(xzx[0] / 180 * M_PI, Eigen::Vector3d::UnitX());
  A.matrix() <<
    transform.row(0), 0,
    transform.row(1), 0,
    transform.row(2), 0,
    0, 0, 0, 1.0;
  return A;
  /////////////////////////////////////////////////////////////////////////////
}
