/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "views.h"
#include "board.h"
#include "coordinate.h"
#include "window.h"
#include "generator.h"
#include "ui.h"
#include "score.h"
#include "textures_def.h"

#include <unistd.h>
#include <graph.h>
#include <stdio.h>
#include <assert.h>

void drawGameScene(const char* background, Board* board, Image* board_image, UI* ui, unsigned int count){
	char buf[10];

	ChargerImageFond(IMG_BACKGROUND_PATH);
	drawBoard(board, board_image);

	drawUI(ui);

	snprintf(buf, 10,"%u", count);
	EcrireTexte(10 + (IMG_PLATE_X / 2) - (TailleChaineEcran(buf, 2) / 2), 20 + (IMG_PLATE_Y / 2), buf, 2);
}
void drawGameEnd(int won, int new_record, Score* score){
	char buf[30];

	assert(score);

	if(won){
		EcrireTexte(SCREEN_X / 2 - (TailleChaineEcran("Victoire !", 2) / 2), SCREEN_Y / 2 - 40, "Victoire !", 2);

		snprintf(buf, 30, "Score: %upts", score->score);
		EcrireTexte(SCREEN_X / 2 - (TailleChaineEcran(buf, 2) / 2), SCREEN_Y / 2 + 35, buf, 2);

		if(new_record){
			ChoisirCouleurDessin(CouleurParComposante(230, 0, 0));
			snprintf(buf, 30, "Nouveau record !");
			EcrireTexte(SCREEN_X / 2 - (TailleChaineEcran(buf, 2) / 2), SCREEN_Y / 2 + 80, buf, 2);
			ChoisirCouleurDessin(0x290d00);
		}
		
	} else{
		EcrireTexte(SCREEN_X / 2 - (TailleChaineEcran("Abandon !", 2) / 2), SCREEN_Y / 2 - 40, "Abandon !", 2);
	}

	snprintf(buf, 30, "Nombre de coups: %u", score->count);
	EcrireTexte(SCREEN_X / 2 - (TailleChaineEcran(buf, 2) / 2), SCREEN_Y / 2 - 15, buf, 2);
	snprintf(buf, 30, "Temps: %us", (unsigned int)(score->time / 1000000));
	EcrireTexte(SCREEN_X / 2 - (TailleChaineEcran(buf, 2) / 2), SCREEN_Y / 2 + 10, buf, 2);
}

void goGameView(SharedState* state){
	int running;
	int win;
	int new_record;
	BoardInput answer;
	unsigned long time_start;
	Board* board;
	Image* board_image;

	UI* ui = NULL;
	Event event;

	button giveup_button;
	button retry_button;
	button quit_button;
	image countplate;
	image endplate;

	Score score;

	ui = createUI();
	
	giveup_button = addButton(ui, IMG_BUTTON_GIVEUP_PATH, makeVector(IMG_BUTTON_GIVEUP_X, IMG_BUTTON_GIVEUP_Y), makeVector((SCREEN_X / 2) - (IMG_BUTTON_GIVEUP_X / 2), SCREEN_Y - 40));
	countplate = addImage(ui, IMG_PLATE_PATH, makeVector(IMG_PLATE_X, IMG_PLATE_Y), makeVector(10, 10));
	board_image = createImage(state->board_image, state->image_size.x, state->image_size.y, state->board_size.x, state->board_size.y);
	board = createBoard(board_image, state->board_size.x, state->board_size.y, (SCREEN_X / 2) - (state->image_size.x / 2), (SCREEN_Y / 2) - (state->image_size.y / 2), 1, 1);
	generateBoard(board);

	score.count = 0;
	win = 0;
	running = 1;

	time_start = Microsecondes();

	startDraw();
	drawGameScene(IMG_BACKGROUND_PATH, board, board_image, ui, score.count);
	stopDraw();

	while(running){

		event = waitEvent(ui);
		handleInput(board, &event, &score.count);
		
		startDraw();
		drawGameScene(IMG_BACKGROUND_PATH, board, board_image, ui, score.count);
		stopDraw();

		if(isBoardCorrect(board)){
			running = 0;
			win = 1;
		}

		if(event.type == KeyboardEvent && event.keyboard == XK_Escape || event.id == giveup_button){
			running = 0;
			win = 0;
		}
	}

	/*END GAME*/
	score.board_size = state->board_size;
	score.time = Microsecondes() - time_start;
	score.score = computeScore(score.count, (unsigned int)state->board_size.x, (unsigned int)state->board_size.y);

	

	retry_button = addButton(ui, IMG_BUTTON_RETRY_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector(SCREEN_X / 2 - (IMG_BUTTON_X / 2) + 90, SCREEN_Y - 200));
	quit_button = addButton(ui, IMG_BUTTON_QUIT_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector(SCREEN_X / 2 - (IMG_BUTTON_X / 2) - 90, SCREEN_Y - 200));
	endplate = addImage(ui, IMG_ENDPLATE_PATH, makeVector(IMG_ENDPLATE_X, IMG_ENDPLATE_Y), makeVector(SCREEN_X / 2 - (IMG_ENDPLATE_X / 2), SCREEN_Y / 2 - (IMG_ENDPLATE_Y / 2)));

	bindButtonLeft(ui, retry_button, quit_button);
	bindButtonRight(ui, quit_button, retry_button);

	setButtonFocus(ui, retry_button);
	setButtonVisible(ui, giveup_button, 0);

	startDraw();
	drawGameScene(IMG_BACKGROUND_PATH, board, board_image, ui, score.count);
	if(win){
		/*Ajouter le score dans le tableau des scores seulement lorsque le joueur a gagné*/
		new_record = insertScore(state->scores, &score);
		drawGameEnd(1, new_record, &score);
	} else{
		drawGameEnd(0, 0, &score);
	}
	stopDraw();

	running = 1;
	while(running){

		event = waitEvent(ui);

		if(event.id == retry_button){
			state->view_state = GameView;
			running = 0;
		} else if(event.id == quit_button){
			state->view_state = MainView;
			running = 0;
		}

		startDraw();
		drawGameScene(IMG_BACKGROUND_PATH, board, board_image, ui, score.count);
		if(win){
			drawGameEnd(1, new_record, &score);
		} else{
			drawGameEnd(0, 0, &score);
		}
		stopDraw();
	}
	
	destroyUI(ui);
	destroyBoard(board);
	destroyImage(board_image);
}