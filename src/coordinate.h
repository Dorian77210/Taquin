/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef COORDINATE_H
#define COORDINATE_H

typedef unsigned int size;

typedef struct {
	int x;
	int y;
} Vector;

typedef struct {
	Vector corner;
	Vector size;
} Rect;

/*
 * @def : constructeur de vecteur
 *
 * @param x : composante x du vecteur
 * @param y : composante y du vecteur
 *
 * @return : retourne le nouveau vecteur
 */
Vector makeVector(int x, int y);

/*
 *
 */
Rect makeRect(Vector corner, Vector size);

/*
 * @def : convertis un système de coordonné 2D 
 *		en un système linéaire
 *
 * @param position : position à convertir
 * @pram rect_x : largeur du système 2D
 */
int coordToLinear(Vector position, size rect_x);

/*
 * @def : convertis une position linéaire en un système 2D
 *
 * @param position : la position linéaire à convertir
 * @pram rect_x : largeur du système 2D
 *
 * @param return : retourne la position dans un plan 2D
 */
Vector linearToCoord(int position, size rect_x);

/*
 * @def : permet de savoir si un position se trouve dans un rectangle
 *
 * @param position : coordonnées du point
 * @pram rect : rectangle de teste
 *
 * @return : retourne un booléen (0 ou 1) si le point se trouve dans le rectangle
 *		ou non.
 */
int intersect(Vector position, Rect rect);

/*
 *
 */
 Vector addVector(Vector vec1, Vector vec2);

#endif