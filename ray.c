#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "ray.h"
#include <string.h>

void draw_fill_circle(SDL_Renderer *renderer, struct Circle circle, uint8_t R,uint8_t G,uint8_t B,uint8_t A)
{
    
    SDL_SetRenderDrawColor(renderer,R,G,B,A);
    double radius_squared = (circle.r * circle.r);
    for (double x = circle.x - circle.r; x <= circle.x + circle.r; x++) {
        for (double y = circle.y - circle.r; y <= circle.y + circle.r; y++) {
            double distance_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
            if (distance_squared <= radius_squared) {
                SDL_Rect pixel = (SDL_Rect){ (int)x, (int)y, 1, 1 };
                if(SDL_RenderDrawPoint(renderer,(int)x,(int)y) != 0){printf("ERR><><");}
  
            }
        }
    }
}

void shoot_rays(struct Circle shooter_circle, struct ray ray_Arr[], SDL_Renderer* renderer, struct Circle circle)
{
    double x_start = shooter_circle.x;
    double y_start = shooter_circle.y; 
    double angle_arr[RAYS_MAX]; 
    double length = 1600;   

    int a = 0;
    for (double i = 0; i < RAYS_MAX; i++)
    {
        double angle = (i / RAYS_MAX) * 360;
        angle_arr[a++] = angle;
    }
    
    double radian_arr[RAYS_MAX];
    for (int i = 0; i < RAYS_MAX; i++)
    {
        radian_arr[i] = angle_arr[i] * (M_PI / 180.0f);
    }

    double radius_squared = circle.r * circle.r;

    for (int i = 0; i < RAYS_MAX; i++)
    {
        double dx = cos(radian_arr[i]);   
        double dy = sin(radian_arr[i]);

        double step_size = 1.0;
        double t = 0;
        double stop_t = length;   

        while (t < length)
        {
            double px = x_start + dx * t;
            double py = y_start + dy * t;
            double distance_squared = pow(px - circle.x, 2) + pow(py - circle.y, 2);

            if (distance_squared <= radius_squared)
            {
                stop_t = t;   
                break;
            }

            t += step_size;
        }

        ray_Arr[i].start_x = x_start;
        ray_Arr[i].start_y = y_start;
        ray_Arr[i].end_x = x_start + dx * stop_t;
        ray_Arr[i].end_y = y_start + dy * stop_t;
    }

    for (int i = 0; i < RAYS_MAX; i++)
    {
        if (SDL_RenderDrawLineF(renderer, ray_Arr[i].start_x, ray_Arr[i].start_y, ray_Arr[i].end_x, ray_Arr[i].end_y) != 0)
        {
            printf("render failed");
        }
    }
}

int menu(SDL_Renderer *renderer)
{
    bool trigger = 0;
    SDL_Event event;

    while(trigger == 0)
    {
        SDL_Texture *t = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC,20,20);
        SDL_Surface *surface = SDL_LoadBMP("arrow_right.bmp");
        SDL_Rect menu = {.h = MENU_HEIGHT, .w = MENU_WIDTH, .x = MENU_X, .y = MENU_Y};
        t = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);

        SDL_RenderCopy(renderer,t,NULL,&menu);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,0,0,0);
        SDL_RenderDrawRect(renderer,&menu);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);
        SDL_Delay(10);
        



        while(SDL_PollEvent(&event))
        {
            if( (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_A) || (event.type == SDL_QUIT))
            {
                trigger = 1;
            }
        }
    } 
    return 0;

}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("raysim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *r = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    struct Circle krug = {100,100,70}; 
    struct Circle shadow_krug = {800,400,170};
    struct ray ray_arr[RAYS_MAX];
    bool sim_running = true;
    bool menu_active = false;
    SDL_Event event;
    int32_t wheel_state = event.wheel.y;

    while (sim_running)
    {
        while (SDL_PollEvent(&event))
        {
            //
            if( event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_Q)
            {
                menu(r);
            }
            //

            if (event.type == SDL_QUIT) {
                sim_running = false;
            }

            if(event.type == SDL_MOUSEMOTION && event.motion.state != 0 )
            {
            krug.x = event.motion.x;
            krug.y = event.motion.y;
            }

            if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_UP: shadow_krug.y -= CONTROL_SPEED_ARROWS       ;break;
                    case SDL_SCANCODE_DOWN: shadow_krug.y += CONTROL_SPEED_ARROWS     ;break;
                    case SDL_SCANCODE_LEFT: shadow_krug.x -= CONTROL_SPEED_ARROWS     ;break;
                    case SDL_SCANCODE_RIGHT: shadow_krug.x += CONTROL_SPEED_ARROWS     ;break;
                }
            }

            if(event.wheel.type == SDL_MOUSEWHEEL)
            {
                if(event.wheel.y > 0){
                    shadow_krug.r += CONTROL_SPEED_WHEEL;
                }
                 if(event.wheel.y < 0){
                    shadow_krug.r -= CONTROL_SPEED_WHEEL;
                }

            }

               //if(menu_active == true)
               //{
                //sim_running = false;
                //draw_menu()
               //}
        }

        SDL_SetRenderDrawColor(r,0,0,0,255);
        SDL_RenderClear(r);

        SDL_SetRenderDrawColor(r,255,255,0,255); //ray color
        shoot_rays(krug,ray_arr,r,shadow_krug);
        draw_fill_circle(r, krug,R,G,B,A); // very gpu intensive calls

        draw_fill_circle(r, shadow_krug,255,0,0,150); //same 
        //
        SDL_RenderPresent(r);
    }
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
