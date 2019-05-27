#include "projected_gradient_descent.h"
#include "line_search.h"

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Add your code here
  double sigma;
  int max_step = 1000;

  for (int i = 0; i < max_iters; i++) {
      Eigen::VectorXd dz = grad_f(z);
      if (dz.norm() == 0){
          return;
      }

      sigma = line_search(f, proj_z, z, dz, max_step);
      z -= sigma * dz;
      proj_z(z);
  }
  /////////////////////////////////////////////////////////////////////////////
}
