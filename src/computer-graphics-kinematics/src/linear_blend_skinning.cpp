#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  U = Eigen::MatrixXd::Zero(V.rows(), 3);

  // each vertex in each bone is assigned a weight
  for (int vertex = 0; vertex < V.rows(); vertex++) {
      Eigen::RowVector3d v = V.row(vertex);
      for (int bone = 0; bone < skeleton.size(); bone++) {
          if (skeleton[bone].weight_index != -1) {
              U.row(vertex) += W(vertex, skeleton[bone].weight_index) *
                                (T[bone] * v.transpose()).transpose();
          }
      }
  }
  /////////////////////////////////////////////////////////////////////////////
}
