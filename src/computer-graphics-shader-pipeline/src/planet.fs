// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
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
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent

vec3 normal_map(vec3 p){
	vec3 T, B;
	tangent(p, T, B);
	float scale = 0.00001;

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
  vec3 ka; vec3 kd; vec3 ks;
  float p = 1000;
  vec3 s = sphere_fs_in;

  // blinn phong
  vec4 view_direction = view * view_pos_fs_in;
  float light_theta = animation_seconds * M_PI / 4;
  mat4 rotation = mat4(
  cos(light_theta),  0, sin(light_theta), 0,
           0,        1.,         0,       0,
  -sin(light_theta), 0, cos(light_theta), 0,
           0,        0,          0,       1.);

  vec3 l = ((view * rotation * vec4(8., 2., 1., 0.))).xyz;
  vec3 v = view_direction.xyz;

  mat4 view_and_transform = view * model(is_moon, animation_seconds);
  vec3 normal = normalize((inverse(transpose(view_and_transform)) * vec4(normal_map(sphere_fs_in), 1.)).xyz);

  if (is_moon){
    ka = vec3(0.03, 0.03, 0.03);
    kd = vec3(0.5, 0.5, 0.5);
    ks = vec3(0.8,0.8,0.8);
  } else { // earth
    float height = bump_height(is_moon, sphere_fs_in);
    if (height <= .001 && .5 * sphere_fs_in.z / animation_seconds <= 0.1 && animation_seconds > .5){
      // ocean animation, change according to z-axis
      ka = vec3(0.01, 0.02, 0.05);
      kd = vec3(0.2, 0.3, 0.8);
      ks = vec3(0.8, 0.8, 0.8);
    } else {
      // continent, yellow on lattitude then change to green
      ka = vec3(0.01, 0.01, 0.01);
      //green and yellow mix land
      kd = vec3(1.2 * (1 - abs(sphere_fs_in.y)), 1, .2);
      ks = vec3(0.3, 0.3, 0.3);
    }
  }

  if (is_moon) {
    color = blinn_phong(ka, kd, ks, p, normal, v, l);
  } else {
    vec3 c = blinn_phong(ka, kd, ks, p, normal, v, l);

    // add cloud animation
    if (animation_seconds > 7) { // cloud appears at 7s
      float cloud_alpha = 0.6;
      vec3 f = vec3(1.5, 5, 2);
      float animation_control = min(max(animation_seconds, 0), 1);
      vec3 cloud_color = vec3(1, 1, 1);

      vec3 s = vec3(sphere_fs_in.x + 0.1 * animation_seconds,
                    sphere_fs_in.y, 0);

      float noise = improved_perlin_noise(s * f);
      float w = (smooth_heaviside(noise, 10) + 0.03) * 0.6;
      float alpha = 0.7 * w * cloud_alpha * animation_control;
      color = cloud_color * alpha + (1 - alpha) * c;
    }
  }
  /////////////////////////////////////////////////////////////////////////////
}
