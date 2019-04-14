#include <stdlib.h>
#include <stdio.h>
#include "../include/monster.h"

Monster* create_monster(Monster* m, int pv, int speed, int money){
	m->pv = pv;
	m->speed = speed;
	m->money = money;
	return m;
}

Monster* set_position(Monster* m, float x, float y){
	m->x = x;
	m->y = y;
	return m;
}

Monster* set_pv(Monster* m, int pv){
	m->pv = pv;
	return m;
}