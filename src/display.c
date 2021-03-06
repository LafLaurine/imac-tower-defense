#include "../include/display.h"

int display_map(GLuint* texture) {
	if(texture != NULL) {
		// Activate 2D texturage
		glEnable(GL_TEXTURE_2D);
		// Texture call
		glBindTexture(GL_TEXTURE_2D, *texture);
			glBegin(GL_QUADS);
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(600, 600);

			glTexCoord2f(1, 0);
			glVertex2f(600, 0);

			glTexCoord2f(0, 0);
			glVertex2f(0, 0);

			glTexCoord2f(0, 1);
			glVertex2f(0, 600);

			glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	} else {
		fprintf(stderr, "Map texture doesn't exist\n");
		return 0;
	}
	return 1;
}

void draw_perim(float rayon) {
	int i, j = 100;
	float angle, x1, y1;
	
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);

	for(i = 0; i <= j; i++) {
		angle = (2*3.14*i)/j;
		x1 = rayon*(cos(angle));
		y1 = rayon*(sin(angle));
		glVertex2f(x1,y1);
	}

	glEnd();
}

int display_path(Map* map) {
	if(map != NULL) {
		Node* tmp = map->list_node->head;

		while(tmp->next != NULL) {
			//node
			glBegin(GL_LINES);
				glColor3ub(0,0,0);
				glVertex2d(tmp->x, tmp->y);
				glVertex2d(tmp->next->x, tmp->next->y);
			glEnd();

			glPushMatrix();
				glColor3ub((map->node).r,(map->node).g,(map->node).b);
				glTranslatef(tmp->x,tmp->y, 0.0);
				draw_perim(2);
			glPopMatrix();
			//path
			glColor3ub(255,255,255);

			tmp = tmp->next;					
		}
	} else {
		fprintf(stderr, "Map doesn't exist\n");
		return 0;
	}
	return 1;
}


int display_full(GLuint *texture) {
	if(texture != NULL) {
		// Activate 2D texture
		glEnable(GL_TEXTURE_2D);
		// Texture call
		glBindTexture(GL_TEXTURE_2D, *texture);
			glBegin(GL_QUADS);
			glColor4ub(255,255,255,255);
			// Texture coordinate
			glTexCoord2f(1, 1);
			// Quadrilatere coordinate
			glVertex2f(1000,600);
			glTexCoord2f(1, 0);
			glVertex2f(1000, 0);
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);
			glTexCoord2f(0, 1);
			glVertex2f(0, 600);
			glEnd();
		// Deactivate 2D texture
		glDisable(GL_TEXTURE_2D);		
	} else {
		fprintf(stderr, "Couldn't find texture\n");
		return 0;
	}
	return 1;
}


int display_money(GLuint* texture) {
	if(texture != NULL) {
		// Activate 2D texture
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Call texture
		glBindTexture(GL_TEXTURE_2D, *texture);
			glBegin(GL_QUADS);
			// Texture coordinate
			glTexCoord2f(1, 1);
			// Quadrilatere coordinate
			glVertex2f(30, 13);
			glTexCoord2f(1, 0);
			glVertex2f(30, 0);
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);
			glTexCoord2f(0, 1);
			glVertex2f(0, 13);
			glEnd();
		// Debind texture
		glBindTexture(GL_TEXTURE_2D, 0);
		// Deactivate 2D texture
		glDisable(GL_TEXTURE_2D);
	} else {
		fprintf(stderr, "Couldn't find money\n");
		return 0;
	}
	return 1;
}

int display_cross(GLuint* texture) {
	if(texture != NULL) {
		// Activate 2D texture
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Texture call
		glBindTexture(GL_TEXTURE_2D, *texture);
			glBegin(GL_QUADS);
			// Texture coordoninate
			glTexCoord2f(1, 1);
			// Quadrilatere coordinate 
			glVertex2f(20, 20);
			glTexCoord2f(1, 0);
			glVertex2f(20, 0);
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);
			glTexCoord2f(0, 1);
			glVertex2f(0, 20);
			glEnd();
		// Debind texture
		glBindTexture(GL_TEXTURE_2D, 0);
		// Deactivate 2D texture
		glDisable(GL_TEXTURE_2D);
	}
	else {
		fprintf(stderr, "Couldn't find cross\n");
		return 0;
	}
	return 1;
}

