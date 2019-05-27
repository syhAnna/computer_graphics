// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step
float improved_perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  // Understand the Perlin Noise: https://flafla2.github.io/2014/08/09/perlinnoise.html

    // "First, divide the x, y, and z coordinates into unit cubes.
    // i.e.: find [x,y,z] % 1.0 to find the coordinate's location within the cube"
    vec3 pt1 = floor(st) + vec3(0, 0, 0); vec3 pt2 = floor(st) + vec3(1, 0, 0);
    vec3 pt3 = floor(st) + vec3(0, 0, 1); vec3 pt4 = floor(st) + vec3(1, 0, 1);
    vec3 pt5 = floor(st) + vec3(0, 1, 0); vec3 pt6 = floor(st) + vec3(1, 1, 0);
    vec3 pt7 = floor(st) + vec3(0, 1, 1); vec3 pt8 = floor(st) + vec3(1, 1, 1);

    // "On each of the 4 unit coordinates (8 in 3D),
    // we generate what's called a pseudorandom gradient vector"
    vec3 gradient1 = random_direction(pt1); vec3 gradient2 = random_direction(pt2);
    vec3 gradient3 = random_direction(pt3); vec3 gradient4 = random_direction(pt4);
    vec3 gradient5 = random_direction(pt5); vec3 gradient6 = random_direction(pt6);
    vec3 gradient7 = random_direction(pt7); vec3 gradient8 = random_direction(pt8);

    // "Next, we take the dot product between the two vectors (the gradient vector and the distance vector)
    // This gives us our final influence values:"
    float smooth1 = dot(gradient1, st - pt1); float smooth2 = dot(gradient2, st - pt2);
    float smooth3 = dot(gradient3, st - pt3); float smooth4 = dot(gradient4, st - pt4);
    float smooth5 = dot(gradient5, st - pt5); float smooth6 = dot(gradient6, st - pt6);
    float smooth7 = dot(gradient7, st - pt7); float smooth8 = dot(gradient8, st - pt8);

    // "Interpolate so that get a sort of weighted average in between With weighted average,
    // final result would look bad because linear interpolation, need a smoother transition between gradients."
    vec3 smooth_vector = improved_smooth_step(st - pt1);
    float smooth_x1_2 = smooth_vector.x * (smooth2 - smooth1) + smooth1;
    float smooth_x3_4 = smooth_vector.x * (smooth4 - smooth3) + smooth3;
    float smooth_x5_6 = smooth_vector.x * (smooth6 - smooth5) + smooth5;
    float smooth_x7_8 = smooth_vector.x * (smooth8 - smooth7) + smooth7;

    float smooth_y1 = smooth_vector.y * (smooth_x5_6 - smooth_x1_2) + smooth_x1_2;
    float smooth_y2 = smooth_vector.y * (smooth_x7_8 - smooth_x3_4) + smooth_x3_4;

    float result = smooth_vector.z * (smooth_y2 - smooth_y1) + smooth_y1;

    // return value between [-1/2, 1/2]
    return result / 2;
  /////////////////////////////////////////////////////////////////////////////
}

