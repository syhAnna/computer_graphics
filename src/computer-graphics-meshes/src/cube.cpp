#include "cube.h"

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////

  //Hint:
   V.resize(8,3);
   F.resize(6,4);
   UV.resize(14,2);
   UF.resize(6,4);
   NV.resize(6,3);
   NF.resize(6,4);

   // consider the cube with bottom, left, front vertex as origin
   // construct according to assignment handout "3D Vertex Positions" image
   // Vertices data structure
   V(0, 0) = 0; V(0, 1) = 0; V(0, 2) = 0;    // (0, 0, 0)
   V(1, 0) = 0; V(1, 1) = 1; V(1, 2) = 0;    // (0, 1, 0)
   V(2, 0) = -1; V(2, 1) = 1; V(2, 2) = 0;   // (-1, 1, 0)
   V(3, 0) = -1; V(3, 1) = 0; V(3, 2) = 0;   // (-1, 0, 0)
   V(4, 0) = 0; V(4, 1) = 0; V(4, 2) = 1;    // (0, 0, 1)
   V(5, 0) = 0; V(5, 1) = 1; V(5, 2) = 1;    // (0, 1, 1)
   V(6, 0) = -1; V(6, 1) = 1; V(6, 2) = 1;   // (-1, 1, 1)
   V(7, 0) = -1; V(7, 1) = 0; V(7, 2) = 1;   // (-1, 0, 1)

   // Faces data structure
   // cube face color as assignment handout "3D Vertex Positions" image
   F(0, 0) = 0; F(0, 1) = 4; F(0, 2) = 7; F(0, 3) = 3; // red
   F(1, 0) = 1; F(1, 1) = 5; F(1, 2) = 4; F(1, 3) = 0; // green
   F(2, 0) = 2; F(2, 1) = 6; F(2, 2) = 5; F(2, 3) = 1; // blue
   F(3, 0) = 3; F(3, 1) = 7; F(3, 2) = 6; F(3, 3) = 2; // orange
   F(4, 0) = 5; F(4, 1) = 6; F(4, 2) = 7; F(4, 3) = 4; // yellow
   F(5, 0) = 2; F(5, 1) = 1; F(5, 2) = 0; F(5, 3) = 3; // white

   // UV 2D parametrization position data structure
   UV(0 ,0) = 1.; UV(0, 1) = 0.;
   UV(1 ,0) = 2.; UV(1, 1) = 0.;
   UV(2 ,0) = 0.; UV(2, 1) = 1.;
   UV(3 ,0) = 1.; UV(3, 1) = 1.;
   UV(4 ,0) = 2.; UV(4, 1) = 1.;
   UV(5 ,0) = 3.; UV(5, 1) = 1.;
   UV(6 ,0) = 4.; UV(6, 1) = 1.;
   UV(7 ,0) = 0.; UV(7, 1) = 2.;
   UV(8 ,0) = 1.; UV(8, 1) = 2.;
   UV(9 ,0) = 2.; UV(9, 1) = 2.;
   UV(10 ,0) = 3.; UV(10, 1) = 2.;
   UV(11 ,0) = 4.; UV(11, 1) = 2.;
   UV(12 ,0) = 1.; UV(12, 1) = 3.;
   UV(13 ,0) = 2.; UV(13, 1) = 3.;
   UV = UV / 4;

   // UF data structure
   UF(0, 0) = 3; UF(0, 1) = 8; UF(0, 2) = 7; UF(0, 3) = 2;    // red
   UF(1, 0) = 4; UF(1, 1) = 9; UF(1, 2) = 8; UF(1, 3) = 3;    // green
   UF(2, 0) = 5; UF(2, 1) = 10; UF(2, 2) = 9; UF(2, 3) = 4;   // blue
   UF(3, 0) = 6; UF(3, 1) = 11; UF(3, 2) = 10; UF(3, 3) = 5;  // orange
   UF(4, 0) = 9; UF(4, 1) = 13; UF(4, 2) = 12; UF(4, 3) = 8;  // yellow
   UF(5, 0) = 1; UF(5, 1) = 4; UF(5, 2) = 3; UF(5, 3) = 0;    // white

   // NV normal vector data structure
   // construct according to assignment handout "3D Normal Vectors" image
   NV(0, 0) = 0; NV(0, 1) = -1; NV(0, 2) = 0; // red
   NV(1, 0) = 1; NV(1, 1) = 0; NV(1, 2) = 0;  // green
   NV(2, 0) = 0; NV(2, 1) = 1; NV(2, 2) = 0;  // blue
   NV(3, 0) = -1; NV(3, 1) = 0; NV(3, 2) = 0; // orange
   NV(4, 0) = 0; NV(4, 1) = 0; NV(4, 2) = 1;  // yellow
   NV(5, 0) = 0; NV(5, 1) = 0; NV(5, 2) = -1; // white

   // NF locate normal data structure
   NF(0, 0) = 0; NF(0, 1) = 0; NF(0, 2) = 0; NF(0, 3) = 0;
   NF(1, 0) = 1; NF(1, 1) = 1; NF(1, 2) = 1; NF(1, 3) = 1;
   NF(2, 0) = 2; NF(2, 1) = 2; NF(2, 2) = 2; NF(2, 3) = 2;
   NF(3, 0) = 3; NF(3, 1) = 3; NF(3, 2) = 3; NF(3, 3) = 3;
   NF(4, 0) = 4; NF(4, 1) = 4; NF(4, 2) = 4; NF(4, 3) = 4;
   NF(5, 0) = 5; NF(5, 1) = 5; NF(5, 2) = 5; NF(5, 3) = 5;
}