void display_right_column() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3ub(255,255,255);
	glBegin(GL_QUADS);
		// Quadrilatere coordinate
		glVertex2f(400, 600);
		glVertex2f(400, 0);
		glVertex2f(0, 0);
		glVertex2f(0, 600);
	glEnd();
}

int display_right_column_down(GLuint *texture) {
	if(texture != NULL) {
		// Activate 2D texture
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Texture call
		glBindTexture(GL_TEXTURE_2D, *texture);
			glBegin(GL_QUADS);
			// Texture coordinate
			glTexCoord2f(1, 1);
			// Quadrilatere coordinate
			glVertex2f(400, 400);
			glTexCoord2f(1, 0);
			glVertex2f(400, 0);
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);
			glTexCoord2f(0, 1);
			glVertex2f(0, 400);
			glEnd();
		// Debind texture
		glBindTexture(GL_TEXTURE_2D, 0);
		// Deactivate 2D texture
		glDisable(GL_TEXTURE_2D);
	}
	else {
		fprintf(stderr, "Couldn't find column\n");
		return 0;
	}
	return 1;
}


// MONSTER
int display_monster(Monster* m, SDL_Surface* img, GLuint texture) {
	if(m->node_next != NULL) {
		if(m->move == m->speed) {
			// Horizontal monster deplacement
			if(m->node_next->y == m->y) {
				// To the right
				if(m->node_next->x > m->x) {
					m->x += 1;
				}
				// To the left
				else {
					m->x -= 1;
				}   
			}
			// Vertical monster deplacement
			else {
				// Down
				if(m->node_next->y > m->y) {
					m->y += 1;
				}
				// Up
				else {
					m->y -= 1;
				}
			}

			if(m->x == m->node_next->x && m->y == m->node_next->y) {
				m->node_next = m->node_next->next;
			}

			m->move = 0;
		}
		else {
			m->move += 1;
		}

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, texture);

		glBegin(GL_QUADS);
			glColor3ub(255, 255, 255); // neutral color
			glTexCoord2d(0, 1); glVertex2d(m->x + img->w * 0.5, m->y + img->h * 0.5);
			glTexCoord2d(0, 0); glVertex2d(m->x + img->w * 0.5, m->y - img->h * 0.5);
			glTexCoord2d(1, 0); glVertex2d(m->x - img->w * 0.5, m->y - img->h * 0.5);
			glTexCoord2d(1, 1); glVertex2d(m->x - img->w * 0.5, m->y + img->h * 0.5);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		// Life visual
		glBegin(GL_QUADS);
		glColor3ub(255, 0, 0);
		glVertex2d(m->x, m->y + 45);
		glVertex2d(m->x, m->y + 40);
		if(m->pv > 0 && m->pv < 1) {
				glVertex2d(m->x + 1, m->y + 40);
			glVertex2d(m->x + 1, m->y + 45);
		}
		else {
				glVertex2d(m->x + m->pv / 2, m->y + 40);
			glVertex2d(m->x + m->pv / 2, m->y + 45);
		}	
		glEnd();
		return 1;
	}
	return 0;
}

int display_wave(List_Monster *l_monster) {
	// Load texture bactery
	SDL_Surface* bactery = IMG_Load("./images/monsters/bactery.png");
	if(bactery == NULL) {
		fprintf(stderr, "impossible de charger l'image monsters/bactery.png \n");
		exit(1);
	}

	// Load texture virus
	SDL_Surface* virus = IMG_Load("./images/monsters/virus.png");
	if(virus == NULL) {
		fprintf(stderr, "impossible de charger l'image monsters/virus.png \n");
		exit(1);
	}

	GLuint texture_bactery;
	load_sprite("./images/monsters/bactery.png",&texture_bactery);
	GLuint texture_virus;
	load_sprite("./images/monsters/virus.png",&texture_virus);

	Monster* m;
	int success = 1;
	m = l_monster->m_last;
		
		// Check all monsters of list monster
		while(m != NULL) {
			if(m->type == BACTERY) {
				if(display_monster(m, bactery, texture_bactery) == 0) {
					success = 0;
				}
			}
			else {
				if(display_monster(m, virus, texture_virus) == 0) {
					success = 0;
				}
			}
			m = m->m_prev;
		}

	SDL_FreeSurface(bactery);
	SDL_FreeSurface(virus);

	return success;
}


