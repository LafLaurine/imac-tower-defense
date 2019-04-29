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
#include "../include/game.h"
/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 500;
static const unsigned int WINDOW_HEIGHT = 500;
static const char WINDOW_TITLE[] = "IMAC1 TOWER DEFENSE";
/* Espace fenetre virtuelle */
static const float GL_VIEW_WIDTH = 50.;
static const float GL_VIEW_HEIGHT = 50.;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{
    SDL_Surface* surface_temp = SDL_SetVideoMode(   
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    if(NULL == surface_temp) 
    {
        fprintf(
            stderr, 
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;
    glViewport(0, 0, (*surface)->w, (*surface)->h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(
        -GL_VIEW_WIDTH / 2, GL_VIEW_WIDTH / 2, 
        -GL_VIEW_HEIGHT / 2, GL_VIEW_HEIGHT / 2);
}


int is_loaded(SDL_Surface *image)
{
    if(image == NULL) {
        printf("%s\n", "Image not loaded");
        SDL_Quit();
        return 0;
    }
    printf("%s\n", "Image loaded");
    return 1;
}


void drawQuad(GLuint texture) {
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);        
        glBegin(GL_QUADS);
            glTexCoord2f(0, 1);
            glVertex2f(-0.5,-0.5);
            glTexCoord2f(0, 0);
            glVertex2f(-0.5,0.5);
            glTexCoord2f(1, 0);
            glVertex2f(0.5,0.5);
            glTexCoord2f(1, 1);
            glVertex2f(0.5,-0.5);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

GLuint texture_image;


int main (int argc, char** argv)
{
	
    // Check map
    Map* map = init_map("./data/map01.itd");
    Image *img = read_image("./images/map01.ppm");
    unsigned char* pixels;
    Color3f path;

    //Init game
    Game *game = new_game();

    //Create NODE
    List_Node* list_node = new_List_Node();
    add_node(list_node, 10, 10);

    // Create monster
    Monster* m = malloc(sizeof(Monster));
    m = create_monster(m, 100, 50, Monster_1, 20, 10, list_node->head);
    game_update(game, m);
    update_player(game,20);
    //change_path_color(img,pixels,map,path,255,255,255); 

    printf("%d\n", game->player_life);

/*
    



    // Create tower
    Tower* t = malloc(sizeof(Tower));
    t = create_tower(t, LASER, 50, 20, 20, 10, 5, 20, list_node->head);
    printf("%d", t->range);
*/
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
  
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_Surface* surface;
    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);

    /* Initialisation du titre de la fenetre */
	SDL_WM_SetCaption(WINDOW_TITLE, NULL);


    //IMG_Load(map->img->path)
	SDL_Surface *image = IMG_Load("./images/map01.ppm");

    is_loaded(image);

    glGenTextures(1,&texture_image);
    glBindTexture(GL_TEXTURE_2D,texture_image);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexImage2D(
    GL_TEXTURE_2D,
    0, 
    GL_RGB,
    image->w,
    image->h, 
    0, 
    GL_RGB,
    GL_UNSIGNED_BYTE, 
    image->pixels);

    SDL_FreeSurface(image);
    glBindTexture(GL_TEXTURE_2D,0);
    int loop = 1;

    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
            glScalef(50,50,0);
            drawQuad(texture_image);
        glPopMatrix();
        
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
		
			if(	e.type == SDL_KEYDOWN 
				&& (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
			{
				loop = 0; 
				break;
			}
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) 
            {
                /* Redimensionnement fenetre */
				case SDL_VIDEORESIZE:
                    reshape(&surface, e.resize.w, e.resize.h);
                    break;

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    break;
                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
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

    glDeleteTextures(1,&texture_image);
    game_end(game);
    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();
    return EXIT_SUCCESS;
}