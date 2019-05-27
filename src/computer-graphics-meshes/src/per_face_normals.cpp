#include "per_face_normals.h"
#include "triangle_area_normal.h"
#include <Eigen/Geometry>

void per_face_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
  // store the unit normal vector of each face
  N = Eigen::MatrixXd::Zero(F.rows(),3);
  Eigen::RowVector3d normal;

  for (int i = 0; i < F.rows(); i++) {
    Eigen::RowVector3d v1 = V.row(F(i, 0));
    Eigen::RowVector3d v2 = V.row(F(i, 1));
    Eigen::RowVector3d v3 = V.row(F(i, 2));

    Eigen::RowVector3d v12 = v2 - v1;
    Eigen::RowVector3d v13 = v3 - v1;

    normal = v12.cross(v13).normalized();
    N.row(i) = normal;
  }
  ////////////////////////////////////////////////////////////////////////////
}
