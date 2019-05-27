// Construct the model transformation matrix. The moon should orbit around the
// origin. The other object should stay still.
//
// Inputs
//   is_moon  whether we're considering the moon
//   time  seconds on animation clock
// Returns affine model transformation as 4x4 matrix
//
// expects: identity, rotate_about_y, translate, PI
mat4 model(bool is_moon, float time)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  if (is_moon) {
    // amount to scale in all directions
    // According to the comment in 'model_view_projection':
    // 'shrink the model by 30%'
    float s = 0.3;

    // According to the comment in 'model_view_projection':
    // 'shift away from the origin by 2 units'
    vec3 t = vec3(2, 0, 0);

    // amount y which to rotate (in radians)
    // According to the comment in 'model_view_projection':
    // 'rotate around the origin at a frequency of 1 revolution per 4 seconds'
    float theta = ((2. * M_PI) / 4.) * time;

    // construct the model using: uniform_scale, translate, rotate_about_y
    mat4 model = rotate_about_y(theta) * translate(t) * uniform_scale(s);

    return model;

  } else {
    return identity();
  }
  /////////////////////////////////////////////////////////////////////////////
}
