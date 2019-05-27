// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent

vec3 normal_trans(vec3 p){
	vec3 T, B;
	tangent(p, T, B);
	float scale = 0.0001;

	vec3 p1 = bump_position(is_moon, p);
	vec3 p2 = bump_position(is_moon, p + scale * T);
	vec3 p3 = bump_position(is_moon, p + scale * B);
	vec3 n = normalize(cross((p2-p1) / scale, (p3-p1) / scale));

	if (dot(p, n) <= 0){
		n = -n;
	}
	return n;
}

void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  // view direction
  // according to the code from lit.fs
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

  // additional code add into the lit.fs code, normalization
  mat4 view_transform = view * model(is_moon, animation_seconds);
  vec3 normal = normalize((inverse(transpose(view_transform)) * vec4(normal_trans(sphere_fs_in), 1.0)).xyz);

  // Hard code data according to the data in Assignment2's .json file
  vec3 ks = vec3(0.8, 0.8, 0.8);
  int p = 1000;
  vec3 ka; vec3 kd;

  if (is_moon) {
     // moon is gray
     ka = vec3(0.05, 0.05, 0.05);
     kd = vec3(0.5, 0.5, 0.5);
  } else {
     // earth is blue
     ka = vec3(0.02, 0.03, 0.08);
     kd = vec3(0.2, 0.3, 0.8);
  }

  ks += improved_perlin_noise(sphere_fs_in);
  color = blinn_phong(ka, kd, ks, p, normal, v, l);
  /////////////////////////////////////////////////////////////////////////////
}
