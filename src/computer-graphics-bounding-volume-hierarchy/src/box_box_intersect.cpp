#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  int flag = 0;
  int dim = 3;

  // we get the 3 dimensions
  // check the
  for (int i = 0; i < dim; i++) {
    if ((A.min_corner[i] >= B.min_corner[i]) && (A.min_corner[i] <= B.max_corner[i])) {
      flag += 1;
    } else if ((A.max_corner[i] >= B.min_corner[i]) && (A.max_corner[i] <= B.max_corner[i])) {
      flag += 1;
    } else if ((B.min_corner[i] >= A.min_corner[i]) && (B.min_corner[i] <= A.max_corner[i])) {
      flag += 1;
    } else if ((B.max_corner[i] >= A.min_corner[i]) && (B.max_corner[i] <= A.max_corner[i])) {
      flag += 1;
    }
  }

  return (flag == 3);
  ////////////////////////////////////////////////////////////////////////////
}

