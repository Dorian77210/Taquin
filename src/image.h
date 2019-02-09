/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef IMAGE_H
#define IMAGE_H

#include "coordinate.h"

#define IMAGE_NAME_MAX 30

typedef struct {
	Rect* uvs;
	char texture_name[IMAGE_NAME_MAX];
} Image;

/*
 *
 */
Image* createImage(const char* file_name, size x, size y, size cut_x, size cut_y);

/*
 *
 */
void destroyImage(Image* image);

const char* getImageName( const Image* image);

Vector getTileSize(const Image* image);



#endif