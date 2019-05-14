#include <stdlib.h>
#include <stdio.h>

int lauch_waves(Map* map, float timer){
  int restMonster = 0;

  Wave* currentWave = malloc(sizeof(Wave));

  currentWave = mapdata->listWaves->next;

  while(currentWave != NULL) {
    restMonster = restMonster + currentWave->monster_total;
    if(currentWave->timeBegin*1000 < timer) {
    }
    currentWave = currentWave->next;
  }

  /* La vague est terminée */
  if(restMonster == 0) {
    return 1;
  }
  return 0;
}
