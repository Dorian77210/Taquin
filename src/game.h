/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef GAME_H
#define GAME_H

#include "coordinate.h"
#include "image.h"
#include "score.h"

#define REFRESH_RATE 80

typedef enum {
	MainView,
	ImageView,
	SizeView,
	ScoreView,
	GameView,
	NoneView
} ViewState;

typedef struct {
	ViewState view_state;
	Vector board_size;
	char board_image[IMAGE_NAME_MAX];
	Vector image_size;
	Score* scores;
} SharedState;

/*
 *
 */
void startGame(void);

#endif