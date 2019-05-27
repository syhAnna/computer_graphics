#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "per_face_normals.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  // algorithm according to: https://en.wikipedia.org/wiki/Vertex_normal
  Eigen::MatrixXd FN;
  per_face_normals(V, F, FN);

  for(int i = 0; i < F.rows(); i++){
      Eigen::RowVector3d v1 = V.row(F(i, 0));
      Eigen::RowVector3d v2 = V.row(F(i, 1));
      Eigen::RowVector3d v3 = V.row(F(i, 2));

      // vertex is on the face
      N.row(F(i, 0)) += FN.row(i) * (triangle_area_normal(v1, v2, v3).norm());
      N.row(F(i, 1)) += FN.row(i) * (triangle_area_normal(v1, v2, v3).norm());
      N.row(F(i, 2)) += FN.row(i) * (triangle_area_normal(v1, v2, v3).norm());
    }
  ////////////////////////////////////////////////////////////////////////////
}
