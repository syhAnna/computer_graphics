#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int dimension = 3;

  for (int i = 0; i < dimension; i++) {
     // insert boxA to boxB
     if (A.min_corner[i] < B.min_corner[i]) {
        B.min_corner[i] = A.min_corner[i];
     }
     if (A.max_corner[i] > B.max_corner[i]) {
        B.max_corner[i] = A.max_corner[i];
     }
  }
  ////////////////////////////////////////////////////////////////////////////
}

