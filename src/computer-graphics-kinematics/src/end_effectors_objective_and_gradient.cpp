#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  f = [&](const Eigen::VectorXd & A)->double
  {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd transformed = transformed_tips(copy, b);
    return (transformed - xb0).squaredNorm();
  };
  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd transformed = transformed_tips(copy, b);

    Eigen::MatrixXd jacobian;
    kinematics_jacobian(copy, b, jacobian);

    Eigen::VectorXd gradient = Eigen::VectorXd::Zero(A.size());
    gradient = jacobian.transpose() * (2 * (transformed - xb0));
    return gradient;
  };
  proj_z = [&](Eigen::VectorXd & A)
  {
    assert(skeleton.size()*3 == A.size());
    for (int i = 0; i < skeleton.size(); i++) {
      A[i*3+0] = std::max(skeleton[i].xzx_min[0], std::min(skeleton[i].xzx_max[0], A[i*3+0]));
      A[i*3+1] = std::max(skeleton[i].xzx_min[1], std::min(skeleton[i].xzx_max[1], A[i*3+1]));
      A[i*3+2] = std::max(skeleton[i].xzx_min[2], std::min(skeleton[i].xzx_max[2], A[i*3+2]));
    }
  };
  /////////////////////////////////////////////////////////////////////////////
}
