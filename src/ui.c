/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "ui.h"
#include "window.h"

#include <assert.h>
#include <stdlib.h>
#include <graph.h>
#include <unistd.h>

UI* createUI(void){
	UI* ui = NULL;

	ui = (UI*)malloc(sizeof(UI));
	assert(ui);
	ui->images = (ImageStorage*)malloc(sizeof(ImageStorage));
	assert(ui->images);
	ui->buttons = (ButtonStorage*)malloc(sizeof(ButtonStorage));
	assert(ui->buttons);
	ui->nbr_buttons = 0;
	ui->nbr_images = 0;
	ui->focus_button = 0;

	return ui;
}
void destroyUI(UI* ui){
	unsigned int i;

	assert(ui);

	for(i = 0; i < ui->nbr_buttons; i++){
		LibererSprite(ui->buttons[i].sprite.id);
	}
	for(i = 0; i < ui->nbr_images; i++){
		LibererSprite(ui->images[i].sprite.id);
	}

	free(ui->images);
	free(ui->buttons);
	free(ui);
}

void drawUI(UI* ui){
	unsigned int i;
	ButtonStorage* button = NULL;

	assert(ui);

	for(i = 0; i < ui->nbr_buttons; i++){
		button = &ui->buttons[i];

		if(button->visible){
			AfficherSprite(button->sprite.id, button->sprite.rect.corner.x, button->sprite.rect.corner.y);

			if(ui->focus_button == (i + 1)){
				ChoisirCouleurDessin(0x000000);
				DessinerRectangle(button->sprite.rect.corner.x, button->sprite.rect.corner.y, button->sprite.rect.size.x, button->sprite.rect.size.y);
			}
		}
	}

	for(i = 0; i < ui->nbr_images; i++){
		if(ui->images[i].visible)
			AfficherSprite(ui->images[i].sprite.id, ui->images[i].sprite.rect.corner.x, ui->images[i].sprite.rect.corner.y);
	}
}
Event waitEvent(UI* ui){
	Event event;
	unsigned int i;

	assert(ui);

	event.id = 0;
	while(1){
		if(SourisCliquee()){
			event.type = MouseEvent;
			event.mouse = getMousePosition();

			for(i = 0; i < ui->nbr_buttons; i++){
				if(intersect(event.mouse, ui->buttons[i].sprite.rect)){
					event.id = i + 1; /*ID = pos + 1*/
				}
			}

			return event;

		} else if(ToucheEnAttente()){
			event.type = KeyboardEvent;
			event.keyboard = Touche();

			if(event.keyboard == XK_Up){
				if(!ui->focus_button){
					if(ui->nbr_buttons > 0) ui->focus_button = 1;
				} else{
					if(ui->buttons[ui->focus_button - 1].top) ui->focus_button = ui->buttons[ui->focus_button - 1].top;
				}
			} else if(event.keyboard == XK_Down){
				if(!ui->focus_button){
					if(ui->nbr_buttons > 0) ui->focus_button = 1;
				} else{
					if(ui->buttons[ui->focus_button - 1].down) ui->focus_button = ui->buttons[ui->focus_button - 1].down;
				}
			} else if(event.keyboard == XK_Right){
				if(!ui->focus_button){
					if(ui->nbr_buttons > 0) ui->focus_button = 1;
				} else{
					if(ui->buttons[ui->focus_button - 1].right) ui->focus_button = ui->buttons[ui->focus_button - 1].right;
				}
			} else if(event.keyboard == XK_Left){
				if(!ui->focus_button){
					if(ui->nbr_buttons > 0) ui->focus_button = 1;
				} else{
					if(ui->buttons[ui->focus_button - 1].left) ui->focus_button = ui->buttons[ui->focus_button - 1].left;
				}
			} else if(event.keyboard == XK_Return){
				if(ui->focus_button){
					event.id = ui->focus_button;
				}
			}

			return event;
		}

		usleep(200);
	}
}

button addButton(UI* ui, char* texture, Vector size, Vector position){
	assert(ui);

	ui->buttons = (ButtonStorage*)realloc(ui->buttons, (ui->nbr_buttons + 1) * sizeof(ButtonStorage));
	assert(ui->buttons);

	ui->buttons[ui->nbr_buttons].sprite.rect.corner = position;
	ui->buttons[ui->nbr_buttons].sprite.rect.size = size;
	ui->buttons[ui->nbr_buttons].sprite.id = ChargerSprite(texture);
	ui->buttons[ui->nbr_buttons].visible = 1;
	ui->buttons[ui->nbr_buttons].top = 0;
	ui->buttons[ui->nbr_buttons].down = 0;
	ui->buttons[ui->nbr_buttons].left = 0;
	ui->buttons[ui->nbr_buttons].right = 0;

	ui->nbr_buttons++;

	/*ID = pos + 1*/
	return (ui->nbr_buttons);
}
image addImage(UI* ui, char* texture, Vector size, Vector position){
	assert(ui);

	ui->images = (ImageStorage*)realloc(ui->images, (ui->nbr_images + 1) * sizeof(ImageStorage));
	assert(ui->images);

	ui->images[ui->nbr_images].sprite.rect.corner = position;
	ui->images[ui->nbr_images].sprite.rect.size = size;
	ui->images[ui->nbr_images].sprite.id = ChargerSprite(texture);
	ui->images[ui->nbr_images].visible = 1;

	ui->nbr_images++;

	return (ui->nbr_images);
}

void setButtonFocus(UI* ui, button id){
	assert(ui);
	ui->focus_button = id;
}

void setButtonVisible(UI* ui, button id, int visible){
	assert(ui);
	assert(id);
	ui->buttons[id - 1].visible = visible;
}
void setImageVisible(UI* ui, image id, int visible){
	assert(ui);
	assert(id);
	ui->images[id - 1].visible = visible;
}

void bindButtonTop(UI* ui, button id, button link){
	assert(ui);
	assert(id);
	ui->buttons[id - 1].top = link;
}
void bindButtonDown(UI* ui, button id, button link){
	assert(ui);
	assert(id);
	ui->buttons[id - 1].down = link;
}
void bindButtonRight(UI* ui, button id, button link){
	assert(ui);
	assert(id);
	ui->buttons[id - 1].right = link;
}
void bindButtonLeft(UI* ui, button id, button link){
	assert(ui);
	assert(id);
	ui->buttons[id - 1].left = link;
}