#ifndef WAVE_H
#define WAVE_H
#define WAVESIZE 10;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "monster.h"
#include "node.h"

typedef struct Wave{
  int wave_id;
  float begin_time;
  float freq;
  float random;
  //time between monsters in 1 wave
  float time_between;
  int monster_total;
  Monster_Type type;
  Wave* next;
};


int lauch_waves(Map* map, float timer);

#endif
