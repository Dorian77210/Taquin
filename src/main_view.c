/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "views.h"
#include "board.h"
#include "coordinate.h"
#include "window.h"
#include "ui.h"
#include "textures_def.h"

#include <graph.h>
#include <stdio.h>
#include <unistd.h>

void goMainView(SharedState* state){
	int running;
	UI* ui = NULL;
	Event event;
	button play_button;
	button quit_button;
	button score_button;
	
	ui = createUI();
	play_button = addButton(ui, IMG_BUTTON_PLAY_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector(500 - (IMG_BUTTON_X / 2), 200));
	score_button = addButton(ui, IMG_BUTTON_SCORE_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector(500 - (IMG_BUTTON_X / 2), 320));
	quit_button = addButton(ui, IMG_BUTTON_QUIT_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector(500 - (IMG_BUTTON_X / 2), 420));
	
	bindButtonDown(ui, play_button, score_button);
	bindButtonTop(ui, score_button, play_button);
	bindButtonDown(ui, score_button, quit_button);
	bindButtonTop(ui, quit_button, score_button);

	startDraw();
	ChargerImageFond(IMG_BACKGROUND_PATH);
	drawUI(ui);
	stopDraw();
	
	running = 1;
	while(running){

		event = waitEvent(ui);

		if(event.id == play_button){
			running = 0;
			state->view_state = ImageView;
		} else if(event.id == score_button){
			running = 0;
			state->view_state = ScoreView;
		} else if(event.id == quit_button){
			running = 0;
			state->view_state = NoneView;
		}

		startDraw();
		ChargerImageFond(IMG_BACKGROUND_PATH);
		drawUI(ui);
		stopDraw();
	}
	
	destroyUI(ui);
}