// TOWERS
int display_tower(Tower* t, SDL_Surface* tourImg, GLuint *tourTexture) {
	if(t != NULL) {
		display_range_tower(t);

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, *tourTexture);

		glBegin(GL_QUADS);
			glColor3ub(255, 255, 255); // neutral color
			glTexCoord2d(0, 1); glVertex2d(t->x + tourImg->w*0.5, t->y + tourImg->h*0.5);
			glTexCoord2d(0, 0); glVertex2d(t->x + tourImg->w*0.5, t->y - tourImg->h*0.5);
			glTexCoord2d(1, 0); glVertex2d(t->x - tourImg->w*0.5, t->y - tourImg->h*0.5);
			glTexCoord2d(1, 1); glVertex2d(t->x - tourImg->w*0.5, t->y + tourImg->h*0.5);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		return 1;
	}
	return 0;
}

int display_list_tower(List_Tower* list_tower) {
	int success = 1;
	
	if(list_tower->t_first == NULL){
		return success;
	} else {
		SDL_Surface* rocket = IMG_Load("./images/towers/globule_rouge.png");
		// Load textures
		if(rocket == NULL) {
			fprintf(stderr, "impossible de charger l'image globule_rouge.png \n");
			exit(1);
		}
		
		SDL_Surface* laser = IMG_Load("./images/towers/globule_blanc.png");
		if(laser == NULL) {
			fprintf(stderr, "impossible de charger l'image globule_blanc.png \n");
			exit(1);
		}

		SDL_Surface* bandage = IMG_Load("./images/towers/bandage.png");
		if(bandage == NULL) {
			fprintf(stderr, "impossible de charger l'image bandage.png \n");
			exit(1);
		}

		SDL_Surface* medoc = IMG_Load("./images/towers/medoc.png");
		if(medoc == NULL) {
			fprintf(stderr, "impossible de charger l'image medoc.png \n");
			exit(1);
		}

		// Load sprites
		GLuint texture_rocket;
		load_sprite("./images/towers/globule_rouge.png",&texture_rocket);
		GLuint texture_laser;
		load_sprite("./images/towers/globule_blanc.png",&texture_laser);
		GLuint texture_bandage;
		load_sprite("./images/towers/bandage.png",&texture_bandage);
		GLuint texture_medoc;
		load_sprite("./images/towers/medoc.png",&texture_medoc);

		Tower* t;
		t = list_tower->t_last;

		// Display tower according to type
		while(t != NULL) {
			if(t->type == GLOBULE_ROUGE) {
				if(display_tower(t, rocket, &texture_rocket) == 0) {
					success = 0;
				}
			}
			else if(t->type == GLOBULE_BLANC) {
				if(display_tower(t, laser, &texture_laser) == 0) {
					success = 0;
				}
			} else if(t->type == MEDOC) {
				if(display_tower(t, medoc, &texture_medoc) == 0) {
					success = 0;
				}
			} else if(t->type == BANDAGE) {
				if(display_tower(t, bandage, &texture_bandage) == 0) {
					success = 0;
				}
			} else {
				printf("Couldn't display tower");
			}
			t = t->t_prev;
		}

		SDL_FreeSurface(rocket);
		SDL_FreeSurface(laser);
		SDL_FreeSurface(bandage);
		SDL_FreeSurface(medoc);
		return success;
	}
}

int display_range_tower(Tower* t) {
	if(t != NULL) {
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1.0,0.0,0.0,0.5);
			glTranslatef(t->x,t->y, 0.0);
			glScalef(t->range+64,t->range+64,0);
			drawCircle(1, 50);
		glPopMatrix();

		return 1;
	}
	return 0;
}

