#include "ut_math.h"
#include <math.h>

#define PI 3.141592653

float Rad2Deg(float rad)
{
  return (rad * 180) / PI;
}

float Deg2Rad(float deg)
{
  return (deg * PI) / 180;
}

float GetAngleBetweenVectors(vec2 v1, vec2 v2)
{
  float dot = v1[0] * v2[0] + v1[1] * v2[1];
  float det = v1[0] * v2[1] - v1[1] * v2[0];
  float angle = atan2f(det, dot);
  return angle;
}
