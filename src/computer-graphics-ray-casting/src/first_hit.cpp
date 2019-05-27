#include "first_hit.h"
#include <limits>

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double currMin = std::numeric_limits<double>::infinity();
  bool flag = false;
  double first_t;
  Eigen::Vector3d matrix3by3;

  // loop through all the objects, find the closet one
  for (int objIndex = 0; objIndex < objects.size(); objIndex++) {
    if (objects[objIndex]->intersect(ray, min_t, first_t, matrix3by3)) {
      if (first_t < currMin) {
        flag = true;
        currMin = first_t;
        hit_id = objIndex;
        n = matrix3by3;
      }
    }
  }

  t = currMin;
  return flag;
  ////////////////////////////////////////////////////////////////////////////
}

