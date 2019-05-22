#include <stdlib.h>
#include <stdio.h>
#include "../include/common.h"

int is_intersect(float x1, float y1, float x2, float y2, float radius){
	float distanceSquare = (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
	return distanceSquare < radius*radius*4;
}

int check_around_tower(Tower* t, List_Installation* list_inst){

	if(list_inst != NULL) {
		Installation* i = list_inst->i_first;
		
		while(i != NULL) {
			if(is_intersect(t->x, t->y, i->x, i->y, 34+t->range) == 1){
				update_tower(t, i->type);
			}
			i = i->i_next;
    	}
		return 0;
	}
	else {
		fprintf(stderr, "Installation not on constructible material\n");
		return 0;
	}
}

int check_around_inst(Installation* i, List_Tower* list_tower){

	if(list_tower != NULL) {
		Tower* t = list_tower->t_first;
		
		while(t != NULL) {
			if(is_intersect(i->x, i->y, t->x, t->y, 34+t->range)){
				update_tower(t, i->type);
			}
			t = t->t_next;
    	}
		return 0;
	}
	else {
		fprintf(stderr, "Installation not on constructible material\n");
		return 0;
	}
}

void update_tower(Tower* t, InstallationType type_inst){
	if(type_inst == 0){
		t->range += (t->range)*0.25;
	} else if(type_inst == 1) {
		t->power += (t->power)*0.25;
	} else {
		t->rate += (t->rate)*0.25;		
	}
}