// INSTALLATION
int display_installation(Installation* i, SDL_Surface* instImg, GLuint *instTexture) {
	if(i != NULL) {
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, *instTexture);

		glBegin(GL_QUADS);
			glColor3ub(255, 255, 255); // neutral color
			glTexCoord2d(0, 1); glVertex2d(i->x + instImg->w * 0.5, i->y + instImg->h * 0.5);
			glTexCoord2d(0, 0); glVertex2d(i->x + instImg->w * 0.5, i->y - instImg->h * 0.5);
			glTexCoord2d(1, 0); glVertex2d(i->x - instImg->w * 0.5, i->y - instImg->h * 0.5);
			glTexCoord2d(1, 1); glVertex2d(i->x - instImg->w * 0.5, i->y + instImg->h * 0.5);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		return 1;
	}
	return 0;
}

int display_list_installation(List_Installation* list_inst) {
	int success = 1;
	
	if(list_inst->i_first == NULL){
		return success;
	} else {
		SDL_Surface* radar = IMG_Load("./images/installations/radar.png");

		if(radar == NULL) {
			fprintf(stderr, "impossible de charger l'image radar.png \n");
			exit(1);
		}
		
		SDL_Surface* usine = IMG_Load("./images/installations/usine.png");
		if(usine == NULL) {
			fprintf(stderr, "impossible de charger l'image usine.png \n");
			exit(1);
		}

		SDL_Surface* stock = IMG_Load("./images/installations/stock.png");
		if(stock == NULL) {
			fprintf(stderr, "impossible de charger l'image stock.png \n");
			exit(1);
		}
		
		GLuint texture_radar;
		load_sprite("./images/installations/radar.png",&texture_radar);
		GLuint texture_usine;
		load_sprite("./images/installations/usine.png",&texture_usine);
		GLuint texture_stock;
		load_sprite("./images/installations/stock.png",&texture_stock);

		Installation* i;
		i = list_inst->i_first;

		// Check all installations of list installation
		while(i != NULL) {
			if(i->type == RADAR) {
				if(display_installation(i, radar, &texture_radar) == 0) {
					success = 0;
				}
			}
			else if(i->type == USINE) {
				if(display_installation(i, usine, &texture_usine) == 0) {
					success = 0;
				}
			}
			else if(i->type == STOCK) {
				if(display_installation(i, stock, &texture_stock) == 0) {
					success = 0;
				}
			}  
			else {
				printf("Couldn't display installation");
			}
			i = i->i_next;
		}

		SDL_FreeSurface(radar);
		SDL_FreeSurface(usine);

		return success;
	}
}


// OTHER
void drawCircle (int fill, int nbSeg) {
    float teta = 0;
    glBegin(GL_POLYGON);
    if (fill)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    for (teta=0; teta<=2*PI; teta+=2*PI/nbSeg) {
        glVertex2f(0.5*cos(teta),0.5*sin(teta));
    }
    glEnd();       
}

