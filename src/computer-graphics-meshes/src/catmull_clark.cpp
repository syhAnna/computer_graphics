#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <Eigen/Geometry>
#include <string>
#include <vector>
#include <iostream>

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (num_iters == 0) {
      return;
  }

  SV.resize(0, 3);
  SF.resize(0, 4);

  // Consider the Catmull-Clark algorithm from the wikipedia
  // https://en.wikipedia.org/wiki/Catmull%E2%80%93Clark_subdivision_surface

  ///////////////////////////////////////////////////////////////////////
  // <key, value> = <vertex_index, [index of vertices adjacent to the key vertex]>
  std::unordered_map<int, std::vector<int>> vertex_adjacentVertex;
  for (int face = 0; face < F.rows(); face++) {
      for (int vertex = 0; vertex < F.cols(); vertex++) {
          vertex_adjacentVertex[F(face, vertex)].push_back(F(face, (vertex+1)%F.cols()));
      }
  }

  // <key, value> = <vertex_index, [index of the faces connected to that point]>
  std::unordered_map<int, std::vector<int>> vertex_adjacentFaces;
  for (int face = 0; face < F.rows(); face++) {
      for (int vertex = 0; vertex < F.cols(); vertex++) {
          vertex_adjacentFaces[F(face, vertex)].push_back(face);
      }
  }

  // the face which connects to the given edge
  // in 3D, each edge shared by 2 faces
  std::unordered_map<std::string, std::vector<int>> edge_sharedFace;
  for (int face = 0; face < F.rows(); face++) {
      for (int vertex = 0; vertex < F.cols(); vertex++) {
          // each face has the same orientation
          std::string edge_string1 = std::to_string(F(face, vertex))+"->"+std::to_string(F(face, (vertex+1)%F.cols()));
          std::string edge_string2 = std::to_string(F(face, (vertex+1)%F.cols()))+"->"+std::to_string(F(face, vertex));
          edge_sharedFace[edge_string1].push_back(face);
          edge_sharedFace[edge_string2].push_back(face);
      }
  }
  ///////////////////////////////////////////////////////////////////////

  // Step1:
  // For each face, add a face point
  //    Set each face point to be the average of all original points for the respective face.
  // face_point hashmap: (key, value) = (face_index[int], face_point[3dVector])
  std::unordered_map<int, Eigen::RowVector3d> face_points;
  for (int face = 0; face < F.rows(); face++) {
      Eigen::RowVector3d point(0, 0, 0);
      for (int vertex = 0; vertex < F.cols(); vertex++) {
          point += V.row(F(face, vertex));
      }
      face_points[face] = point/4.;
  }

  // Step2:
  // For each edge, add an edge point.
  //    Set each edge point to be the average of the two neighbouring face points
  //    and its two original endpoints.
  // Step3:
  // For each face point, add an edge for every edge of the face,
  // connecting the face point to each edge point for the face.
  const auto edgePoint = [&V, &F, &edge_sharedFace, &face_points](const int a, const int b) {
      Eigen::RowVector3d faceCenter(0, 0, 0);
      Eigen::RowVector3d edgeCenter = (V.row(a)+V.row(b))/2.;

      std::string key = std::to_string(a)+"->"+std::to_string(b);
      for (const int f : edge_sharedFace[key]) {
          faceCenter += face_points[f];
      }
      faceCenter /= 2.;
      return (faceCenter+edgeCenter)/2.;
  };

  // Step4:
  // For each original point P, take the average F of all n (recently created) face points
  // for faces touching P, and take the average R of all n edge midpoints
  // for (original) edges touching P, where each edge midpoint is the average of its two endpoint vertices
  // (not to be confused with new "edge points" above). Move each original point to the point
  // F+2R+(n-3)P \ n.
  // This is the barycenter of P, R and F with respective weights (n − 3), 2 and 1.
  const auto new_vertex = [&vertex_adjacentFaces, &face_points, &vertex_adjacentVertex, &V, &F](const int p) {
      Eigen::RowVector3d old_vertex = V.row(p);

      Eigen::RowVector3d F(0, 0, 0);
      for (const auto f : vertex_adjacentFaces[p]) {
          F += face_points[f];
      }
      F /= (double)vertex_adjacentFaces[p].size();

      Eigen::RowVector3d R(0, 0, 0);
      for (const auto neighbor : vertex_adjacentVertex[p]) {
          R += (V.row(p)+V.row(neighbor))/2.0;
      }
      R /= (double)vertex_adjacentVertex[p].size();

      double n = vertex_adjacentFaces[p].size();
      return (F + 2 * R + (n - 3) * old_vertex) / n;
  };

  // Step5:
  // Connect each new vertex point to the new edge points of all original edges
  // incident on the original vertex.
  // Add a new face into SV and SF.
  // i.e.: the helper function for the Step6 to add the new faces.
  const auto addNewFace = [&SV, &SF](const Eigen::RowVector3d p1, const Eigen::RowVector3d p2,
          const Eigen::RowVector3d p3, const Eigen::RowVector3d p4) {
      // the index of the 4 vertex of the face, the 4 3D points
      Eigen::RowVector4i idxs(-1, -1, -1, -1);
      Eigen::MatrixXd points(4, 3);
      points << p1, p2, p3, p4;
      for (int vertex = 0; vertex < points.rows(); vertex++) {
          for (int dim = 0; dim < SV.rows(); dim++) {
              if (points.row(vertex).isApprox(SV.row(dim))) {
                  idxs(vertex) = dim;
                  break;
              }
          }
          if (idxs(vertex) == -1) {
              SV.conservativeResize(SV.rows() + 1, SV.cols());
              SV.row(SV.rows() - 1) = points.row(vertex);
              idxs(vertex) = SV.rows() - 1;
          }
      }
      SF.conservativeResize(SF.rows() + 1, SF.cols());
      SF.row(SF.rows() - 1) = idxs;
  };

  // Step6:
  // Define new faces as enclosed by edges.
  // for each face, further divides it into four sub faces
  for (int face = 0; face < F.rows(); face++) {
      for (int vertex = 0; vertex < F.cols(); vertex++) {
          Eigen::RowVector3d p1 = new_vertex(F(face, vertex));
          Eigen::RowVector3d p2 = edgePoint(F(face, vertex), F(face, (vertex+1)%F.cols()));
          Eigen::RowVector3d p3 = face_points[face];
          Eigen::RowVector3d p4 = edgePoint(F(face, vertex), F(face, ((vertex-1)+F.cols())%F.cols()));
          addNewFace(p1, p2, p3, p4);
      }
  }

  catmull_clark(Eigen::MatrixXd(SV), Eigen::MatrixXi(SF), num_iters-1, SV, SF);
  ////////////////////////////////////////////////////////////////////////////
}
