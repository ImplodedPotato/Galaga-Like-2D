#include "Player.h"

void PlayerInit(Player *player, int health) {
	player->health = health;
    player->isDead = false;
	player->speed = PLAYER_SPEED;
	player->score = 0;
	player->direction = (Vector2){0, 0};
	player->pos = (Vector2){GetScreenWidth() / 2, GetScreenHeight() / 3 * 2};
	player->sprite = LoadTexture("images/spaceship.png");
    player->hitBox = (Rectangle){player->pos.x + (HIT_BOX_GIVE / 2), player->pos.y + (HIT_BOX_GIVE / 2), 112 - HIT_BOX_GIVE, 75 - HIT_BOX_GIVE};
}

void PlayerUpdate(Player *player, float dt) {
	player->direction.x = bint(IsKeyDown(KEY_D)) - bint(IsKeyDown(KEY_A)) - (bint(IsKeyDown(KEY_LEFT)) - bint(IsKeyDown(KEY_RIGHT)));
	player->direction.y = bint(IsKeyDown(KEY_S)) - bint(IsKeyDown(KEY_W)) - (bint(IsKeyDown(KEY_UP)) - bint(IsKeyDown(KEY_DOWN)));

	player->direction = Vector2Normalize(player->direction);

	player->pos.x += player->direction.x * player->speed * dt;
	player->pos.y += player->direction.y * player->speed * dt;

	if (player->pos.x < 0) player->pos.x = 0;
    if (player->pos.x > GetScreenWidth() - 112) player->pos.x = GetScreenWidth() - 112;
    if (player->pos.y < 0) player->pos.y = 0;
    if (player->pos.y > GetScreenHeight() - 75) player->pos.y = GetScreenHeight() - 75;


    player->hitBox = (Rectangle){player->pos.x + (HIT_BOX_GIVE / 2), player->pos.y + (HIT_BOX_GIVE / 2), 112 - HIT_BOX_GIVE, 75 - HIT_BOX_GIVE};
}

void PlayerShoot(Player player, Laser ***lasers, int *numberOfLasers, Sound laserSound) {
	(*numberOfLasers)++;
	*lasers = realloc(*lasers, (*numberOfLasers) * sizeof(Laser *));
	(*lasers)[*numberOfLasers - 1] = malloc(sizeof(Laser));

	PlaySound(laserSound);

	LazerInit((*lasers)[*numberOfLasers - 1], player);
}