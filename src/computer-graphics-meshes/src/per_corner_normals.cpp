#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>
#include "per_face_normals.h"
#include <cmath>
#include <math.h>
#include <Eigen/Geometry>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  // computing the area-weighted average of normals at incident faces
  // whose normals (face normal: FN) deviate less than the provided threshold.
  // in vertex_triangle_adjacency.h:
  // num_vertices  number of vertices (i.e., V.rows(); usually ==F.maxCoeff()+1)

  // Compute a vertex-triangle adjacency list
  std::vector<std::vector<int> > VF;
  vertex_triangle_adjacency(F, F.maxCoeff()+1, VF);

  // Compute per-face unit normal vectors
  Eigen::MatrixXd FN;
  per_face_normals(V, F, FN);

  int num_face = F.rows();
  int num_face_vertex = F.cols();

  // corner_threshold: threshold in degrees on sharp angles.
  // according to: http://www.cplusplus.com/reference/cmath/cos/
  // Value representing an angle expressed in radians.
  // One radian is equivalent to 180/PI degrees.
  double radian_threshold = corner_threshold * (M_PI / 180.);

  Eigen::RowVector3d face_normal;
  std::vector<int> face_adjacent;
  Eigen::RowVector3d curr_adjacent_face_normal;

  for (int face_index = 0; face_index < num_face; face_index++) {
      // compute the face normal of current face
      face_normal = FN.row(face_index).normalized();

      for (int face_vertex = 0; face_vertex < num_face_vertex; face_vertex++) {
          int curr_pos = face_index * num_face_vertex + face_vertex;

          // the adjacent faces of current vertex
          face_adjacent = VF[F(face_index, face_vertex)];

          // consider all adjacent faces whose normals deviate less than threshold.
          for (const auto &face : face_adjacent) {
             curr_adjacent_face_normal = FN.row(face).normalized();
             double cosine = face_normal.dot(curr_adjacent_face_normal);
             //double radian = acos(cosine) * (M_PI / 180.);

             // check normals deviate less than threshold.
             if (cosine >= radian_threshold) {
                 N.row(curr_pos) += curr_adjacent_face_normal;
             }
          }

          N.row(curr_pos).normalized();
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}
