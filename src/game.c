/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "views.h"
#include "window.h"
#include "coordinate.h"
#include "score.h"

void startGame(void){
	int running;
	SharedState shared_state;
	
	shared_state.view_state = MainView;
	shared_state.board_size = makeVector(4, 4);
	shared_state.scores = loadScore();
	
	createWindow();
	
	running = 1;	
	while(running){
		
		if(shared_state.view_state == MainView){
			goMainView(&shared_state);
		} else if(shared_state.view_state == ImageView){
			goImageView(&shared_state);
		} else if(shared_state.view_state == SizeView){
			goSizeView(&shared_state);
		} else if(shared_state.view_state == GameView){
			goGameView(&shared_state);
		} else if(shared_state.view_state == ScoreView){
			goScoreView(&shared_state);
		} else if(shared_state.view_state == NoneView){
			running = 0;
		}
		
	}

	storeScore(shared_state.scores);
	
	destroyWindow();
}