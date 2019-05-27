// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  vec2 psuedorandom = random2(seed);
  float theta = (2. * M_PI / 4.) * psuedorandom.x;
  float phi = (2. * M_PI / 4.) * psuedorandom.y;

  float x = sin(theta) * cos(phi) * 1.;
  float y = sin(theta) * sin(phi) * 1.;
  float z = cos(theta) * 1.;

  // spherical coordinate
  return normalize(vec3(x, y, z));
  /////////////////////////////////////////////////////////////////////////////
}
