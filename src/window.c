/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "window.h"

#include <graph.h>
#include <unistd.h>

void createWindow(void){
	InitialiserGraphique();
	CreerFenetre(200, 100, SCREEN_X, SCREEN_Y);
	ChoisirTitreFenetre("Taquin");
	ChoisirCurseur(3);
}

void destroyWindow(void){
	FermerGraphique();
}

void startDraw(void){
	ChoisirEcran(1);
	EffacerEcran(SCREEN_COLOR);
}

void stopDraw(void){
	CopierZone(1, 0, 0, 0, SCREEN_X, SCREEN_Y, 0, 0);
}

Vector getMousePosition(void){
	Vector mouse_pos;
	
	SourisPosition();
	
	mouse_pos.x = _X;
	mouse_pos.y = _Y;
	
	return mouse_pos;
}

void waitMouseEvent(void){
	while(!SourisCliquee()) usleep(200);
}

