/* fonction.c
grainDeSable

Created by Manuel Konrath on 19/06/2019.
Copyright © 2019 Manuel Konrath. All rights reserved.*/


#include "fonction.h"

/* Afficher l'aide du programme*/
void printHelp(char * prgName) {
    printf("%s\n", prgName);
    printf("The goal of this project is to develop an hour-glass when looked from above.\nLet’s imagine a rectangular grid, with each square containing grains of sand.\nWhen there are at least four grains of sand in the same square, it becomes unstable.\nIt will then distribute a grain of sand into each of the 4 neighboring squares, and its own number will decrease by 4.\nOne collapse can lead to another, which will create a chain reaction\n\n");
    printf(" Usage:\n");
    printf(" %s <fileName> <string> <nbIterations>\n", prgName);
    printf(" where:\n");
    printf(" <fileName> is the name of the file that contains the initial grid.\n");
    printf(" <string> is a string containing 4 characters (no more no less) used to represent the number of grains of sand in a cell.\n");
    printf(" <nbIterations> is the number of iterations to apply on the supplied grid.");
}

/* Affiche l'erreur errStr, puis l'aide du programme */
void printError(char * prgName, char * errStr) {
   printf("Error : '%s'\n", errStr);
   printHelp(prgName);
}


void initialiserStructGrille(structureGrille* grille)
{
    grille->centreX = 0;
    grille->centreY = 0;
    grille->nbCaracteres = 0;
    grille->nbLignes = 0;
}

void initialiserSommet(Sommet* max)
{
    max->position = -1;
}

int verifGrille(structureGrille* pointeurStructGrille, FILE* file )
{
    
    int caractere = 0;
    int nbCaractere = 0;
    int nbLigne = 0;
    int nbCaractereLigne1 = 0;
    int nbCaractereLigne2 = 0;
    

    /*Test validité de la grille :*/
    do
    {
        caractere = fgetc(file);
        /*test caractères :*/
        if (caractere != '0' && caractere != '1' && caractere != '2' && caractere != '3' && caractere != '\n' && caractere != EOF) {
            perror("Grille non valide : caractère non compris entre 0 et 3\n");
            return 0;
        }
        /*test si le nbr de caracteres par ligne est identique*/
        nbCaractere += 1;
        
        if (caractere == '\n'){
            nbLigne += 1;
            if (nbLigne == 1){
                nbCaractereLigne1 = nbCaractere;
            } else if (nbLigne > 1) {
                nbCaractereLigne2 = nbCaractere;
                if(nbCaractereLigne2 != nbCaractereLigne1) {
                    perror("Grille non valide : longueur lignes non identique");
                    return 0;
                }
            }
            nbCaractere = 0;
        }
    } while(caractere != EOF);
    
    if (nbLigne * nbCaractereLigne1 > TAILLE_MAX - 1 ) {
        perror("Grille non valide : trop grande");
        return 0;
    }
    
    if (nbLigne == 1 && nbCaractereLigne1 == 2) {
        perror("Grille non valide : trop petite");
        return 0;
    }
    
    pointeurStructGrille->nbLignes = nbLigne;
    pointeurStructGrille->nbCaracteres = nbCaractereLigne1;
    return 1;
}


void analyseGrille (char *grille, structureGrille* pointeurStructGrille){
    int milieuHorizontal = 0, milieuVertical = 0;
    int nbCaractParLigne = 0;
    int nbLigne = 0, i = 0;
    int reste = 0;
    
    /*compte le nombre de caractère par ligne dans la grille*/
    while(grille[nbCaractParLigne] != '\n'){
        nbCaractParLigne++;
    }
    
    /*compte le nombre de ligne dans la grille*/
    while(grille[i] != '\0'){
        if(grille[i] == '\n') {
            nbLigne += 1;
        }
        i++;
    }
    
    /*Calcul du milieu Vertical Y*/
    reste = nbLigne % 2;
    milieuVertical = nbLigne / 2 ;
    pointeurStructGrille->centreY = milieuVertical + reste ;
    
    /*Calcul du milieu Horizontal X*/
    reste = nbCaractParLigne % 2;
    milieuHorizontal = nbCaractParLigne / 2 ;
    pointeurStructGrille->centreX = milieuHorizontal + reste ;
}

void ajouterGrain (char *grille, const int positionAjoutGrain) {
    grille[positionAjoutGrain] += 1;
}


