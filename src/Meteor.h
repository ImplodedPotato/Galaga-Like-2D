#pragma once
#include "raylib.h"
#include "Explosion.h"
#include "Laser.h"
#include "Settings.h"
#include "Player.h"
#include <stdio.h>
#include <stdlib.h>

struct Player;
struct Laser;
struct Explosion;

typedef struct Meteor {
    Vector2 pos;
    Vector2 direction;
    int speed;
    float scale;
    Vector2 size;
    Rectangle hitBox;
} Meteor;

void MeteorInit(Meteor *meteor);

void MeteorExplosion(struct Explosion ***explosions, int *numberOfExplosions, Meteor meteor, Texture startingtex);

void MeteorsUpdate(Meteor **meteor, float dt, struct Laser **lasers, int *numberOfLasers, struct Player *player, struct Explosion ***explosions, int *numberOfExplosions, Texture startingtex, Sound explosionSound);