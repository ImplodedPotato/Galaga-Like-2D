#include "resource_dir.h"
#include "raymath.h"
#include "Settings.h"
#include "fun.h"
#include "Player.h"
#include "Laser.h"
#include "Meteor.h"
#include "Explosion.h"
#include "Timer.h"
#include "Star.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

typedef struct Game {
	Player player;
	Laser **lasers;
	int numberOfLasers;
	Meteor **meteors;
	Explosion **explosions;
	int numberOfExplosions;
	Star **stars;
	Music music;
	Sound laserSound;
	Sound explosionSound;
	Font font;
	Texture las;
	Texture meteorTex;
	Texture starTex;
	Texture explosionTex[28];
	bool debugMode;
} Game;

void UpdateDrawFrame(void *args);

int main() {
	SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Galaga-Like-2D");
	InitAudioDevice();
	SearchAndSetResourceDir("resources");

	Game game;
	game.player = (Player) {0};
	game.lasers = NULL;
	game.numberOfLasers = 0;
	game.meteors = NULL;
	game.explosions = NULL;
	game.numberOfExplosions = 0;
	game.stars = NULL;
	game.music = LoadMusicStream("audio/music.wav");
	game.laserSound = LoadSound("audio/laser.wav");
	game.explosionSound = LoadSound("audio/explosion.wav");
	game.font = LoadFont("font/Stormfaze.otf");
	game.las = LoadTexture("images/laser.png");
	game.meteorTex = LoadTexture("images/meteor.png");
	game.starTex = LoadTexture("images/star.png");
	for (size_t i = 0; i < 28; i++) {
		game.explosionTex[i] = LoadTexture(TextFormat("images/explosion/%d.png", i + 1));
	}
	PlayerInit(&game.player, 5);
	StarsCreate(&game.stars);
	game.meteors = malloc(NUMBER_OF_METEORS * sizeof(Meteor *));
	for (int i = 0; i < NUMBER_OF_METEORS; i++) {
		game.meteors[i] = (Meteor *)malloc(sizeof(Meteor));
		MeteorInit(game.meteors[i]);
	}
	game.debugMode = IS_DEBUG;
	PlayMusicStream(game.music);

	#if defined(PLATFORM_WEB)
		emscripten_set_main_loop_arg(UpdateDrawFrame, &game, 0, 1);
	#else

	while (!WindowShouldClose()) {
		UpdateDrawFrame(&game);
	}

	#endif

	for (int i = 0; i < NUMBER_OF_METEORS; i++) {
		free(game.meteors[i]); // Free each Meteor
	}
	free(game.meteors);
	for (int i = 0; i < game.numberOfLasers; i++) {
        free(game.lasers[i]);  // Free each laser
    }
	free(game.lasers);
	UnloadTexture(game.player.sprite);
	UnloadTexture(game.las);
	UnloadTexture(game.meteorTex);
	UnloadTexture(game.starTex);
	for (int i = 0; i < 28; i++) {
		UnloadTexture(game.explosionTex[i]);
	}
	UnloadFont(game.font);
	UnloadMusicStream(game.music);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}

void UpdateDrawFrame(void *arg) {
	Game *game = (Game *)arg;
	UpdateMusicStream(game->music);

        float dt = GetFrameTime();

        if (!game->player.isDead) {
            PlayerUpdate(&game->player, dt);
            LasersUpdate(game->lasers, &game->numberOfLasers, dt);
            MeteorsUpdate(game->meteors, dt, game->lasers, &game->numberOfLasers, &game->player, &game->explosions, &game->numberOfExplosions, game->explosionTex[0], game->explosionSound);
            ExplosionsUpdate(game->explosions, &game->numberOfExplosions, dt, game->explosionTex);

            if (IsKeyPressed(KEY_SPACE)) {
                PlayerShoot(game->player, &game->lasers, &game->numberOfLasers, game->laserSound);
            }
        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                PlayerInit(&game->player, 5);
                for (int i = 0; i < NUMBER_OF_METEORS; i++) {
                    MeteorInit(game->meteors[i]);
                }
                int newNumberOfLasers = game->numberOfLasers;
                for (int i = 0; i < newNumberOfLasers; i++, game->numberOfLasers--) {
                    game->lasers[i] = NULL;
                    free(game->lasers[i]);
                }
                
                StarsCreate(&game->stars);
            }
        }

        if (IsKeyPressed(KEY_GRAVE)) {
            game->debugMode = !game->debugMode;
        }

    BeginDrawing();
        ClearBackground(BG_COLOR);

        for (int i = 0; i < NUMBER_OF_STARS; i++) {
            DrawTextureEx(game->starTex, game->stars[i]->pos, 0, game->stars[i]->scale, WHITE);
        }
        

        for (int i = 0; i < game->numberOfLasers; i++) {
            DrawTextureV(game->las, game->lasers[i]->pos, WHITE);
            if (game->debugMode) {
                DrawRectangleLinesEx(game->lasers[i]->hitBox, 1, RED);
            }
        }
        for (int i = 0; i < game->numberOfExplosions; i++) {
            DrawTextureEx(game->explosions[i]->tex, game->explosions[i]->pos, 0, game->explosions[i]->scale * 2, WHITE);
        }
        
        for (int i = 0; i < NUMBER_OF_METEORS; i++) {
            DrawTextureEx(game->meteorTex, game->meteors[i]->pos, 0, game->meteors[i]->scale, WHITE);
            if (game->debugMode) {
                DrawRectangleLinesEx(game->meteors[i]->hitBox, 1, RED);
            }
        }

        DrawTextureV(game->player.sprite, game->player.pos, WHITE);
        if (game->debugMode) {
            DrawRectangleLinesEx(game->player.hitBox, 1, RED);
        }

        DrawTextEx(game->font, TextFormat("Socre: %d", game->player.score), (Vector2){GetScreenWidth() / 2 - 100, GetScreenHeight() / 6}, 50, 0, WHITE);

        if (game->player.isDead) {
            DrawTextEx(game->font, "Game Over", (Vector2){GetScreenWidth() / 2 - 175, GetScreenHeight() / 3}, 75, 0, RED);
            DrawTextEx(game->font, "Press Return to Restart", (Vector2){GetScreenWidth() / 2 - 275, GetScreenHeight() / 2}, 50, 0, WHITE);
        }

        DrawFPS(0, 0);

        EndDrawing();
}