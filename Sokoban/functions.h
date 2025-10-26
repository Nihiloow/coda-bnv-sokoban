#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Structures :

typedef struct pos {
    int pos_x;
    int pos_y;
} position; // Alternative ChatGPT qui fonctionne aussi


// Fonctions :

void init_position(position *objet);

void init_value(position *player, position *box, position *mark);

void affiche_map(position *player, position *box, position *mark);

void mouvement_player(position *player, position *box, int map[10][10], char direction);

int boite_corner(position *box, int map[10][10]);

void map_save(position *player, position *box, position *mark);

#endif
