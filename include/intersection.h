#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "geometry/Point2D.h"
#include "geometry/Vector2D.h"

//Vérifie s'il y a une intersection entre un point et un segment
int intersection_point_segment (Point2D, Point2D, Point2D);
//Vérifie s'il y a une intersection entre deux segments
int intersection_segments (Point2D, Point2D, Point2D, Point2D);
//Vérifie s'il y a une intersection entre un cercle et un segment
int intersection_segment_cercle (Point2D, Point2D, Point2D, float);
//Vérifie s'il y a une intersection entre deux carrés
int intersection_carres (Point2D, Point2D, Point2D, Point2D);
//Vérifie s'il y a une intersection entre un carré et un disque
int intersection_carre_disque (Point2D, Point2D, float, Point2D);

#endif