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

/* Inital dimension and window title */
static unsigned int WINDOW_WIDTH = 1000;
static unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "IL ETAIT UNE FOIS LA VIE";

/* Number bit per pixel */
static const unsigned int BIT_PER_PIXEL = 32;

/* Minimal number of miliseconde. 100 ms = 1/10 s */
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
            SDL_OPENGL | SDL_DOUBLEBUF)) {
        fprintf(stderr, "Can't open window. End of programm.\n");
        exit(EXIT_FAILURE);
    }
}

int main (int argc, char* argv[])
{
    int length = 1;
    char* vector[] = {"Tab text"};
    glutInit(&length, vector); // GLUT init

    if(-1 == SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) 
    {
        printf("Cannot initialize SDL. End of programm.\n");
        exit(EXIT_FAILURE);
    }

    //Open window and create SDL context
    init_window();
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //API Mixer init
    {
      printf("Sound error %s", Mix_GetError());
    }

    reshape();
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapBuffers();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Mix_Music *music; //Init music
    music = Mix_LoadMUS("./son/la_vie.mp3"); //Load music
    Mix_AllocateChannels(16);
    Mix_PlayMusic(music, -1); //Infinite play music

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
    Tower* t_selected = NULL;
    Installation* i_selected = NULL;

    //Init map
    Map* map = init_map(argv[1]);

    //int *path_tab = malloc(sizeof(int*));
    //init_djisksra(*map, path_tab);

    //Map
    GLuint map_texture;
    SDL_Surface* s_map = load_sprite(map->img->path,&map_texture);

    //Money
    GLuint money_texture;
    SDL_Surface* s_money = load_sprite("./images/ui/money.png",&money_texture);

    //Cross
    GLuint cross_texture;
    SDL_Surface* s_cross = load_sprite("./images/ui/cross.png",&cross_texture);

    //Help
    GLuint help_txt;
    SDL_Surface* help_surface = load_sprite("./images/ui/aide.png", &help_txt);

    //Game over
    GLuint game_over;
    SDL_Surface* s_over = load_sprite("./images/ui/game_over.png",&game_over);

    //Game win
    GLuint game_win;
    SDL_Surface* s_win = load_sprite("./images/ui/game_win.png",&game_win);

    //Game start
    GLuint game_start;
    SDL_Surface* s_start = load_sprite("./images/ui/game_start.png",&game_start);

    //Game pause
    GLuint game_pause;
    SDL_Surface* s_pause = load_sprite("./images/ui/pause.png",&game_pause);

    //Right texture
    GLuint texture_right;
    SDL_Surface* s_right = load_sprite("./images/ui/colonne_droite.png",&texture_right);

    //Get 1st node of map for the monster position
    Node *root = map->list_node->head;
    Node *first = root;
    
    //Monster position = 1st node position
    float monster_x = root->x;
    float monster_y = root->y;
      
    //Create monster
    List_Monster* l_monster = new_monster_list();
    Monster *m = NULL;
    //Default type ist BACTERY
    Monster_Type m_type = BACTERY;
    
    //Create monster wave
    Wave wave;
    wave.nb_lists = 1;
    wave.lists[wave.nb_lists - 1] = l_monster;
    int nb_monsters_to_send = 10;
    
    //Init game
    Game *game = new_game();
    
    //Create list tower
    List_Tower* l_tower =  new_tower_list();
    TowerType draw_type_tower = -1;
    
    //Create list installation
    List_Installation* l_inst =  new_installation_list();
    InstallationType draw_type_inst = -1;

    //Create tower
	Tower* t = NULL;
    //Create installation
    Installation* i = NULL;
    int loop = 1;
    
    while(loop) 
    {
        //root = first node
        root = first;
        //Get time at the beginning of the loop
        Uint32 startTime = SDL_GetTicks();

        //Drawing code
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
        glMatrixMode(GL_MODELVIEW);
        
        //if game hasn't start yet display title 
        if(game->start == 0) {
			display_full(&game_start);
		}

        //if game is lost
        else if(game->over == 1) {
            display_full(&game_over);
		}
        
        //if game is won
        else if(game->win == 1) {
            display_full(&game_win);
        }

        else {
        // Display map
        display_map(&map_texture);
        //display right column
        glPushMatrix();
            glTranslatef(600,0,0);
            display_right_column();
        glPopMatrix();
         //display right column down
        glPushMatrix();
            glTranslatef(600,200,0);
            display_right_column_down(&texture_right);
        glPopMatrix();

        //Display argent
        glPushMatrix();
            glTranslatef(620,68,0);
            display_money(&money_texture);
        glPopMatrix();        

        //Display cross
        glPushMatrix();
            glTranslatef(980,0,0);
            display_cross(&cross_texture);
        glPopMatrix();

        glPushMatrix();
            //Textes
            glColor3d(0,0,0);
            vBitmapOutput(620,50,"Appuyez sur h pour afficher l'aide",GLUT_BITMAP_HELVETICA_18);
            int money = game->money;
            char string_money[100];
            sprintf(string_money, "%d", money);
            //Print player money
            vBitmapOutput(700,80,string_money,GLUT_BITMAP_HELVETICA_18);

            //Get time spent to play
            int time = startTime/1000;
            char string_time[100];
            sprintf(string_time, "%d", time);
            //print time
            vBitmapOutput(620,130,"Temps : ",GLUT_BITMAP_HELVETICA_18);
            vBitmapOutput(700,130,string_time,GLUT_BITMAP_HELVETICA_18);
            vBitmapOutput(740,130,"secondes",GLUT_BITMAP_HELVETICA_18);
            
            int nb_wave = wave.nb_lists;
            char string_wave[100];
            sprintf(string_wave, "%d", nb_wave);
            vBitmapOutput(620,105,"Vague numero : ",GLUT_BITMAP_HELVETICA_18);
            vBitmapOutput(800,105,string_wave,GLUT_BITMAP_HELVETICA_18);
        glPopMatrix();
       
        //if game is paused
        if(game->pause == 1){
            display_map(&game_pause);
        }

        //if help is pushed
        if(help == 1){
            display_full(&help_txt);
        }

        //Wave monster
        if(game->pause == 0) {
            if(cpt%50 == 0) {
                //generate random monster type
                monsterTypeInt = rand()%2;
                if(monsterTypeInt == 0) {
                    m_type = BACTERY;
                } else {
                    m_type = VIRUS;
                }

                //New monster list
                if((l_monster->nb_monsters < 10) && (waveBool == 0) && (nb_monsters_to_send != 0)) {
                    m = create_monster(m_type, monster_x, monster_y, root, l_monster);
                    nb_monsters_to_send--;
                }
                //if 10 monsters have been generated : it's a wave !
                if(cpt%550 == 0 && l_monster->nb_monsters == 10){
                    waveBool = 1;
                //if there is no monster in our wave we complete it
                } else if (l_monster->nb_monsters == 0) {
                    waveBool = 0;
                    nb_monsters_to_send = 10;
                    wave.nb_lists++;
                    m->pv = m->pv*(wave.nb_lists/2);
                    m->money = m->money*(wave.nb_lists);
                    //i->cost += i->cost;
                }
            }
            cpt++;

            //50 waves = game over
            if(wave.nb_lists == 51){
                game->win = 1;
            }

            //Money won by monster type killed
            Monster_Type monsterKilled = monster_on_tower(l_monster, l_tower);
        
            //one virus killed = 2* more money !
            if(monsterKilled != -1){
                if(monsterKilled == BACTERY){
                    game->money += m->money;
                } else if(monsterKilled == VIRUS) {
                    game->money += m->money*2;
                }
            }

            //display wave
            if (display_wave(l_monster) == 0) {
                game->over = 1; 
            }
            
            //Display tower
            display_list_tower(l_tower);
            if(l_tower != NULL) {
                if(t != NULL) {
                    //get tower on hover
                    t_selected = constructTowerSelected(l_tower, xOver, yOver);
                    if(t_selected != NULL) {
                        //display tower properties on hover
                        displayTowerFeatures(t_selected);
                    }
                }
            }
        
            //Display installations
            display_list_installation(l_inst);

            if(l_inst != NULL) {
                if(i != NULL) {
                    //get installations on hover
                    i_selected = select_installation_construted(l_inst, xOver, yOver);
                    if(i_selected != NULL) {
                        //display installation properties on hover
                        displayInstallationFeatures(i_selected);
                    }
                }
            }
        }
        }
        SDL_GL_SwapBuffers();
        
       
        //Event loop
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            //close window
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }

            //hover point position
			if(e.type == SDL_MOUSEMOTION) {
				xOver = e.motion.x;
	        	yOver = e.motion.y;
			}
		
        
            switch(e.type) {               
                //Mouse clic
                case SDL_MOUSEBUTTONDOWN:
                    if(e.button.button == SDL_BUTTON_LEFT) {
                        if(draw_type_tower != -1){
                            //if we're on the map
                            if(e.button.x >=0 && e.button.x <=600) {
                                //check if click is on construct area
                                if(tower_on_construct(map, e.button.x, e.button.y)) {
                                    //check is tower is on an installation
                                    if(tower_on_building(l_tower, e.button.x, e.button.y, l_inst)){
                                        //create tower
                                        t = create_tower(draw_type_tower, e.button.x, e.button.y, l_tower, game->money);
                                        if(t != NULL){
                                            construct_tower = 1;
                                            //check for installation power
                                            check_around_tower(t, l_inst);
                                            //downgrade money
                                            player_money_down_update(game, t->cost);
                                        }                                    
                                    } else {
                                        printf("Tour sur une autre\n");
                                    }
                                }   
                            }
                        }
                        if(draw_type_inst != -1){
                                 //if we're on the map
                                if(e.button.x >=0 && e.button.x <=600) {
                                    //if click is on a constructible material 
                                    if(installation_on_construct(map, e.button.x, e.button.y)) {
                                        //if installation is on another installation
                                        if(inst_on_building(l_inst, e.button.x, e.button.y, l_tower)){
                                            //create new installation
                                            i = create_installation(draw_type_inst, e.button.x, e.button.y, l_inst,game->money);
                                            if(i != NULL) {
                                                construct_install = 1;
                                                //check around in order to give tower power
                                                check_around_inst(i, l_tower);
                                                //downgrade money
                                                player_money_down_update(game, i->cost);
                                            }
                                        } else {
                                            printf("Installation sur une autre\n");
                                        }
                                    }   
                                }
                        }
                        //if click on red cross
                        if(e.button.x <= 1000 && e.button.x >= 980 && e.button.y <= 20 && e.button.y >= 0) {
                            loop = 0;
                        }
                    }
                   
                    if(e.button.button == SDL_BUTTON_RIGHT) {
                        //check if we click on a tower
                        t = click_tower(l_tower, e.button.x, e.button.y);
                        if(t != NULL && construct_tower == 1){
                            //delete tower
							click_delete_tower(l_tower, t, game);
                        }
                        //check if we click on an installation
                        i = click_installation(l_inst, e.button.x, e.button.y);
                        if(i != NULL && construct_install == 1) {
                            //delete installation
                            click_installation_delete(l_inst, i, game, l_tower);
                        }
					}
                    break;
                    
                    //key touch
                    case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                            //monster globule_blanc
                            case 'l' :
                                draw_type_tower = GLOBULE_BLANC;
                                draw_type_inst = -1;
                            break;
                            
                            //pause game
                            case 'p' :
                                 if(game->pause == 0)
                                    game->pause = 1;
                                else
                                    game->pause = 0;
                                if(Mix_PausedMusic() == 1) //if music is paused
                                    Mix_ResumeMusic(); //restart music
                                else
                                {
                                    Mix_PauseMusic(); //pause music
                                }
                                break;     

                            //monster globule_rouge
                            case 'z' :
                                draw_type_tower = GLOBULE_ROUGE;
                                draw_type_inst = -1;
                            break;

                            //monster medoc
                            case 'm' :
                                draw_type_tower = MEDOC;
                                draw_type_inst = -1;
                            break;

                            //monster bandage
                            case 'b' :
                                draw_type_tower = BANDAGE;
                                draw_type_inst = -1;
                            break;
                            
                            //get back to none
                            case 'n' :
                                draw_type_tower = -1;
                                draw_type_inst = -1;
                                break;
                                
                            //installation radar
                            case 'r' :
                                draw_type_inst = RADAR;
                                draw_type_tower = -1;
                            break;

                            //installation usine
                            case 'u' :
                                draw_type_inst = USINE;
                                draw_type_tower = -1;
                            break;
                            
                            //installation stock
                            case 't' :
                                draw_type_inst = STOCK;
                                draw_type_tower = -1;
                            break;
                            
                            //if player pressed s, game start
                            case 's' :
                               game->start = 1;
                            break;

                            //speed game
                            case 'a' :
                                if(speed == 0)
                                    speed = 1;
                                else
                                    speed = 0;
                                break;     

                            //press h for help                       
                            case 'h' :
                                if(help == 0)
                                {
                                    help = 1;
                                }
                                else {
                                    help = 0;
                                }
                                if(Mix_PausedMusic() == 1)
                                {
                                    Mix_ResumeMusic();
                                }
                                else
                                {
                                    Mix_PauseMusic(); 
                                }
                                if(game->pause == 0)
                                    game->pause = 1;
                                else
                                    game->pause = 0;
                                break;

                            //q or esc quit game
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

        //calculate time spent
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        //change time for acceleration
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

    //free all elements
    free_all_monster(l_monster);
    free_all_tower(l_tower);
    free_all_inst(l_inst);
    free_all_node(map->list_node);
    free_map(map);
    game_end(game);
  
    //free all textures
    glDeleteTextures(1,&map_texture);
    glDeleteTextures(2,&cross_texture);
    glDeleteTextures(3,&money_texture);
    glDeleteTextures(4,&help_txt);
    glDeleteTextures(5,&game_over);
    glDeleteTextures(5,&game_win);
    glDeleteTextures(5,&game_start);

    //free all surfaces
    SDL_FreeSurface(s_map);
    SDL_FreeSurface(s_money);
    SDL_FreeSurface(s_win);
    SDL_FreeSurface(s_over);
    SDL_FreeSurface(s_right);
    SDL_FreeSurface(s_cross);
    SDL_FreeSurface(help_surface);
    SDL_FreeSurface(s_start);
    SDL_FreeSurface(s_pause);

    //free sdl ressources 
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
    return EXIT_SUCCESS;
}