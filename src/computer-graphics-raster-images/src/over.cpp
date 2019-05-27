#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int i = 0; i < A.size(); i += 4) {
    for (int j = i; j < i + 4; j++) {
      if (j < i + 3) { // r, g, b
        double alpha = A[i + 3] / 255.;
        C[j] = alpha * A[j] + (1 - alpha) * B[j];
      } else { // alpha
        // alpha compositing formula from wikipedia:
        // https://en.wikipedia.org/wiki/Alpha_compositing#Analytical_derivation_of_the_over_operator
        C[j] = A[i + 3] + B[i + 3] * (1 - A[i + 3] / 255.);
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}