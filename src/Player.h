#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Settings.h"
#include "fun.h"
#include "Laser.h"
#include <stdlib.h>

struct Laser;

typedef struct Player {
	int health;
    bool isDead;
	int speed;
	int score;
	Vector2 direction;
	Vector2 pos;
	Texture sprite;
    Rectangle hitBox;
} Player;

void PlayerInit(Player *player, int health); // Initalize the Player

void PlayerUpdate(Player *player, float dt); // Update the Player, Ran once a frame

void PlayerShoot(Player player, struct Laser ***lasers, int *numberOfLasers, Sound laserSound); // Spawns a laser, when the player shoots

