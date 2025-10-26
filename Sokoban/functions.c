#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void init_position(position *objet) 
{
    objet->pos_x = rand() % 8 + 1;
    objet->pos_y = rand() % 8 + 1;
}

void init_value(position *player, position *box, position *mark) 
{
    do { // Suggestion de ChatGPT pour éviter les chevauchements

        init_position(player);
        init_position(box);
        init_position(mark);

    } while (

        // Pas de chevauchement

        (player->pos_x == box->pos_x && player->pos_y == box->pos_y) ||
        (player->pos_x == mark->pos_x && player->pos_y == mark->pos_y) ||
        (box->pos_x == mark->pos_x && box->pos_y == mark->pos_y) ||

        // Pas de boîte dans un coin

        ((box->pos_x == 1 && box->pos_y == 1) ||
         (box->pos_x == 1 && box->pos_y == 8) ||
         (box->pos_x == 8 && box->pos_y == 1) ||
         (box->pos_x == 8 && box->pos_y == 8))
    );
}

void affiche_map(position *player, position *box, position *mark) 
{
    int map[10][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    }; // 1 pour mur, 0 pour case vide

    printf("\n-- Coordonnées --\nJoueur (o) : (%d, %d)\nBoîte (X) : (%d, %d)\nMarque (+) : (%d, %d)\n\n",player->pos_x, player->pos_y, box->pos_x, box->pos_y,mark->pos_x, mark->pos_y);
    
    int i = 0;

    while (i < 10) 
    {
        int j = 0;

        while (j < 10) 
        {
            if (i == player->pos_y && j == player->pos_x)
            {
                printf("o"); // joueur
            }

            else if (i == box->pos_y && j == box->pos_x)
            {
                printf("X"); // boîte
            }

            else if (i == mark->pos_y && j == mark->pos_x)
            {
                printf("+"); // marque
            }

            else if (map[i][j] == 1)
            {
                printf("#"); // mur
            }

            else
            {
                printf(" "); // case vide
            }

            j++;
        }

        printf("\n");

        i++;
    }
}

void mouvement_player(position *player, position *box, int map[10][10], char direction) 
{
    int next_x = player->pos_x;
    int next_y = player->pos_y;

    if (direction == 'z') 
    {
        next_y--; // haut
    }

    if (direction == 's') 
    {
        next_y++; // bas
    }

    if (direction == 'q') 
    {
        next_x--; // gauche
    }

    if (direction == 'd') 
    {
        next_x++; // droite
    }

    if (map[next_y][next_x] == 1) 
    {
        return; // Mur, on ne bouge pas
    }

    if (next_x == box->pos_x && next_y == box->pos_y) 
    {
        int box_next_x = box->pos_x;
        int box_next_y = box->pos_y;

        if (direction == 'z') 
        {
            box_next_y--;
        }

        if (direction == 's') 
        {
            box_next_y++;
        }

        if (direction == 'q') 
        {
            box_next_x--;
        }

        if (direction == 'd') 
        {
            box_next_x++;
        }

        if (map[box_next_y][box_next_x] == 1) 
        {
            return;
        }

        box->pos_x = box_next_x;
        box->pos_y = box_next_y;
    }

    player->pos_x = next_x;
    player->pos_y = next_y;
}

int boite_corner(position *box, int map[10][10]) // Petit souci dans le cas où la boîte est contre un mur dès le départ et que la marque n'est pas atteignable (axe d'amélioration)
{
    int x = box->pos_x;
    int y = box->pos_y;

    // Coin haut-gauche

    if (map[y-1][x] == 1 && map[y][x-1] == 1) 
    {
        return 1;
    }

    // Coin haut-droit

    if (map[y-1][x] == 1 && map[y][x+1] == 1)
    {
        return 1;
    }

    // Coin bas-gauche

    if (map[y+1][x] == 1 && map[y][x-1] == 1) 
    {
        return 1;
    }

    // Coin bas-droit

    if (map[y+1][x] == 1 && map[y][x+1] == 1) 
    {
        return 1;
    }

    return 0; // Pas bloquée
}

void map_save(position *player, position *box, position *mark) 
{
    // Map initial :

    int map[10][10] = {
        {1,1,1,1,1,1,1,1,1,1}, // 1 pour mur
        {1,0,0,0,0,0,0,0,0,1}, //  0 pour case vide
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };  

    // Mode w pour changer le contenu du fichier

    FILE *fp = fopen("end.txt", "w");

    if (fp == NULL) // Si le fichier ne s'ouvre pas (ChatGPT)
    {
        printf("Erreur : impossible d'ouvrir end.txt\n"); 
        return;
    }

    // Écriture ligne par ligne :

    int i = 0;

    while (i < 10) 
    {
        int j = 0;

        while (j < 10) 
        {
            if (i == player->pos_y && j == player->pos_x)
            {
                fprintf(fp, "o");  // joueur
            }

            else if (i == box->pos_y && j == box->pos_x)
            {
                fprintf(fp, "X");  // boîte
            }

            else if (i == mark->pos_y && j == mark->pos_x)
            {
                fprintf(fp, "+");  // marque (que je trouve plus jolie que le .)
            }

            else if (map[i][j] == 1)
            {    
                fprintf(fp, "#");  // mur
            }

            else
            {
                fprintf(fp, " ");  // case vide
            }

            j++;
        }

        fprintf(fp, "\n");

        i++;
    }
  
    fclose(fp); // Fermer le fichier
}