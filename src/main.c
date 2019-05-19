#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/image.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/node.h"
#include "../include/display.h"
#include "../include/game.h"
#include "../include/sprite.h"

/* Dimensions initiales et titre de la fenetre */
static unsigned int WINDOW_WIDTH = 500;
static unsigned int WINDOW_HEIGHT = 300;

static const char WINDOW_TITLE[] = "IMAC1 TOWER DEFENSE";


/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 40;
static const Uint32 FRAMERATE_MILLISECONDS_FAST = 1000 / 60;


void reshape() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0., 500., 300., 0.);
}

void init_window() {
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, 
            SDL_OPENGL  | SDL_RESIZABLE | SDL_DOUBLEBUF)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
}


int main (int argc, char* argv[])
{
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    init_window();
    reshape();
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapBuffers();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Initialisation du titre de la fenetre */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);

    if (argc > 0) {

        int play = 0;
        int help = 0;
        int monsterTypeInt = 0;

        // Textures et surfaces associées
        SDL_Surface* surface;
        
        // Map
        GLuint texture_map;
        SDL_Surface* s_map = NULL;

        // Help
        GLuint help_txt;
        SDL_Surface* help_surface = NULL;   

        GLuint tower_texture;

        // Init game
        Game *game = new_game();

     
        Map* map = init_map(argv[1]);
        //récup 1er noeud de la liste de noeud pour y positioner le monstre
        Node *root = map->list_node->head;
        Node *first = root;

        float monster_x = root->x;
        float monster_y = root->y;

        printf("Current root x %f\n", monster_x);
        //C'EST ICI QUE CA SEG FAULT 
       // printf("GROS BUG ICI JSP PQ %f\n", root->next->x);

        // Test check segment
        int x1, x2, y1, y2;
        x1 = 200; y1 = 200; x2 = 300; y2 = 100;
        
        if ((x2-x1) > (y2-y1)) {
            check_segment_X(x1, y1, x2, y2, map);
	    } else {
            check_segment_Y(x1, y1, x2, y2, map);
	    }


        // Create list monster
        List_Monster* l_monster = new_monster_list();

        //création monstre
        Monster_Type m_type = BACTERY;
        Monster* new_m = create_monster(m_type, monster_x, monster_y, root, 0);

        List_Monster* current_list = new_monster_list();
        current_list->m_first = new_m;
        current_list->nb_monsters = 1;
        current_list->nb_monsters_send = 1;

        // Création du tableau des listes de monstre
        Wave wave;
        wave.nb_lists = 1;
        wave.lists[wave.nb_lists - 1] = current_list;
        game->nb_lists_send = 1;

        printf("New monster x position %f\n", new_m->x);


        // Create list tower
        List_Tower* l_tower =  new_tower_list();
        TowerType draw_type_tower = -1;

        Tower* tower = NULL;

        s_map = load_sprite(map->img->path,&texture_map);
        help_surface = load_sprite("./images/aide.jpg", &help_txt);

        int loop = 1;

        while(loop) 
        {
            root = first;
            /* Recuperation du temps au debut de la boucle */
            Uint32 startTime = SDL_GetTicks();
            
            /* Placer ici le code de dessin */
            glClear(GL_COLOR_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);

             // Check map

            display_map(&texture_map);
        

            //Vague monstre

            monsterTypeInt = rand()%2;
            if(monsterTypeInt == 0) {
                m_type = BACTERY;
             }
            else {
                m_type = VIRUS;
            }
            Monster* newMonster = create_monster(m_type, monster_x, monster_y, root, game->nb_lists_send);
            // Nouvelle liste de monstre
            if(game->nb_lists_send < WAVENUMBER) {
                List_Monster* newList = new_monster_list();
                new_m = newMonster;
                newList->m_first = new_m;
                newList->nb_monsters = 1;
                newList->nb_monsters_send = 1;
                current_list = newList;
                wave.nb_lists += 1;
                game->nb_lists_send += 1;
                wave.lists[wave.nb_lists - 1] = current_list;
                }
            else if(current_list->nb_monsters_send < 10) {
            // Ajout du monstre à la liste actuelle
            new_m = add_monster(new_m, newMonster);
            wave.lists[wave.nb_lists - 1]->m_first = new_m;
            current_list->nb_monsters += 1;
            current_list->nb_monsters_send += 1;
            }


            /* ON ARRIVE A AVOIR DES VAGUES DE MONSTRES !
            printf("Monsters : %d\n", current_list->nb_monsters);*/

            if(help == 1){
                display_help(&help_txt);
            }

            //Affichage wave de monstres
            //display_wave(wave);

            //Affichage tours
            display_list_tower(l_tower);
            
            /* Echange du front et du back buffer : mise a jour de la fenetre */
            SDL_GL_SwapBuffers();
            
            /* Boucle traitant les evenements */
            SDL_Event e;
            while(SDL_PollEvent(&e)) 
            {
                /* L'utilisateur ferme la fenetre : */
                if(e.type == SDL_QUIT) 
                {
                    loop = 0;
                    break;
                }
        
                /* Quelques exemples de traitement d'evenements : */
                switch(e.type) 
                {
                    /* Redimensionnement fenetre */
                    case SDL_VIDEORESIZE:
                        WINDOW_WIDTH = e.resize.w;
                        WINDOW_HEIGHT = e.resize.h;
                        init_window();
                        break;

                    /* Clic souris */
                    case SDL_MOUSEBUTTONUP:
                        if(draw_type_tower != -1){
                            Tower* new_tower = create_tower(draw_type_tower, e.button.x, e.button.y, root, l_tower);
                            printf("clic en (%d)\n", draw_type_tower);
                            printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                        }
                        break;
                    
                    /* Touche clavier */
                    case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                            
                            case 'a' :
                                draw_type_tower = LASER;
                                break;
                            
                            case 'z' :
                                draw_type_tower = ROCKET;
                                break;

                            case 'p' :
                                if(play == 0)
                                    play = 1;
                                else
                                    play = 0;
                                break;
                            
                            case 'h' :
                            if(help == 0)
                            {
                                help = 1;
                            }
                            else {
                                help = 0;
                            }
                                break;

                                case 'q' : 
                                case SDLK_ESCAPE : 
                                loop = 0;
                                break;

                                default : break;
                        }
                        break;
                  
                    default:
                        break;
                }
            }

            /* Calcul du temps ecoule */
            Uint32 elapsedTime = SDL_GetTicks() - startTime;
            /* Si trop peu de temps s'est ecoule, on met en pause le programme */
            if(play == 0) {
                if(elapsedTime < FRAMERATE_MILLISECONDS) {
                    SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
                }
            }
            else if(play == 2) {
                if(elapsedTime < FRAMERATE_MILLISECONDS_FAST) {
                        SDL_Delay(FRAMERATE_MILLISECONDS_FAST - elapsedTime);
                }
            }
            
        }

        glDeleteTextures(1,&texture_map);
        game_end(game);
    }
    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();
    return EXIT_SUCCESS;
}