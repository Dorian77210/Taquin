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
#include "score.h"

#include <unistd.h>
#include <graph.h>
#include <stdio.h>

void drawScoreScene(UI* ui, SharedState* state){
	char buf[50];
	Score* ptr = NULL;
	unsigned int i, y;

	startDraw();
	ChargerImageFond(IMG_BACKGROUND_PATH);
	drawUI(ui);

	ptr = state->scores;
	ChoisirCouleurDessin(0x290d00);
	y = 100;
	for(i = 0; i < MAX_SAVE; i++){

		if(ptr[i].score != 0 || ptr[i].count != 0 || ptr[i].time != 0){
			snprintf(buf, 50, "%u. %upts %ucoups %us %ux%u", i + 1, ptr[i].score, ptr[i].count, (unsigned int)(ptr[i].time / 1000000), (unsigned int)ptr[i].board_size.x, (unsigned int)ptr[i].board_size.y);
			EcrireTexte(SCREEN_X / 2 - TailleChaineEcran(buf, 2) / 2, y, buf, 2);
		} else{
			snprintf(buf, 50, "-----");
			EcrireTexte(SCREEN_X / 2 - TailleChaineEcran(buf, 2) / 2, y, buf, 2);
		}
		
		y += 40;
	}

	stopDraw();
}

void goScoreView(SharedState* state){
	int running;
	UI* ui = NULL;
	Event event;
	button back_button;

	ui = createUI();
	back_button = addButton(ui, IMG_BUTTON_BACK_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector((SCREEN_X / 2) - (IMG_BUTTON_X / 2), 550));

	drawScoreScene(ui, state);

	running = 1;
	while(running){

		event = waitEvent(ui);

		if(event.id == back_button){
			running = 0;
			state->view_state = MainView;
		}

		drawScoreScene(ui, state);

	}

	destroyUI(ui);
}