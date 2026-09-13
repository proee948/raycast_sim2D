# raycast_sim2D

A real-time 2D ray-casting simulation built with SDL2. A light source casts a configurable number of rays outward, which travel until they intersect an obstacle circle.

## Overview

`raysim` renders a light-emitting circle that fires a ring of rays in all directions. Each ray travels outward until it hits a movable obstacle circle, at which point it stops — producing a live shadow-casting effect. An in-simulation overlay menu lets you tune ray count, ray length, and the obstacle's render color.

## Features

- Real-time ray casting from a central light source, with per-frame recalculation of ray-obstacle intersections
- Mouse-draggable light source
- Keyboard and mouse-wheel control of the obstacle circle's position and radius
- In-app overlay menu (toggled with Q) for adjusting:
  - Number of active rays
  - Maximum ray length
  - Obstacle color, cycled through a set of preset colors
- Built entirely on SDL2 primitives — no external rendering engine

## Controls

| Input | Action |
|---|---|
| Left-click + drag | Move the light source circle |
| Arrow keys | Move the obstacle circle |
| Mouse wheel | Grow / shrink the obstacle circle's radius |
| `Q` | Open the settings menu |
| `A` | Close the settings menu |

## Requirements

- A C compiler
- SDL2
- SDL2_ttf

### Installing dependencies (Debian/Ubuntu)

    `sudo apt install libsdl2-dev libsdl2-ttf-dev`

## Building

   `gcc main.c -o raysim -lSDL2 -lSDL2_ttf -lm`

## Running

    `./raysim`

## Project Structure

    .
    ├── main.c        # Simulation loop, rendering, ray-casting logic, menu
    ├── ray.h         # Shared type definitions (Circle, ray, config constants)
    ├── arrow_left.bmp
    ├── arrow_right.bmp
    └── font.ttf

## TO FIX/ADD

- [ ]texture redrawing
- [ ]texture leaks
- [ ]resizable window
- [ ] code cleanup and redundancy removal
