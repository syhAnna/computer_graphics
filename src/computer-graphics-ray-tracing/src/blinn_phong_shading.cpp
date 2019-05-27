#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <limits>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
    Eigen::Vector3d objPos = ray.origin + t * ray.direction;
    Eigen::Vector3d rgb = Eigen::Vector3d(0, 0, 0);
    int scale = 1000;

    for(int i = 0; i < lights.size();i++){
        Eigen::Vector3d l;
        double t_light;
        int id;

        lights[i]->direction(objPos, l, t_light);
        Eigen::Vector3d h = ((-1) * ray.direction.normalized() + l.normalized()).normalized();

        // shoot a ray from p to light source, check if this ray hit any object
        Ray shadowRay;
        shadowRay.direction = l;
        shadowRay.origin = objPos;
        double shadow_t = 0;
        Eigen::Vector3d shadow_n = Eigen::Vector3d(0, 0, 0);

        if(!first_hit(shadowRay, std::numeric_limits<double>::epsilon()*scale, objects, id, shadow_t, shadow_n)
        || shadow_t > t_light){

            double kd_term = (n.dot(l) > 0) ? n.dot(l) : 0;
            double ks_term = (n.dot(h) > 0) ? n.dot(h) : 0;

            rgb += (objects[hit_id]->material->kd.array() * lights[i]->I.array()).matrix() * kd_term +  // kd
                   (objects[hit_id]->material->ks.array() * lights[i]->I.array()).matrix() * // ks
                   pow(ks_term, objects[hit_id]->material->phong_exponent);
        }
    }

    return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
