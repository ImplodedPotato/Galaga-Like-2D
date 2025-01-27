#pragma once
#include "raylib.h"
#include "Meteor.h"
#include "Settings.h"
#include <stdio.h>
#include <stdlib.h>

struct Meteor;

typedef struct Explosion {
	Vector2 pos;
	int scale;
	Texture tex;
	float animationIndex;
} Explosion;

void ExplosionInit(Explosion *explosion, struct Meteor meteor, Texture tex);

void ExplosionsUpdate(Explosion **explosions, int *numberOfExplosions, float dt, Texture frames[]);