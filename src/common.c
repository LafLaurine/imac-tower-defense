#include <stdlib.h>
#include <stdio.h>
#include "../include/common.h"

int is_intersect(float x1, float y1, float x2, float y2, float radius){
	float distanceSquare = (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
	return distanceSquare < radius*radius*4;
}

int check_tower(Tower* t, List_Installation* list_inst){
	if(list_inst != NULL) {
		Installation* i = list_inst->i_first;
		
		while(i != NULL) {
			if(is_intersect(t->x, t->y, i->x, i->y, 34) == 1){
				printf("BONJOUR");
        		return 0;
			}
			i = i->i_next;
    	}
		return 1;
	}
	else {
		fprintf(stderr, "Installation not on constructible material\n");
		return 0;
	}
}