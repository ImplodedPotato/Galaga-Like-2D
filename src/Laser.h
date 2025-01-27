#pragma once
#include "raylib.h"
#include "Settings.h"
#include "fun.h"
#include "Player.h"
#include <stdlib.h>

struct Player;

typedef struct Laser {
    int speed;
    Vector2 direction;
    Vector2 pos;
    Rectangle hitBox;
} Laser;

void LazerInit(Laser *laser, struct Player player); // Initalize the Laser

void LaserDelete(Laser **lasers, int deleteIndex, int *numberOfLasers); // Delete a laser

void LasersUpdate(Laser **lasers, int *numberOfLasers, float dt); // Update the Lasers, Ran once a frame