#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  // https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline
  Eigen::Vector3d value = Eigen::Vector3d(0,0,0);
  int num_keyframe = keyframes.size();

  // there is not frame in the keyframe
  if (num_keyframe != 0) {
    //list of pairs of (key-times, key-values), in ascending order of time
    t = fmod(t, keyframes[num_keyframe - 1].first);
    double t0, t1, t2, t3, proportion;
    Eigen::Vector3d p0, p1, p2, p3;

    for (int i = 0; i < num_keyframe; i++) {
      if (keyframes[i].first >= t) {
        p0 = keyframes[fmax(i-2, 0)].second;
        p1 = keyframes[fmax(i-1, 0)].second;
        p2 = keyframes[i].second;
        p3 = keyframes[fmin(i+1, keyframes.size()-1)].second;

        if (i == 0) {
          proportion = (t - keyframes[0].first) / (keyframes[1].first - keyframes[0].first);
        } else {
          proportion = (t - keyframes[i-1].first) / (keyframes[i].first - keyframes[i-1].first);
        }

        return 0.5 * ((2 * p1) + (p2 - p0) * proportion +
                      (2 * p0 - 5 * p1 + 4 * p2 - p3) * pow(proportion, 2.0) +
                      (- p0 + 3 * p1 - 3 * p2 + p3) * pow(proportion, 3.0));
      }
    }
  }

  return Eigen::Vector3d(0,0,0);
  /////////////////////////////////////////////////////////////////////////////
}
