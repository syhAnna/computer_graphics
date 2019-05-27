#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // consider equation from book: Fundamentals of Computer Graphics; p79
  Eigen::Vector3d A = std::get<0>(corners);
  Eigen::Vector3d B = std::get<1>(corners);
  Eigen::Vector3d C = std::get<2>(corners);

  double Ax; double Ay; double Az;
  double Bx; double By; double Bz;
  double Cx; double Cy; double Cz;
  double Ex; double Ey; double Ez;

  Ax = A(0, 0); Ay = A(1, 0); Az = A(2, 0);
  Bx = B(0, 0); By = B(1, 0); Bz = B(2, 0);
  Cx = C(0, 0); Cy = C(1, 0); Cz = C(2, 0);
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
  if (t < min_t) {
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

  // compute the norm
  Eigen::Vector3d AB = B - A;
  Eigen::Vector3d AC = C - A;
  n = AB.cross(AC) / (AB.cross(AC).norm());

  return true;
  ////////////////////////////////////////////////////////////////////////////
}


