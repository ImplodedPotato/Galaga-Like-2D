#include "Explosion.h"

void ExplosionInit(Explosion *explosion, Meteor meteor, Texture tex) {
	explosion->pos = meteor.pos;
	explosion->scale = meteor.scale;
	explosion->tex = tex;
	explosion->animationIndex = 0;
}

void ExplosionsUpdate(Explosion **explosions, int *numberOfExplosions, float dt, Texture frames[]) {
	if (*numberOfExplosions <= 0) {
		return;
	}
	int newNumberOfExplosions = *numberOfExplosions;
	for (int i = 0; i < newNumberOfExplosions; i++) {
		explosions[i]->animationIndex += ANIMATION_SPEED * dt;
		if ((int)explosions[i]->animationIndex % 28 == 27) {
			// delete explosion
			explosions[i] = NULL;
			free(explosions[i]);
			for (int j = i; j < newNumberOfExplosions - 1; j++) {
				explosions[j] = explosions[j + 1];
			}
			(*numberOfExplosions)--;
		} else {
			explosions[i]->tex = frames[(int)explosions[i]->animationIndex % 28];
		}
	}
}