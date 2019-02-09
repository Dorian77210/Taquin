/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "generator.h"
#include "board.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void generateBoard(Board* board){
	srand((unsigned int)time(NULL));
	assert(board);
	unsigned int i, rand_pos, bx = board->size.x, by = board->size.y;

	for(i=0;i<3000;i++){ /*on fait tourner la boucle un grand nombre de fois pour s'assurer de bien melanger le taquin */
		rand_pos = (rand() % 4);
		if(rand_pos == Up){
			moveBlank(board, Up);
		} else if(rand_pos == Right){
			moveBlank(board, Right);
		} else if(rand_pos == Down){
			moveBlank(board, Down);
		} else if(rand_pos == Left){
			moveBlank(board, Left);
		}
	}
	Vector vec = getBlankPosition(board);
	for(i = 0; i <= vec.x; i++){
		moveBlank(board, Left);
	}
	for(i = 0 ; i < vec.y; i++){
		moveBlank(board, Up);
	}
}






