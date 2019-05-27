#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // consider algorithm from: Fundamentals of Computer Graphics; p86-87, 4.7-8
  // consider the data in the .json file
  // ka: ambient; kd: diffuse; ks: specular; km: mirror
  // total color = shading + mirror

  int id = 0;
  double t = 0;
  double reflectionMin_t = 0.001;
  double epsilon = 0.001;
  int max_depth = 5;

  Eigen::Vector3d n = Eigen::Vector3d(0, 0, 0);
  Eigen::Vector3d objPos = Eigen::Vector3d(0, 0, 0);
  Eigen::Vector3d Ia = Eigen::Vector3d(0.1, 0.1, 0.1);

  if (first_hit(ray, min_t, objects, id, t, n)) {
    // position of the first hit object
    objPos = ray.origin + t * ray.direction;

    // original phong shading: ka + blinn_phong
    rgb = ((objects[id]->material->ka).array() * Ia.array()).matrix() +
            (blinn_phong_shading(ray, id, t, n, objects, lights));

    // ideal specular reflection
    Ray reflection;
    reflection.origin = objPos;
    reflection.direction = reflect(ray.direction, n);
    Eigen::Vector3d reflectionKm = objects[id]->material->km;
    Eigen::Vector3d reflectionColor = Eigen::Vector3d(0, 0, 0);

    // add the mirror reflection
    if ((std::pow(reflectionKm(0), num_recursive_calls) >= epsilon) &&
    (std::pow(reflectionKm(1), num_recursive_calls) >= epsilon) &&
    (std::pow(reflectionKm(2), num_recursive_calls) >= epsilon) &&
    (raycolor(reflection, reflectionMin_t, objects,
            lights, num_recursive_calls+1, reflectionColor)) &&
            num_recursive_calls < max_depth) {
      // component-wise multiplication
      rgb += (reflectionKm.array() * reflectionColor.array()).matrix();
    }
    return true;

  } else { // ray does not hit anything
    rgb = Eigen::Vector3d(0,0,0);
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}