void displayTowerFeatures(Tower* t) {
	SDL_Surface* featuresImg = malloc(sizeof(SDL_Surface*));
	GLuint featuresTexture;

	if(t != NULL) {
		// Load tower features according to its type
		if((*t).type == GLOBULE_ROUGE) {
			featuresImg = IMG_Load("./images/info/info_gr.png");
		    if(featuresImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image info/info_gr.png \n");
		        exit(1);
		    }
		    load_sprite("./images/info/info_gr.png",&featuresTexture);
		}
		else if((*t).type == GLOBULE_BLANC) {
			featuresImg = IMG_Load("./images/info/info_gb.png");
		    if(featuresImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image info/info_gb.png \n");
		        exit(1);
			}
		    load_sprite("./images/info/info_gb.png",&featuresTexture);		
		}
		else if((*t).type == MEDOC) {
			featuresImg = IMG_Load("./images/info/info_medoc.png");
		    if(featuresImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image info/info_medoc.png \n");
		        exit(1);
		    }
		    load_sprite("./images/info/info_medoc.png",&featuresTexture);
		}
		else if((*t).type == BANDAGE) {
			featuresImg = IMG_Load("./images/info/info_bandage.png");
		    if(featuresImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image info/info_bandage.png \n");
		        exit(1);
		    }
		    load_sprite("./images/info/info_bandage.png",&featuresTexture);
		}
		
		// Display texture on map
		glEnable(GL_TEXTURE_2D);
	    glEnable(GL_BLEND);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glBindTexture(GL_TEXTURE_2D, featuresTexture);
	    
		glBegin(GL_QUADS);
			glColor4ub(255, 255, 255, 255); // Opacity 100%
			glTexCoord2d(0, 0); 
			glVertex2f((*t).x - featuresImg->w * 0.5 + featuresImg->w / 2.5, (*t).y - featuresImg->h * 0.5 + featuresImg->h / 2);
			glTexCoord2d(0, 1);
			glVertex2f((*t).x - featuresImg->w * 0.5 + featuresImg->w / 2.5, (*t).y + featuresImg->h * 0.5 + featuresImg->h / 2);
			glTexCoord2d(1, 1); 
			glVertex2f((*t).x + featuresImg->w * 0.5 + featuresImg->w / 2.5, (*t).y + featuresImg->h * 0.5 + featuresImg->h / 2);
			glTexCoord2d(1, 0);
			glVertex2f((*t).x + featuresImg->w * 0.5 + featuresImg->w / 2.5, (*t).y - featuresImg->h * 0.5 + featuresImg->h / 2);
		glEnd();
	    
	    glBindTexture(GL_TEXTURE_2D, 0);
	    glDisable(GL_BLEND);
	    glDisable(GL_TEXTURE_2D);
    }

    glDeleteTextures(1, &featuresTexture);
    SDL_FreeSurface(featuresImg);
}

void displayInstallationFeatures(Installation* i) {
	SDL_Surface* featuresImg = malloc(sizeof(SDL_Surface*));
	GLuint featuresTexture;

	if(i != NULL) {
		// Load installation features according to its type
		if((*i).type == USINE) {
			featuresImg = IMG_Load("./images/info/info_usine.png");
		    if(featuresImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image info/info_usine.png \n");
		        exit(1);
		    }
		    load_sprite("./images/info/info_usine.png",&featuresTexture);
		}
		else if((*i).type == STOCK) {
			featuresImg = IMG_Load("./images/info/info_stock.png");
		    if(featuresImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image info/info_stock.png \n");
		        exit(1);
			}
		    load_sprite("./images/info/info_stock.png",&featuresTexture);		
		}
		else if((*i).type == RADAR) {
			featuresImg = IMG_Load("./images/info/info_radar.png");
		    if(featuresImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image info/info_radar.png \n");
		        exit(1);
		    }
		    load_sprite("./images/info/info_radar.png",&featuresTexture);
		}
		
		// Display texture on map
		glEnable(GL_TEXTURE_2D);
	    glEnable(GL_BLEND);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glBindTexture(GL_TEXTURE_2D, featuresTexture);
	    
		glBegin(GL_QUADS);
			glColor4ub(255, 255, 255, 255); // Opacity 100%
			glTexCoord2d(0, 0); 
			glVertex2f((*i).x - featuresImg->w * 0.5 + featuresImg->w / 2.5, (*i).y - featuresImg->h * 0.5 + featuresImg->h / 2);
			glTexCoord2d(0, 1);
			glVertex2f((*i).x - featuresImg->w * 0.5 + featuresImg->w / 2.5, (*i).y + featuresImg->h * 0.5 + featuresImg->h / 2);
			glTexCoord2d(1, 1); 
			glVertex2f((*i).x + featuresImg->w * 0.5 + featuresImg->w / 2.5, (*i).y + featuresImg->h * 0.5 + featuresImg->h / 2);
			glTexCoord2d(1, 0);
			glVertex2f((*i).x + featuresImg->w * 0.5 + featuresImg->w / 2.5, (*i).y - featuresImg->h * 0.5 + featuresImg->h / 2);
		glEnd();
	    
	    glBindTexture(GL_TEXTURE_2D, 0);
	    glDisable(GL_BLEND);
	    glDisable(GL_TEXTURE_2D);
    }

    glDeleteTextures(1, &featuresTexture);
    SDL_FreeSurface(featuresImg);
}
