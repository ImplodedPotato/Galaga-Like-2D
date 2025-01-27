#include "Star.h"

void StarInit(Star *star) {
	star->pos = (Vector2){GetRandomValue(0, GetScreenWidth()), GetRandomValue(0, GetScreenHeight())};
	star->scale = GetRandomValue(1, 3) / 3;
	star->lifeSpan = GetRandomValue(1, 10);
}

void StarsCreate(Star ***stars) {
	*stars = malloc(NUMBER_OF_STARS * sizeof(Star *));
	for (int i = 0; i < NUMBER_OF_STARS; i++) {
		(*stars)[i] = (Star *)malloc(sizeof(Star));
		StarInit((*stars)[i]);
	}
}