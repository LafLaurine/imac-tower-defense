#include <stdlib.h>
#include <stdio.h>
#include "../include/wave.h"

Wave* addMonster(Wave* wave, Monster myNewMonster){
	Wave* currentMonster = wave;
	Wave* newMonster;
	while(currentMonster != NULL && currentMonster->nextMonster != NULL){
		currentMonster = currentMonster->nextMonster;
	}
	newMonster = (Wave*)malloc(sizeof(Wave));
	if(newMonster == NULL){
		exit(EXIT_FAILURE);
	}
	newMonster -> monster = myNewMonster;
	newMonster -> nextMonster = NULL;
	if(currentMonster != NULL){
		currentMonster -> nextMonster = newMonster;
	}else{
		wave = newMonster;
	}
	return wave;
}