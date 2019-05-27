#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());
  for (int i = 0; i < skeleton.size(); i++) {
      Eigen::Affine3d v = Eigen::Affine3d::Identity();
      Bone bone = skeleton[i];
      // the general node bone
      if (skeleton[i].parent_index != -1) {
          v = T[bone.parent_index];
      }
      T[i] = v * bone.rest_T *
             euler_angles_to_transform(bone.xzx) *
             bone.rest_T.inverse();
  }
  /////////////////////////////////////////////////////////////////////////////
}
