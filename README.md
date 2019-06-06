# IMAC TOWER DEFENSE
IMAC 1 - Projet C / OpenGL

## Sommaire

* [**Installer libraires**](#installer les libraries)

# Installer les librairies et package 
Pour que le projet fonctionne bien, vous aurez besoin d'installer le package GLUT, OpenGL, SDL, SDL_Image et SDL_Mixer. Et si jamais vous n'avez jamais compilé de C, vous aurez besoin de gcc.

### Installer gcc
Taper dans votre terminal : 
$ sudo apt install gcc

### Installer GLUT
Taper dans votre terminal : 
$sudo apt-get install freeglut3 freeglut3-dev

### Installer SDL
Taper dans votre terminal : 
```bash
sudo apt-get install libsdl2-dev
```

### Installer SDL_Image
Taper dans votre terminal : 
```bash
sudo apt-get install libsdl-image1.2 libsdl-image1.2-dev
```
### Installer SDL_Mixer
Taper dans votre terminal :
```bash
sudo apt-get install libsdl-mixer1.2 libsdl-mixer1.2-dev
```

# Installation du programme

#### 1ère étape : bon répertoire
Aller dans le répertoire où vous voulez mettre le dossier du jeu.

#### 2ème étape : compiler le programme
Taper dans votre terminal : 
$ make 

#### 3ème étape : lancer le programme
Si vous n'avez pas les librairies d'installées sur votre ordinateur et que vous n'avez pas envie, taper la commande suivante dans votre terminal : 
export LD_LIBRARY_PATH=./lib/lib 

Lancer avec la commande suivante : 

./bin/itd ./data/map.itd

# Utilisation
Appuyez sur [a] pour accélérer le jeu.
Appuyez sur [h] pour afficher l'aide.
Appuyez sur [p] pour mettre en pause le jeu.

# Auteurs

* **Clara DAIGMORTE**
* **Laurine LAFONTAINE** 
