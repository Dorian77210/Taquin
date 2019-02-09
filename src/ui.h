/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef UI_H
#define UI_H

#include "coordinate.h"

typedef int key;
typedef unsigned int button;
typedef unsigned int image;

typedef struct {
	Rect rect;
	int id;
} Sprite;

typedef struct {
	Sprite sprite;
	button top;
	button down;
	button left;
	button right;
	char visible; 
} ButtonStorage;

typedef struct {
	Sprite sprite;
	char visible;
} ImageStorage;

typedef struct {
	ButtonStorage* buttons;
	ImageStorage* images;
	unsigned int nbr_buttons;
	unsigned int nbr_images;
	button focus_button;
} UI;

typedef enum {
	KeyboardEvent,
	MouseEvent
} EventType;

typedef struct {
	unsigned int id;
	EventType type;
	Vector mouse;
	key keyboard;
} Event;

/*
 *
 */
UI* createUI(void);
void destroyUI(UI* ui);

void drawUI(UI* ui);
Event waitEvent(UI* ui);

button addButton(UI* ui, char* texture, Vector size, Vector position);
image addImage(UI* ui, char* texture, Vector size, Vector position);

void setButtonVisible(UI* ui, button id, int visible);
void setImageVisible(UI* ui, image id, int visible);

void setButtonFocus(UI* ui, button id);

void bindButtonTop(UI* ui, button id, button link);
void bindButtonDown(UI* ui, button id, button link);
void bindButtonRight(UI* ui, button id, button link);
void bindButtonLeft(UI* ui, button id, button link);

#endif