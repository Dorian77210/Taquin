/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef SCORE_H
#define SCORE_H

#include "coordinate.h"

#define SAVE_FILE "save.dat"
#define MAX_SAVE 10

typedef struct{
	Vector board_size;
	unsigned int count;
	unsigned int score;
	unsigned long time; /*Microseconds*/
	unsigned long date;
} Score;

unsigned int computeScore(unsigned int count, unsigned int size_x, unsigned int size_y);

void storeScore(Score* score);

Score* loadScore(void);

void initialisationStruct(Score score[MAX_SAVE]);

int insertScore(Score* scores, const Score* input);

int isBestScore(const Score* scores, const Score* score);

#endif