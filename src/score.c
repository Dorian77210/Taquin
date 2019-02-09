/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "score.h"

unsigned int computeScore(unsigned int count, unsigned int size_x, unsigned int size_y){
	unsigned int x;
	unsigned int factor;

	if(count == 0) return 0;

	factor = size_x * size_y;

	assert(factor > 0);

	x = (factor * factor * factor) - count;
	x += 1;

	return x;
}

int insertScore(Score* scores, const Score* input){
	unsigned int i, j;

	assert(input);
	assert(scores);

	for(i = 0; i < MAX_SAVE; i++){
		if(input->score > scores[i].score){
			for(j = MAX_SAVE - 1; j > i; j--){
				scores[j] = scores[j - 1];
			}
			scores[i] = *input;

			if(i == 0) return 1;
			else return 0;
		}
	}
	return 0;
}
void initialiseScore(Score score[MAX_SAVE]){
	unsigned int i;

	for(i = 0; i < MAX_SAVE; i++){
		score[i].count = 0;
		score[i].time = 0;
	}
}

Score* loadScore(void){
	Score* score = NULL;
	Score score_buf;
	unsigned int i;
	size_t s;
	FILE* input = NULL;

	score = (Score*)malloc(MAX_SAVE * sizeof(Score));
	initialiseScore(score);

	input = fopen(SAVE_FILE, "r");
	if(input == NULL){
		return score;
	}

	for(i = 0; i < MAX_SAVE; i++){
		s = fread(&score_buf, sizeof(Score), 1, input);
		if(s != 1){
			return score;
		}

		score[i] = score_buf;
	}

	fclose(input);

	return score;
}
void storeScore(Score* score){
	unsigned int i;
	size_t s;
	FILE* output = NULL;

	assert(score);

	output = fopen(SAVE_FILE, "w");
	if(output == NULL){
		fprintf(stderr, "Failed to open the file: %s\n", SAVE_FILE);
		
		return;
	}

	for(i = 0; i < MAX_SAVE; i++){
		s = fwrite(&score[i], sizeof(Score), 1, output);
		if(s != 1){
			fprintf(stderr, "Failed to save score in file: %s\n", SAVE_FILE);

			return;
		}
	}

	fclose(output);
	free(score);
	score = NULL;
}

