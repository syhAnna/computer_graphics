#include "point_triangle_squared_distance.h"
#include "Ray.h"
#include "Eigen/Geometry"

double point_triangle_squared_distance(
  const Eigen::RowVector3d & query,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  Eigen::RowVector3d & bary)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  // Consider algorithm from book: Fundamentals of Computer Graphics; p45-49
  // about Barycentric Coordinates
  // Also consider the algorithm from the paper: "Barycentric Coordinates"
  // link to paper: https://pdfs.semanticscholar.org/d7be/b4eabd3ea7108ff41135d87984a34c29ce7c.pdf
  Eigen::Vector3d Av = Eigen::Vector3d(A[0], A[1], A[2]);
  Eigen::Vector3d Bv = Eigen::Vector3d(B[0], B[1], B[2]);
  Eigen::Vector3d Cv = Eigen::Vector3d(C[0], C[1], C[2]);
  Eigen::Vector3d QUERYv = Eigen::Vector3d(query[0], query[1], query[2]);
  Eigen::Vector3d normal = ((Bv - Av).cross(Cv - Av)).normalized();

  // the ray in the direction of normal of plane
  Ray ray(query, normal);
  double height = ray.direction.dot(normal);
  double projectLength = fabs((Av - ray.origin).dot(normal) / height);

  Eigen::Vector3d P = ray.origin + projectLength * ray.direction;
  Eigen::Vector3d PtoA = Av - P;
  Eigen::Vector3d PtoB = Bv - P;
  Eigen::Vector3d PtoC = Cv - P;

  double areaAB; double areaAC; double areaBC; double areaABC;
  double alpha; double beta; double gamma;
  areaAB = (1/2.) * (PtoA.cross(PtoB).norm());
  areaAC = (1/2.) * (PtoA.cross(PtoC).norm());
  areaBC = (1/2.) * (PtoB.cross(PtoC).norm());
  areaABC = (1/2.) * ((Bv - Av).cross(Cv - Av).norm());

  alpha = fabs(areaBC / areaABC);
  beta = fabs(areaAC / areaABC);
  gamma = 1 - alpha - gamma;
  bary(0) = alpha; bary(1) = beta; bary(2) = gamma;

  // check the position of P in plane of triangle: 7 cases
  if ((alpha >= 0) && (beta >= 0) && (gamma >= 0)) {
    // case1: inside/on the triangle
    return pow(projectLength, 2);

  } else if ((alpha > 0) && (beta < 0) && (gamma < 0)) {
    // case2: outside triangle, around point A
    // update P to A
    Eigen::Vector3d AtoA = Av - Av;
    Eigen::Vector3d AtoB = Bv - Av;
    Eigen::Vector3d AtoC = Cv - Av;

    areaAB = (1/2.) * (AtoA.cross(AtoB).norm());
    areaAC = (1/2.) * (AtoA.cross(AtoC).norm());
    areaBC = (1/2.) * (AtoB.cross(AtoC).norm());

    alpha = fabs(areaBC / areaABC);
    beta = fabs(areaAC / areaABC);
    gamma = 1 - alpha - gamma;
    bary(0) = alpha; bary(1) = beta; bary(2) = gamma;

    return pow((QUERYv - Av).norm(), 2);

  } else if ((alpha < 0) && (beta > 0) && (gamma < 0)) {
    // case3: outside triangle, around point B
    // update P to B
    Eigen::Vector3d BtoA = Av - Bv;
    Eigen::Vector3d BtoB = Bv - Bv;
    Eigen::Vector3d BtoC = Cv - Bv;

    areaAB = (1/2.) * (BtoA.cross(BtoB).norm());
    areaAC = (1/2.) * (BtoA.cross(BtoC).norm());
    areaBC = (1/2.) * (BtoB.cross(BtoC).norm());

    alpha = fabs(areaBC / areaABC);
    beta = fabs(areaAC / areaABC);
    gamma = 1 - alpha - gamma;
    bary(0) = alpha; bary(1) = beta; bary(2) = gamma;

    return pow((QUERYv - Bv).norm(), 2);

  } else if ((alpha < 0) && (beta < 0) && (gamma > 0)) {
    // case4: outside triangle, around point C
    // update P to C
    Eigen::Vector3d CtoA = Av - Cv;
    Eigen::Vector3d CtoB = Bv - Cv;
    Eigen::Vector3d CtoC = Cv - Cv;

    areaAB = (1/2.) * (CtoA.cross(CtoB).norm());
    areaAC = (1/2.) * (CtoA.cross(CtoC).norm());
    areaBC = (1/2.) * (CtoB.cross(CtoC).norm());

    alpha = fabs(areaBC / areaABC);
    beta = fabs(areaAC / areaABC);
    gamma = 1 - alpha - gamma;
    bary(0) = alpha; bary(1) = beta; bary(2) = gamma;

    return pow((QUERYv - Cv).norm(), 2);

  } else if ((alpha > 0) && (beta > 0) && (gamma < 0)) {
    // case5: outside triangle, around line AB
    double t = (P - Av).dot(Bv - Av) / (Bv - Av).dot(Bv - Av);
    Eigen::Vector3d newP = Av + t * (Bv - Av);
    // update P to newP
    Eigen::Vector3d PtoA = Av - newP;
    Eigen::Vector3d PtoB = Bv - newP;
    Eigen::Vector3d PtoC = Cv - newP;

    areaAB = (1/2.) * (PtoA.cross(PtoB).norm());
    areaAC = (1/2.) * (PtoA.cross(PtoC).norm());
    areaBC = (1/2.) * (PtoB.cross(PtoC).norm());

    alpha = fabs(areaBC / areaABC);
    beta = fabs(areaAC / areaABC);
    gamma = 1 - alpha - gamma;
    bary(0) = alpha; bary(1) = beta; bary(2) = gamma;

    return pow((QUERYv - newP).norm(), 2);

  } else if ((alpha < 0) && (beta > 0) && (gamma > 0)) {
    // case6: outside triangle, around line BC
    double t = (P - Bv).dot(Cv - Bv) / (Cv - Bv).dot(Cv - Bv);
    Eigen::Vector3d newP = Bv + t * (Cv - Bv);
    // update P to newP
    Eigen::Vector3d PtoA = Av - newP;
    Eigen::Vector3d PtoB = Bv - newP;
    Eigen::Vector3d PtoC = Cv - newP;

    areaAB = (1/2.) * (PtoA.cross(PtoB).norm());
    areaAC = (1/2.) * (PtoA.cross(PtoC).norm());
    areaBC = (1/2.) * (PtoB.cross(PtoC).norm());

    alpha = fabs(areaBC / areaABC);
    beta = fabs(areaAC / areaABC);
    gamma = 1 - alpha - gamma;
    bary(0) = alpha; bary(1) = beta; bary(2) = gamma;

    return pow((QUERYv - newP).norm(), 2);

  } else if ((alpha > 0) && (beta < 0) && (gamma > 0)) {
    // case7: outside triangle, around line CA
    double t = (P - Cv).dot(Av - Cv) / (Av - Cv).dot(Av - Cv);
    Eigen::Vector3d newP = Cv + t * (Av - Cv);
    // update P to newP
    Eigen::Vector3d PtoA = Av - newP;
    Eigen::Vector3d PtoB = Bv - newP;
    Eigen::Vector3d PtoC = Cv - newP;

    areaAB = (1/2.) * (PtoA.cross(PtoB).norm());
    areaAC = (1/2.) * (PtoA.cross(PtoC).norm());
    areaBC = (1/2.) * (PtoB.cross(PtoC).norm());

    alpha = fabs(areaBC / areaABC);
    beta = fabs(areaAC / areaABC);
    gamma = 1 - alpha - gamma;
    bary(0) = alpha; bary(1) = beta; bary(2) = gamma;

    return pow((QUERYv - newP).norm(), 2);
  }

  return 0;
  ////////////////////////////////////////////////////////////////////////////
}
