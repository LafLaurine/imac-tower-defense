#ifndef MONSTER_H__
#define MONSTER_H__

#include "node.h"
#include "tower.h"

#define WAVENUMBER 10

// Enum type monster
typedef enum {
	BACTERY, VIRUS
} Monster_Type;

// Monster
typedef struct Monster {
	float x; // x Position
	float y; // y Position
	Node* node_next; // Next node (map)
	int pv; // Life points (current)
	int pv_max; // Max life points
	int move; // Movement
	int speed; // Speed
	int money; // Money it costs - gives
	Monster_Type type; // Type
	int resist; // Resistance
	struct Monster* m_next; // Next monster
	struct Monster* m_prev; // Previous monster
} Monster;

// List monster
typedef struct List_Monster {
	Monster* m_first;
	Monster* m_last;
	int nb_monsters; // Nb monster into list
	int nb_monsters_send; // Nb monster already sent
} List_Monster;

// Wave
typedef struct Wave {
	List_Monster* lists[WAVENUMBER];
	int nb_lists;
} Wave;

// Create new monster list
List_Monster* new_monster_list();
// Create new monster
Monster* create_monster(Monster_Type type, float x, float y, Node *node_next, List_Monster* l_monster);
// Add monster to list
void add_monster_list(Monster* m, List_Monster* list_monster);
// Kill monster
Monster_Type kill_monster(List_Monster* list_monster, Monster* current);
// Remove monster
List_Monster* remove_monster(List_Monster* current_m, Monster* current);
// Free all monster from list
void free_all_monster(List_Monster* l_monster);

#endif