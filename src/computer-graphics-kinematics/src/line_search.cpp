#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  double curr_step = max_step;
  Eigen::VectorXd curr_z = z - curr_step * dz;
  proj_z(curr_z);

  while (f(curr_z) > f(z)) {
    curr_step *= 0.5;
    curr_z = z - curr_step * dz;
    proj_z(curr_z);

    if (curr_z == z) {
      return 0.;
    }
  }

  return curr_step;
  /////////////////////////////////////////////////////////////////////////////
}
