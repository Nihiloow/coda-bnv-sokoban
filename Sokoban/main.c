#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main() {
    
    char pseudo[50];

    printf("Bienvenue dans Sokoban ! Quel est votre pseudo ?\n");
    scanf("%s", pseudo);

    printf("\nBonjour %s ! Lançons une partie de Sokoban :\n", pseudo);
    
    srand(time(NULL)); // Nécessaire pour la fonction rand()

    // Définition des positions

    position player, box, mark;
    init_value(&player, &box, &mark);

    // Map fixe avec murs

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
    };

    char move; // Stocke le déplacement du joueur

    while (1) { //1 = vrai

        // Affichage de la map

        affiche_map(&player, &box, &mark);

        // Condition de victoire

        if (box.pos_x == mark.pos_x && box.pos_y == mark.pos_y) 
        {
            printf("\nFélicitations ! Vous avez gagné.\n"); // Bien joué !
            break;
        }

        // Condition de défaite

        if (boite_corner(&box, map)) 
        {
            printf("\nLa boîte est bloquée dans un coin. Vous avez perdu !\n");
            break;
        }

        // Lecture du déplacement

        printf("\nChoisissez un mouvement : Haut(z) Bas(s) Gauche(q) Droite(d) Quitter(x) :\n");
        scanf(" %c", &move);  // L'espace avant %c ignore les retours à la ligne (ChatGPT)

        if (move == 'x') 
        {
            break;
        }

        mouvement_player(&player, &box, map, move);
    }
    
    map_save(&player, &box, &mark); // Sauvegarde de l'état du plateau dans end.txt
    
    printf("\nVotre partie est enregistrée dans le fichier end.txt !\n");

    printf("\nMerci d'avoir joué !");

    exit(0);
}
