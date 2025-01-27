#include "Meteor.h"

void MeteorInit(Meteor *meteor) {
	meteor->pos = (Vector2){GetRandomValue(0, GetScreenWidth()), GetRandomValue(-100, -1000)};
	meteor->direction = (Vector2){0, 1};
	meteor->speed = GetRandomValue(METEOR_SPEED_MIN, METEOR_SPEED_MAX);
	meteor->scale = GetRandomValue(10, 25) / 10.0f;
	meteor->size = (Vector2){101 * meteor->scale, 84 * meteor->scale};
	meteor->hitBox = (Rectangle){meteor->pos.x + (HIT_BOX_GIVE / 2), meteor->pos.y + (HIT_BOX_GIVE / 2), meteor->size.x - HIT_BOX_GIVE, meteor->size.y - HIT_BOX_GIVE};
}

void MeteorExplosion(Explosion ***explosions, int *numberOfExplosions, Meteor meteor, Texture startingtex) {
	*explosions = realloc(*explosions, (*numberOfExplosions + 1) * sizeof(Explosion *));
	(*explosions)[*numberOfExplosions] = malloc(sizeof(Explosion));
	ExplosionInit((*explosions)[*numberOfExplosions], meteor, startingtex);
	(*numberOfExplosions)++;
}

void MeteorsUpdate(Meteor **meteor, float dt, Laser **lasers, int *numberOfLasers, Player *player, Explosion ***explosions, int *numberOfExplosions, Texture startingtex, Sound explosionSound) {
	for (int i = 0; i < NUMBER_OF_METEORS; i++) {
		meteor[i]->pos.y += meteor[i]->direction.y * meteor[i]->speed * dt;
		meteor[i]->hitBox = (Rectangle){meteor[i]->pos.x + (HIT_BOX_GIVE / 2), meteor[i]->pos.y + (HIT_BOX_GIVE / 2), meteor[i]->size.x - HIT_BOX_GIVE, meteor[i]->size.y - HIT_BOX_GIVE};

		if (meteor[i]->pos.y > GetScreenHeight()) {
			MeteorInit(meteor[i]);
		}

		if (CheckCollisionRecs(meteor[i]->hitBox, player->hitBox)) {
			player->isDead = true;
		}
		
		if (*numberOfLasers <= 0) {
			continue;
		}
		for (int j = 0; j < *numberOfLasers; j++) {
			if (lasers[j] == NULL) {
				continue;
			}
			if (CheckCollisionRecs(meteor[i]->hitBox, lasers[j]->hitBox)) {
				MeteorExplosion(explosions, numberOfExplosions, *meteor[i], startingtex);

                PlaySound(explosionSound);

				MeteorInit(meteor[i]);
				LaserDelete(lasers, j, &(*numberOfLasers));
				player->score++;
				j--;
			}
		}
	}
}