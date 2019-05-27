// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  float noise;
  vec3 f = vec3(1, 10, 3);
  vec3 a = normalize(vec3(300, 10, 100));

  if (is_moon) { // moon
    float scale = 0.25;
    float sum = improved_perlin_noise(s / scale);
    float noise = 0.2 * scale * sin(M_PI * (s.x + 2 * sum) +
                                    M_PI * (s.y + 2 * sum) +
                                    M_PI * (s.z + 2 * sum));
    float height = 0.05 * smooth_heaviside(noise, 40);
    noise = a.x * improved_perlin_noise(s * f.x) +
            a.y * improved_perlin_noise(s * f.y) +
            a.z * improved_perlin_noise(s * f.z);
    height += noise + 2;
    return height;

  } else { // earth
    float scale = 0.5;
        float sum = improved_perlin_noise(s / scale);
        float noise = 0.3 * scale * sin(M_PI * (s.x + 1.5 * sum) +
                                        M_PI * (s.y + 2 * sum) +
                                        M_PI * (s.z + 2.5 * sum));

        noise += .2 * improved_perlin_noise(s * 2) +
                 .3 * improved_perlin_noise(s * 8) +
                 .5 * improved_perlin_noise(s * 4);

        if (smooth_heaviside(noise * 5 + .1, 2) * .02 > 0.001) {
          return smooth_heaviside(noise * 5 + .1, 2) * .03;
        }

        return smooth_heaviside(noise * 6 + .1, 2) * 0.03;
  }
  /////////////////////////////////////////////////////////////////////////////
}
