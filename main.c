/* main.c
test grain de sable

Created by Manuel Konrath on 21/06/2019.
Copyright © 2019 Manuel Konrath. All rights reserved.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"


int main(int argc, char *argv[]) {

    
    int nbIterations = 0;
    char *fileName;
    char *chaineAffichage = NULL;
    FILE *file = NULL;
    int i = 0;
    
    structureGrille Grille;
    structureGrille *pointeurStructGrille = &Grille;
    
    /* Affichage de l'aide */
    if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0) {
            printHelp(argv[0]);
            return EXIT_SUCCESS;
        }
    }
    
    /* Parsing des arguments : */
    if(argc < 3 || argc > 4) {
        printError( argv[0], "number of args invalid" );
        return 84;
    }

    /* Affecter le nom du fichier */
    fileName = argv[1];
    
    /* chaine d'affichage */
    if (strlen(argv[2]) != 4) {
        printError (argv[0], "number of caracters for <string> invalid");
        return 84;
    }
    
    chaineAffichage = argv[2];
    
    /*Nombre d'iterations */
    if (sscanf(argv[3], "%d", &nbIterations) != 1) {
        printError (argv[0], "Integer awaited");
        return 84;
    }
    if (nbIterations <= 0) {
        printError (argv[0], "Positive Integer awaited");
        return 84;
    }
    

    initialiserStructGrille(pointeurStructGrille);
    
    
    file = fopen(fileName, "r");
    if (file == NULL)
    {
        perror("Cannot open filename: ");
        return 84;
    }
    
    if(verifGrille(pointeurStructGrille, file)){
        int nbSommet = 0;
        int *pnbSommet = &nbSommet;
        Sommet max;
        Sommet *pointeurSommet = &max;
        int positionAjoutGrain = 0;
        char map[TAILLE_MAX] = {0};
        char map2[TAILLE_MAX] = {0};
        char *p = map;
        char caractereLu = 0;
        
        /*On récupère les données du fichier si la grille est conforme*/
        if (file == NULL) {
            printf("Impossible de charger le fichier ");
        }
        
        rewind(file);
        if (file != NULL) {
            while (fgets(map2, TAILLE_MAX, file) != NULL){
                strcat(map, map2);
            }
        }
        fclose(file);
        
        
        initialiserSommet(pointeurSommet);
        
        /*récupère la position du centre de la grille :*/
        analyseGrille(map, pointeurStructGrille);
        
        /*ajouter un grain au centre et éboulement*/
       positionAjoutGrain = (Grille.nbCaracteres * (Grille.centreY -1)) + Grille.centreX -1;

        for(i = 0; i < nbIterations; i++ ){
            ajouterGrain(p, positionAjoutGrain);
            do {
                chercherSommet(p, pointeurSommet, pnbSommet);
                if(nbSommet > 0) {
                    eboulement(p, max, Grille);
                }
            } while(nbSommet != 0);
        }
        
        /*affichage de la grille finale :*/
        i = 0;
        do {
            caractereLu = map[i];
            i++;
            
            switch (caractereLu) {
                    
                case '0' :
                    printf("%c", chaineAffichage[0]);
                    break;
                case '1' :
                    printf("%c", chaineAffichage[1]);
                    break;
                case '2' :
                    printf("%c", chaineAffichage[2]);
                    break;
                case '3' :
                    printf("%c", chaineAffichage[3]);
                    break;
                case '\n' :
                    printf("%c", caractereLu);
                    break;
                case '\0' :
                    printf("%c\n", caractereLu);
                    break;
            }
            
        } while (caractereLu != '\0');
        
        return 0;
    } else {
        return 84;
    }
}
