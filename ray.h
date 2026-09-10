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


uint8_t R,G,B,A;
uint32_t RAYS_MAX  = 5;
#define RAYS_HARD_LIMIT 1000

#define WIDTH 1600
#define HEIGHT 1000
#define M_PI 3.14159265358979323846
#define CONTROL_SPEED_ARROWS 10
#define CONTROL_SPEED_WHEEL 2
#define MENU_X ((WIDTH/2) - (MENU_WIDTH / 2))
#define MENU_Y ((HEIGHT/2) - (MENU_HEIGHT / 2))
#define MENU_HEIGHT 600
#define MENU_WIDTH 800

#endif
