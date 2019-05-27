#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // reuse part of the code for A2.triangle.cpp
  Eigen::Vector3d Av = Eigen::Vector3d(A[0], A[1], A[2]);
  Eigen::Vector3d Bv = Eigen::Vector3d(B[0], B[1], B[2]);
  Eigen::Vector3d Cv = Eigen::Vector3d(C[0], C[1], C[2]);

  double Ax; double Ay; double Az;
  double Bx; double By; double Bz;
  double Cx; double Cy; double Cz;
  double Ex; double Ey; double Ez;

  Ax = Av(0, 0); Ay = Av(1, 0); Az = Av(2, 0);
  Bx = Bv(0, 0); By = Bv(1, 0); Bz = Bv(2, 0);
  Cx = Cv(0, 0); Cy = Cv(1, 0); Cz = Cv(2, 0);
  Ex = ray.origin(0, 0); Ey = ray.origin(1, 0); Ez = ray.origin(2, 0);

  double a; double b; double c;
  double d; double e; double f;
  double g; double h; double i;
  double j; double k; double l;

  a = Ax - Bx; b = Ay - By; c = Az - Bz;
  d = Ax - Cx; e = Ay - Cy; f = Az - Cz;
  g = ray.direction(0, 0); h = ray.direction(1, 0); i = ray.direction(2, 0);
  j = Ax - Ex; k = Ay - Ey; l = Az - Ez;

  double term1; double term2; double term3;
  double term4; double term5; double term6;

  term1 = e*i - h*f; term2 = g*f - d*i; term3 = d*h - e*g;
  term4 = a*k - j*b; term5 = j*c - a*l; term6 = b*l - k*c;

  double M; double beta; double gamma;

  M = a*term1 + b*term2 + c*term3;
  t = (-1) * (f*term4 + e*term5 + d*term6) / M;
  if (t < min_t || t > max_t) {
    return false;
  }
  gamma = (i*term4 + h*term5 + g*term6) / M;
  if (gamma < 0 or gamma > 1) {
    return false;
  }
  beta = (j*term1 + k*term2 + l*term3) / M;
  if (beta < 0 or beta > (1 - gamma)) {
    return false;
  }

  return true;
  ////////////////////////////////////////////////////////////////////////////
}

