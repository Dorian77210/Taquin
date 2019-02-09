/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "coordinate.h"

#include <assert.h>

Vector makeVector(int x, int y){
	Vector vec;
	
	vec.x = x;
	vec.y = y;
	
	return vec;
}

Rect makeRect(Vector corner, Vector size){
	Rect rect;
	
	rect.corner = corner;
	rect.size = size;
	
	return rect;
}

int coordToLinear(Vector position, size rect_x){
	assert(rect_x > 0U);
	
	return position.y * (int)rect_x + position.x;
}

Vector linearToCoord(int linear, size rect_x){
	Vector coord;
	
	assert(rect_x > 0U);
	
	coord.y = linear / rect_x;
	coord.x = linear % rect_x;
	
	return coord;
}

int intersect(Vector position, Rect rect){
	int x, y;
	int xx, yy;
	
	x = rect.corner.x;
	y = rect.corner.y;
	xx = x + rect.size.x;
	yy = y + rect.size.y;
	
	if(position.x >= x && position.y >= y && position.x <= xx && position.y <= yy)
		return 1;
	else
		return 0;
}

Vector addVector(Vector vec1, Vector vec2){
	Vector res;
	
	res.x = vec1.x + vec2.x;
	res.y = vec1.y + vec2.y;
	
	return res;
	
}

