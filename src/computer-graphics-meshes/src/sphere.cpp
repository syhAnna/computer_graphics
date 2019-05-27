#include "sphere.h"
#include <iostream>
#include <math.h>
#include <Eigen/Geometry>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  double PI = M_PI;
  double radius = 1.;
  double u_theta = (2 * PI * radius) / num_faces_u;     // longitude, a full circle, west -> east -> west
  double v_theta = PI * radius / num_faces_v;           // latitude, a half circle, south -> north

  //Hint: from cube.cpp
  V.resize((num_faces_u + 1) * (num_faces_v + 1), 3);                   // # vertices in 3D
  F.resize(num_faces_u * num_faces_v, 4);                               // # faces in 3D
  UV = Eigen::MatrixXd::Zero((num_faces_u + 1) * (num_faces_v + 1), 2); // # vertices in "flatten" 2D
  UF = Eigen::MatrixXi::Zero(num_faces_u * num_faces_v, 4);             // # faces in "flatten" 2D
  NV = Eigen::MatrixXd::Zero(num_faces_u * num_faces_v, 3);             // # normal directions for each face in 3D
  NF = Eigen::MatrixXi::Zero(num_faces_u * num_faces_v, 4);             // # faces in 3D

  // polar coordinate to represent the sphere
  // V data structure
  for (int latitude = 0; latitude < num_faces_v + 1; latitude++) {          // south -> north direction
      for (int longitude = 0; longitude < num_faces_u + 1; longitude++) {   // west -> east -> west direction
          double curr_v_theta = v_theta * latitude;
          double curr_u_theta = u_theta * longitude;
          int curr_pos = latitude * (num_faces_u + 1) + longitude;

          // consider the center of the sphere as the origin
          if (latitude == 0) { // at the North pole, iterates on all the parts west -> east -> west
              // Each parts west -> east -> west, considered to be the North point on the earth
              V(curr_pos, 0) = 0; V(curr_pos, 1) = 0; V(curr_pos, 2) = 1;
          } else if (latitude == num_faces_v) { // at the South pole
              // Each parts west -> east -> west, considered to be the South point on the earth
              V(curr_pos, 0) = 0; V(curr_pos, 1) = 0; V(curr_pos, 2) = -1;
          } else {
              V(curr_pos, 0) = radius * sin(curr_v_theta) * cos(curr_u_theta);
              V(curr_pos, 1) = radius * sin(curr_v_theta) * sin(curr_u_theta);
              V(curr_pos, 2) = radius * cos(curr_v_theta);
          }
      }
  }

  // F data structure
  for (int latitude = 0; latitude < num_faces_v; latitude++) {
      for (int longitude = 0; longitude < num_faces_u; longitude++) {
          int curr_pos = latitude * (num_faces_u + 1) + longitude;
          int curr_face = curr_pos - latitude;

          F(curr_face, 0) = curr_pos;
          F(curr_face, 1) = curr_pos + num_faces_u + 1;
          F(curr_face, 2) = curr_pos + num_faces_u + 2;
          F(curr_face, 3) = curr_pos + 1;
      }
  }

  // UV data structure
  for (int latitude = 0; latitude < num_faces_v + 1; latitude++) {
      for (int longitude = 0; longitude < num_faces_u + 1; longitude++) {
          int curr_pos = latitude * (num_faces_u + 1) + longitude;
          double x_2D = longitude * 1.; double y_2D = latitude * 1.;

          UV(curr_pos, 0) = x_2D / (num_faces_u + 1);
          UV(curr_pos, 1) = y_2D / (num_faces_v + 1);
      }
  }

  // UF data structure, after "flatten" is 2D rectangle
  // NV, NF data structure, note radius = 1.
  UF = F; NV = V; NF = F;
  ////////////////////////////////////////////////////////////////////////////
}
