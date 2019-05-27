#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > T;
  Eigen::VectorXd transform_tips = Eigen::VectorXd::Zero(3 * b.size());
  forward_kinematics(skeleton, T);

  for (int i = 0; i < b.size(); i++) {
      int curr = b[i];
      Eigen::VectorXd v = T[curr] * skeleton[curr].rest_T *
                          Eigen::Vector4d(skeleton[curr].length, 0, 0, 1);
      transform_tips[3 * i + 0] = v[0];
      transform_tips[3 * i + 1] = v[1];
      transform_tips[3 * i + 2] = v[2];
  }
  return transform_tips;
  /////////////////////////////////////////////////////////////////////////////
}
