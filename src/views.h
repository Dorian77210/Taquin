/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef VIEWS_H
#define VIEWS_H

#include "board.h"
#include "game.h"

/*
 *
 */
void goGameView(SharedState* state);

/*
 *
 */
void goMainView(SharedState* state);

/*
 *
 */
void goSizeView(SharedState* state);

/*
 *
 */
void goImageView(SharedState* state);

/*
 *
 */
void goScoreView(SharedState* state);

#endif