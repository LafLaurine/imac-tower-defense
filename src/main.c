#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/image.h"
#include "../include/map.h"
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
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

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


int main (int argc, char** argv)
{

    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
  
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_Surface* surface;
    init_window();
    reshape();
  
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapBuffers();

    /* Initialisation du titre de la fenetre */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);

    GLuint texture_map;
    GLuint texture_monster;
    // Check map
    Map* map = init_map("./data/map01.itd");
    SDL_Surface* s_map = load_sprite(map->img->path,&texture_map);
    SDL_Surface* s_monster = load_sprite("./images/monster.jpg", &texture_monster);
    printf("Texture map %d\n", texture_map);
    printf("Texture monstre %d\n", texture_monster);

    //Init game
    Game *game = new_game();

    //Create NODE
    List_Node* list_node = new_List_Node();
    add_node(list_node, 10, 10);

    // Test check segment
    //check_segment(300, 100, 450, 100, map);

    // Create monster
    List_Monster* l_monster = new_monster_list();
    Monster* m = malloc(sizeof(Monster));
    m = create_monster(l_monster, m, 100, 100, 10, VIRUS, ROCKET, 20, 10, list_node->head);
    game_update(game, m);
    player_money_update(game,50);

    printf("Player money : %d\n", game->money);

/*  // Create tower
    Tower* t = malloc(sizeof(Tower));
    t = create_tower(t, LASER, 50, 20, 20, 10, 5, 20, list_node->head);
    printf("%d", t->range);
*/

    //kill_monster(l_monster, m);
    int loop = 1;

    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        display_map(&texture_map);
        display_path(map);
        
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

            /* L'utilisateur ferme la fenetre : */
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }
        
            if( e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
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
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    break;
                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    //printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    break;
                    
                default:
                    break;
            }
        }

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    glDeleteTextures(1,&texture_map);
    game_end(game);
    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();
    return EXIT_SUCCESS;
}