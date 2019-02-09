/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "image.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

Image* createImage(const char* file_name, size x, size y, size cut_x, size cut_y){
	Image* image = NULL;
	unsigned int i, j;
	unsigned int tile_x, tile_y;
	
	assert(x > 0U && y > 0U && cut_x > 0U && cut_y > 0U);
	
	image = (Image*)malloc(sizeof(Image));
	assert(image != NULL);
	
	image->uvs = (Rect*)malloc(cut_x * cut_y * sizeof(Rect));
	assert(image->uvs != NULL);
	
	strncpy(image->texture_name, file_name, IMAGE_NAME_MAX);
	
	tile_x = x / cut_x;
	tile_y = y / cut_y;
	for(j = 0U; j < cut_y; j++){
		for(i = 0U; i < cut_x; i++){
			image->uvs[j * cut_x + i] = makeRect(makeVector(i * tile_x, j * tile_y), makeVector(tile_x, tile_y));
		}
	}
	
	return image;
}

void destroyImage(Image* image){
	free(image->uvs);
	free(image);
}

const char* getImageName(const Image* image){
	assert(image != NULL);
	return image->texture_name;
}

Vector getTileSize(const Image* image){	
	assert(image != NULL);
	return image->uvs[0].size;
}

