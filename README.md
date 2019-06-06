# IMAC TOWER DEFENSE
IMAC 1 - Projet C / OpenGL

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
```bash
make
``` 

#### 3ème étape : lancer le programme
Si vous n'avez pas les librairies d'installées sur votre ordinateur et que vous n'avez pas envie, taper la commande suivante dans votre terminal : 
``` bash
export LD_LIBRARY_PATH=./lib/lib 
``` 

Lancer avec la commande suivante : 
```bash
./bin/itd ./data/map01.itd
```
pour le level 1

```bash
./bin/itd ./data/map02.itd
```
pour le level 2

# Utilisation

## Général
* Appuyez sur [a] pour accélérer le jeu.
* Appuyez sur [h] pour afficher l'aide.
* Appuyez sur [p] pour mettre en pause le jeu.

## Tours
* Appuyez sur [z] pour faire un globule rouge.
* Appuyez sur [l] pour faire un globule blanc.
* Appuyez sur [b] pour faire un bandage.
* Appuyez sur [m] pour faire un médicament.

## Installations
* Appuyez sur [u] pour faire une usine.
* Appuyez sur [r] pour faire un radar.
* Appuyez sur [t] pour faire un stock.

# Autrices

* **Clara DAIGMORTE**
* **Laurine LAFONTAINE** 

#Graphisme
* **Laurine LAFONTAINE**
