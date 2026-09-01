#ifndef RAY_H
#define RAY_H

struct Circle
{
    double x;
    double y;
    double r;
};
struct ray
{
    double start_x;
    double start_y;
    double end_x;
    double end_y;
};
struct vector2
{
    double x;
    double y;
};


#define WIDTH 1600
#define HEIGHT 1000
#define RAYS_MAX 200
#define M_PI 3.14159265358979323846
#define CONTROL_SPEED_ARROWS 10
#define CONTROL_SPEED_WHEEL 2

#endif
