#ifndef TOWER
#define TOWER

typedef enum{
	LASER, ROCKET, ELECTRIC, WATER
}TowerType;


typedef struct Tower {

	//position
	float x;
	float y;
	//Type de la tour
	char* tower_type;
	//cadence 
	int rate;
    //puissance de tir de la tour
	int power;
    //porté de la tour
	int range;
	//cout de la tour
	int cost;
}Tower;

#endif