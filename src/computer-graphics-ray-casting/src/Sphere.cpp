#include "Sphere.h"
#include "Ray.h"
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d c = center;
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e = ray.origin;

  // consider equation from book: Fundamentals of Computer Graphics; p77
  double A = d.dot(d);
  double B = 2 * d.dot(e - c);
  double C = (e - c).dot((e - c)) - radius * radius;

  double discriminant = B * B - 4 * A * C;

  if (discriminant < 0) {
    // ray and sphere do not intersect
    return false;
  } else if (discriminant == 0) {
    // ray grazes the sphere, touching it at exactly one point
    t = ((-1) * B + sqrt(discriminant)) / (2 * A);

    if (t < min_t) {
      return false;
    }
  } else {
    // discriminant > 0, 2 solutions.
    // one where the ray enters the sphere, one where it leaves
    double sol1 = ((-1) * B + sqrt(discriminant)) / (2 * A);
    double sol2 = ((-1) * B - sqrt(discriminant)) / (2 * A);

    double minSol = (sol1 < sol2) ? sol1 : sol2;
    double maxSol = (sol1 > sol2) ? sol1 : sol2;

    if (min_t > maxSol) {
        return false;
    } else if (min_t > minSol) {
        t = maxSol;
    } else { // min_t <= minSol
        t = minSol;
    }
  }

  Eigen::Vector3d hit = d * t + e;
  n = (hit - c) / radius;

  return true;
  ////////////////////////////////////////////////////////////////////////////
}

