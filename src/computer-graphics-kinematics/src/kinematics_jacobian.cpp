#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  J = Eigen::MatrixXd::Zero(b.size()*3,skeleton.size()*3);
  Eigen::VectorXd trans = transformed_tips(skeleton, b);
  Skeleton skeleton_cpy = skeleton;

  double sigma = 1e-7;
  for (int i = 0; i < skeleton.size(); i++) {
    skeleton_cpy[i].xzx[0] += sigma;
    J.col(3*i+0) = (transformed_tips(skeleton_cpy, b) - trans) / sigma;
    skeleton_cpy[i].xzx[0] -= sigma;

    skeleton_cpy[i].xzx[1] += sigma;
    J.col(3*i+1) = (transformed_tips(skeleton_cpy, b) - trans) / sigma;
    skeleton_cpy[i].xzx[1] -= sigma;

    skeleton_cpy[i].xzx[2] += sigma;
    J.col(3*i+2) = (transformed_tips(skeleton_cpy, b) - trans) / sigma;
    skeleton_cpy[i].xzx[2] -= sigma;
  }
  /////////////////////////////////////////////////////////////////////////////
}
