#include "Laser.h"

void LazerInit(Laser *laser, Player player) {
	laser->speed = LASER_SPEED;
	laser->direction = (Vector2){0, -1};
	laser->pos = (Vector2){player.pos.x + 56, player.pos.y};
    laser->hitBox = (Rectangle){laser->pos.x, laser->pos.y, 9, 54};
}

void LaserDelete(Laser **lasers, int deleteIndex, int *numberOfLasers) {
	lasers[deleteIndex] = NULL;
	free(lasers[deleteIndex]);
	int newNumberOfLasers = *numberOfLasers;
	for (int j = deleteIndex; j < newNumberOfLasers - 1; j++) {
		lasers[j] = lasers[j + 1];
	}

	(*numberOfLasers)--;
}

void LasersUpdate(Laser **lasers, int *numberOfLasers, float dt) {
	// position
	if (*numberOfLasers <= 0) {
		return;
	}
	for (int i = 0; i < *numberOfLasers; i++) {
		lasers[i]->pos.y += lasers[i]->direction.y * LASER_SPEED * dt;
        lasers[i]->hitBox = (Rectangle){lasers[i]->pos.x, lasers[i]->pos.y, 9, 54};
	}
	const int newLaserCount = *numberOfLasers;

	for (int i = 0; i < newLaserCount; i++) {
		if (lasers[i] == NULL) {
			continue;
		}
		if (lasers[i]->pos.y < 0) {
			LaserDelete(lasers, i, &(*numberOfLasers));
			i--;
		}
	}
	if (*numberOfLasers > 0) {
		lasers = realloc(lasers, (*numberOfLasers) * sizeof(Laser *));
	}
	// Add code for collision
}