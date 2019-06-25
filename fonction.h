/* fonction.h
test grain de sable

Created by Manuel Konrath on 22/06/2019.
Copyright © 2019 Manuel Konrath. All rights reserved.*/


#ifndef fonction_h
#define fonction_h
#define TAILLE_MAX 1000

#include <stdio.h>

typedef struct structureGrille structureGrille;
struct structureGrille
{
    int centreX;
    int centreY;
    int nbCaracteres;
    int nbLignes;
};

typedef struct Sommet Sommet;
struct Sommet
{
    int position;
};

void printHelp(char * prgName);

void printError(char * prgName, char * errStr);

int verifGrille(structureGrille* pointeurStructGrille, FILE* file);

void analyseGrille (char *grille, structureGrille* pointeurStructGrille);

void initialiserStructGrille(structureGrille* grille);

void initialiserSommet(Sommet* max);

void ajouterGrain (char *grille, const int positionAjoutGrain);

void chercherSommet (char *grille, Sommet* sommet, int* nbSommet);

void eboulement(char *grille, Sommet sommet, structureGrille structureGrille);

#endif /* fonction_h */