void chercherSommet (char *grille, Sommet* sommet, int* nbSommet){
    int i = 0;
    *nbSommet = 0;
    while(grille[i]!='\0') {
        if(grille[i] >= '4' && grille[i] != '\n'){
            *nbSommet += 1;
            sommet->position = i;
        }
        i++;
    }
}


void eboulement(char *grille, Sommet sommet, structureGrille structureGrille){
    /*Si la grille est sur une seule ligne :*/
    if (structureGrille.nbLignes == 1){
        /*coin haut gauche*/
        if(sommet.position == 0) {
            grille[sommet.position + 1] += 1;
            grille[sommet.position] -= 4;
            /*coin droit*/
        } else if (sommet.position <= structureGrille.nbCaracteres && grille[sommet.position +1] == '\n') {
            grille[sommet.position - 1] += 1;
            grille[sommet.position] -= 4;
        } else {
            grille[sommet.position - 1] += 1;
            grille[sommet.position + 1] += 1;
            grille[sommet.position] -= 4;
        }
        /* Si la grille est sur une seule colonne :*/
    } else if (structureGrille.nbCaracteres == 2 && structureGrille.nbLignes > 1) {
        /*coin haut*/
        if(sommet.position == 0) {
            grille[sommet.position + structureGrille.nbCaracteres] += 1;
            grille[sommet.position] -= 4;
            /* coin bas*/
        }  else if (grille[sommet.position +2] == '\0' ) {
            grille[sommet.position - structureGrille.nbCaracteres] += 1;
            grille[sommet.position] -= 4;
        } else {
            grille[sommet.position - structureGrille.nbCaracteres] += 1;
            grille[sommet.position + structureGrille.nbCaracteres] += 1;
            grille[sommet.position] -= 4;
        }
        
    } else {
        /*coin haut gauche*/
        if(sommet.position == 0) {
            grille[sommet.position + 1] += 1;
            grille[sommet.position + structureGrille.nbCaracteres] += 1;
            grille[sommet.position] -= 4;
            /*coin haut droit*/
        } else if (sommet.position <= structureGrille.nbCaracteres && grille[sommet.position +1] == '\n') {
            grille[sommet.position - 1] += 1;
            grille[sommet.position + structureGrille.nbCaracteres] += 1;
            grille[sommet.position] -= 4;
            /*premiere ligne*/
        } else if (sommet.position < structureGrille.nbCaracteres - 1 ) {
            grille[sommet.position - 1] += 1;
            grille[sommet.position + 1] += 1;
            grille[sommet.position + structureGrille.nbCaracteres] += 1;
            grille[sommet.position] -= 4;
            /*coin bas gauhe*/
        } else if (grille[sommet.position -1] == '\n' && grille[sommet.position + structureGrille.nbCaracteres] == '\0') {
            grille[sommet.position - structureGrille.nbCaracteres] += 1;
            grille[sommet.position + 1] += 1;
            grille[sommet.position] -= 4;
            /*premiere colonne gauche*/
        } else if (grille[sommet.position -1] == '\n') {
            grille[sommet.position - structureGrille.nbCaracteres] += 1;
            grille[sommet.position + 1] += 1;
            grille[sommet.position + structureGrille.nbCaracteres] += 1;
            grille[sommet.position] -= 4;
            /*coin bas droit*/
        } else if (grille[sommet.position +2] == '\0' ) {
            grille[sommet.position - 1] += 1;
            grille[sommet.position - structureGrille.nbCaracteres] += 1;
            grille[sommet.position] -= 4;
            /*dernière colonne droite*/
        } else if (grille[sommet.position +1] == '\n') {
            grille[sommet.position - 1] += 1;
            grille[sommet.position + structureGrille.nbCaracteres] += 1;
            grille[sommet.position - structureGrille.nbCaracteres] += 1;
            grille[sommet.position] -= 4;
            /*dernière ligne*/
        } else if (sommet.position > (structureGrille.nbLignes) * structureGrille.nbCaracteres){
            grille[sommet.position - 1] += 1;
            grille[sommet.position + 1] += 1;
            grille[sommet.position - structureGrille.nbCaracteres] += 1;
            grille[sommet.position] -= 4;
            /*les autres cas sans contraintes*/
        } else {
            grille[sommet.position - 1] += 1;
            grille[sommet.position + 1] += 1;
            grille[sommet.position - structureGrille.nbCaracteres] += 1;
            grille[sommet.position + structureGrille.nbCaracteres] += 1;
            grille[sommet.position] -= 4;
        }
    }
}




