#pragma once
#include "raylib.h"
#include "Settings.h"
#include <stdlib.h>

typedef struct Star {
	Vector2 pos;
	float scale;
	float lifeSpan;
} Star;

void StarInit(Star *star);

void StarsCreate(Star ***stars);