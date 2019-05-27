// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  // view direction
  vec4 view_direction = view_pos_fs_in;
  vec3 v = (view_direction).xyz;

  // light rotation
  float light_theta = (2. * M_PI / 8.) * animation_seconds;
  mat4 light_rotation = mat4(
  cos(light_theta),  0, sin(light_theta), 0,
          0,         1.,        0,        0,
  -sin(light_theta), 0, cos(light_theta), 0,
          0,         0,         0,        1.);
  vec3 l = (light_rotation * view * vec4(14., 14., 1., 0.8)).xyz;

  // Hard code data according to the data in Assignment2's .json file
  vec3 ks = vec3(0.8, 0.8, 0.8);
  int p; vec3 ka; vec3 kd;

  if (is_moon) {
    // moon is gray
    p = 500;
    ka = vec3(0.05, 0.05, 0.05);
    kd = vec3(0.5, 0.5, 0.5);
  } else {
    // earth is blue
    p = 1000;
    ka = vec3(0.02, 0.03, 0.08);
    kd = vec3(0.2, 0.3, 0.8);
  }

  color = blinn_phong(ka, kd, ks, p, normalize(normal_fs_in), v, l);
  /////////////////////////////////////////////////////////////////////////////
}
