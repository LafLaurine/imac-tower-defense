#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "../include/image.h"
#include "../include/map.h"
#include "../include/monster.h"
#include "../include/node.h"
#include "../include/display.h"
#include "../include/sprite.h"
#include "../include/installation.h"
#include "../include/common.h"

/* Dimensions initiales et titre de la fenetre */
static unsigned int WINDOW_WIDTH = 1000;
static unsigned int WINDOW_HEIGHT = 600;

static const char WINDOW_TITLE[] = "IMAC1 TOWER DEFENSE";


/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images. 100 ms = 1/10eme seconde */
static const Uint32 FRAMERATE_MILLISECONDS = 100;
static const Uint32 FRAMERATE_MILLISECONDS_FAST = 1000 / 60;


void reshape() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0., 1000., 600., 0.);
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
    int taille = 1;
    char* vecteur[] = {"Tab texte"};
    glutInit(&taille,vecteur); // initialisation de GLUT

    if(-1 == SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    init_window();
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
      printf("Erreur de son %s", Mix_GetError());
    }

    reshape();
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapBuffers();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Mix_Music *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadMUS("./son/la_vie.mp3"); //Chargement de la musique
  //  Mix_PlayMusic(musique, -1); //Jouer infiniment la musique

    /* Initialisation du titre de la fenetre */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);

    int cpt = 1;
    int xOver = 0;
    int yOver = 0;
    int speed = 0;
    int construct_tower = 0;
    int construct_install = 0;
    int help = 0;
    int monsterTypeInt = 0;
    int waveBool = 0;
    int nb_map = 0;
    int nb_menu = 0;
    Tower* t_selected = NULL;

    //Init map
    Map* map = init_map(argv[1]);

    //Menu pour map
    GLuint menuMap;
	SDL_Surface* imgMenuMap = load_sprite("./images/choix_map.png", &menuMap);
    
    // Map 1
    GLuint texture_map;
    SDL_Surface* s_map = load_sprite(map->img->path,&texture_map);

    //Argent
    GLuint texture_money;
    SDL_Surface* s_money = load_sprite("./images/money.png",&texture_money);

    //Croix pour quitter
    GLuint texture_cross;
    SDL_Surface* s_cross = load_sprite("./images/cross.png",&texture_cross);

    // Help
    GLuint help_txt;
    SDL_Surface* help_surface = load_sprite("./images/aide.jpg", &help_txt);

    //Game over
    GLuint game_over;
    SDL_Surface* s_over = load_sprite("./images/game_over.png",&game_over);
    //Game win
    GLuint game_win;
    SDL_Surface* s_win = load_sprite("./images/game_win.png",&game_win);

    //Game start
    GLuint game_start;
    SDL_Surface* s_start = load_sprite("./images/game_start.png",&game_start);

    //récup 1er noeud de la liste de noeud pour y positioner le monstre
    Node *root = map->list_node->head;
    Node *first = root;
    
    float monster_x = root->x;
    float monster_y = root->y;
    printf("Monster root head y %f", map->list_node->head->y);
    
    
    // Test check segment
    int x1, x2, y1, y2;
    x1 = 173; y1 = 375; x2 = 173; y2 = 467;
    if ((x2-x1) !=0) {
        check_segment_X(x1, y1, x2, y2, map);
    } else {
        check_segment_Y(x1, y1, x2, y2, map);
    }
      
    //création monstre
    List_Monster* l_monster = new_monster_list();
    Monster *m = NULL;
    Monster_Type m_type = BACTERY;
    
    // Création de la vague des monstres
    Wave wave;
    wave.nb_lists = 1;
    wave.lists[wave.nb_lists - 1] = l_monster;
    int nb_monsters_to_send = 10;
    
    // Init game
    Game *game = new_game();
    game->nb_lists_send = 1;
    
    // Create list tower
    List_Tower* l_tower =  new_tower_list();
    TowerType draw_type_tower = -1;
    
    // Create list installation
    List_Installation* l_inst =  new_installation_list();
    InstallationType draw_type_inst = -1;

	Tower* t = NULL;
    Installation* i = NULL;
    int loop = 1;
    
    while(loop) 
    {
        root = first;
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();

        /*code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
        glMatrixMode(GL_MODELVIEW);
        
        if(game->start == 0) {
			display_full(&game_start);
		}

        else if(game->over == 1) {
            display_full(&game_over);
		}
        
        else if(game->win == 1) {
            display_full(&game_win);
        }
      

        else {
        // Display map
        display_map(&texture_map);
        //display right column
        glPushMatrix();
            glTranslatef(600,0,0);
            display_right_column();
        glPopMatrix();

        //Display argent
        glPushMatrix();
            glTranslatef(620,68,0);
            display_money(&texture_money);
        glPopMatrix();        

        //Display cross
        glPushMatrix();
            glTranslatef(980,0,0);
            display_cross(&texture_cross);
        glPopMatrix();

        glPushMatrix();
            //Textes
            glColor3d(0,0,0); // Texte en blanc
            vBitmapOutput(620,50,"Appuyez sur h pour afficher l'aide",GLUT_BITMAP_HELVETICA_18);
            int money = game->money;
            char string_money[100];
            sprintf(string_money, "%d", money);
            //affichage nb argent qu'on a 
            vBitmapOutput(700,80,string_money,GLUT_BITMAP_HELVETICA_18);

            int time = startTime/1000;
            char string_time[100];
            sprintf(string_time, "%d", time);
            vBitmapOutput(620,130,"Temps : ",GLUT_BITMAP_HELVETICA_18);
            vBitmapOutput(700,130,string_time,GLUT_BITMAP_HELVETICA_18);
            vBitmapOutput(740,130,"secondes",GLUT_BITMAP_HELVETICA_18);
            
            int nb_wave = wave.nb_lists;
            char string_wave[100];
            sprintf(string_wave, "%d", nb_wave);
            vBitmapOutput(620,100,"Vague numero : ",GLUT_BITMAP_HELVETICA_18);
            vBitmapOutput(800,100,string_wave,GLUT_BITMAP_HELVETICA_18);
        glPopMatrix();

         if(help == 1){
            display_full(&help_txt);
        }

        //Vague monstre
        if(game->pause == 0) {
            if(cpt%50 == 0) {
                
                monsterTypeInt = rand()%2;
                if(monsterTypeInt == 0) {
                    m_type = BACTERY;
                } else {
                    m_type = VIRUS;
                }

                // Nouvelle liste de monstre
                if((l_monster->nb_monsters < 10) && (waveBool == 0) && (nb_monsters_to_send != 0)) {
                    m = create_monster(m_type, monster_x, monster_y, root, l_monster);
                    nb_monsters_to_send--;
                }

                if(cpt%550 == 0 && l_monster->nb_monsters == 10){
                    waveBool = 1;
                } else if (l_monster->nb_monsters == 0) {
                    waveBool = 0;
                    nb_monsters_to_send = 10;
                    wave.nb_lists++;
                    m->pv = m->pv*(wave.nb_lists/2);
                    m->money = m->money*(wave.nb_lists/2);
                }
            }
            cpt++;

            // Au bout de 50 vagues : Game Over
            if(wave.nb_lists == 51){
                game->win = 1;
            }

            // Argent gagne par type de monstre tue
            Monster_Type monsterKilled = monster_on_tower(l_monster, l_tower);
        
            if(monsterKilled != -1){
                if(monsterKilled == BACTERY){
                    game->money += m->money;
                } else {
                    game->money += m->money*2;
                }
            }

            //Affichage wave de monstres
            if (display_wave(l_monster) == 0) {
                game->over = 1; 
            }
            
            //Affichage tours
            display_list_tower(l_tower);
            if(l_tower != NULL) {
                if(t != NULL) {
                    t_selected = constructTowerSelected(l_tower, xOver, yOver);
				if(t_selected != NULL) {
					displayTowerFeatures(t_selected);
				}
            }
            }
            
        
            //Affichage installations
            display_list_installation(l_inst);
        }
         }
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

			if(e.type == SDL_MOUSEMOTION) {
				xOver = e.motion.x;
	        	yOver = e.motion.y;
			}
		
        
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) {
                /* Redimensionnement fenetre */
                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    init_window();
                break;
                
                /* Clic souris */
                case SDL_MOUSEBUTTONDOWN:
                    if(e.button.button == SDL_BUTTON_LEFT) {
                        if(draw_type_tower != -1){
                            if(tower_on_construct(map, e.button.x, e.button.y)) {
                                if(tower_on_building(l_tower, e.button.x, e.button.y, l_inst)){
                                    t = create_tower(draw_type_tower, e.button.x, e.button.y, l_tower, game->money);
                                    construct_tower = 1;
                                    check_around_tower(t, l_inst);
                                    player_money_down_update(game,t->cost);
                                    
                                } else {
                                    printf("Tour sur une autre\n");
                                }
                            }   
                        }
                        if(draw_type_inst != -1){
                            if(installation_on_construct(map, e.button.x, e.button.y)) {
                                if(inst_on_building(l_inst, e.button.x, e.button.y, l_tower)){
                                    i = create_installation(draw_type_inst, e.button.x, e.button.y, l_inst,game->money);
                                    construct_install = 1;
                                    check_around_inst(i, l_tower);
                                    printf("clic installation en (%d, %d)\n", e.button.x, e.button.y);
                                    player_money_down_update(game,i->cost);
                                } else {
                                    printf("Installation sur une autre\n");
                                    }
                            }   
                        }
                        //si on appuie sur la croix
                        if(e.button.x <= 1000 && e.button.x >= 980 && e.button.y <= 20 && e.button.y >= 0) {
                            loop = 0;
                        }
                    }
                   
                    if(e.button.button == SDL_BUTTON_RIGHT) {
                        if(t != NULL && construct_tower == 1){
                            t = click_tower(l_tower,e.button.x,e.button.y);
							click_delete_tower(l_tower,t,game, e.button.x, e.button.y);
                        }
                        if(i != NULL && construct_install == 1) {
                            i = click_installation(l_inst,e.button.x,e.button.y);
                            click_installation_delete(l_inst,i,game, e.button.x, e.button.y);
                            delete_around_inst(i, l_tower);
                        }
					}
            
                    

                   
                    break;
                    
                    /* Touche clavier */
                    case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                            case 'l' :
                                draw_type_tower = LASER;
                                draw_type_inst = -1;
                                break;
                            
                            case 'p' :
                                 if(game->pause == 0)
                                    game->pause = 1;
                                else
                                    game->pause = 0;
                                break;     
                            
                            case 'z' :
                                draw_type_tower = ROCKET;
                                draw_type_inst = -1;
                                break;
                                
                            case 'n' :
                                draw_type_tower = -1;
                                draw_type_inst = -1;
                                break;
                            
                            case 'r' :
                                draw_type_inst = RADAR;
                                draw_type_tower = -1;
                                break;

                            case 'u' :
                                draw_type_inst = USINE;
                                draw_type_tower = -1;
                                break;
                            
                            case 's' :
                               game->start = 1;
                            break;

                            case 'a' :
                                if(speed == 0)
                                    speed = 1;
                                else
                                    speed = 0;
                                break;                            
                            case 'h' :
                                if(help == 0)
                                {
                                    help = 1;
                                }
                                else {
                                    help = 0;
                                }
                                if(Mix_PausedMusic() == 1)//Si la musique est en pause
                                {
                                    Mix_ResumeMusic(); //Reprendre la musique
                                }
                                else
                                {
                                    Mix_PauseMusic(); //Mettre en pause la musique
                                }
                                if(game->pause == 0)
                                    game->pause = 1;
                                else
                                    game->pause = 0;
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
        if(speed == 0) {
            if(elapsedTime < FRAMERATE_MILLISECONDS) {
                SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
            }
        }
        else if(speed == 2) {
            if(elapsedTime < FRAMERATE_MILLISECONDS_FAST) {
                SDL_Delay(FRAMERATE_MILLISECONDS_FAST - elapsedTime);
            }
        }
    }

    game_end(game);
  
    glDeleteTextures(1,&texture_map);
    glDeleteTextures(2,&texture_cross);
    glDeleteTextures(3,&texture_money);
    glDeleteTextures(4,&help_txt);
    glDeleteTextures(5,&game_over);
    glDeleteTextures(5,&game_win);
    glDeleteTextures(5,&game_start);
    SDL_FreeSurface(s_map);
    SDL_FreeSurface(s_money);
    SDL_FreeSurface(s_win);
    SDL_FreeSurface(s_over);
    SDL_FreeSurface(s_cross);
    SDL_FreeSurface(help_surface);
    SDL_FreeSurface(s_start);
    /* Liberation des ressources associees a la SDL */ 
    Mix_FreeMusic(musique); //Libération de la musique
    Mix_CloseAudio();
    SDL_Quit();
    return EXIT_SUCCESS;
}