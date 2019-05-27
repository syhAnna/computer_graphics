// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  vec3 tangent1 = vec3(0,1,0);
  vec3 tangent2 = vec3(0,0,1);

  vec3 cross1 = cross(N, tangent1);
  vec3 cross2 = cross(N, tangent1);

  T = (length(cross1) > length(cross2)) ? cross1 : cross2;

  T = normalize(T);
  B = normalize(cross(T, N));
  return;
  /////////////////////////////////////////////////////////////////////////////
}
