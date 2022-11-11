#ifndef EDP_h
#define EDP_h

#include <stdio.h>
#include "source.h"

#define nb_points 35
#define delta_x 0.05
#define delta_y 0.05
#define delta_t 5
#define nb_delta_t 100
#define alpha_Alu 0.0001127214
#define alpha_Cuivre 0.000113436
#define alpha_Air 0.0000215588

//Structure pour caractériser les paramètre de matériau
typedef struct{
    float K;
    float C;
    float rou;
}materiel;

float** creerMatrice(int dimX,int dimY);//Créer la matrice qui adapte à la diffusion de la chaleur 1D. x représente le fil et y représente le temps
float** Init_condition_1D(int nb_point,int nb_temps);//Initialiser la température à t=0 pour la diffusion de la chaleur 1D
float calculDeriveeSeconde_X (float valeur_avant,float valeur_centre,float valeur_arriere);//caculer la dérivée seconde en x
float calculDeriveeSeconde_Y (float valeur_avant,float valeur_centre,float valeur_arriere);//Calculer la dérivée seconde en y
float** Diffusion_1D(source_1D source,int nb_temps);//Calculer la diffusion de la chaleur 1D en utilisant la méthode Différences Finies
void Affichage_Diffusion_1D(float** difussion,int nb_temps,source_1D source);//Afficher la diffusion de la chaleur 1D


float*** creerVolume(int dimX,int dimY,int dimT);//Créer la volume qui adapte à la diffusion de la chaleur 2D. x et y représente le plan et z représente le temps
float*** Init_condition_2D(int nb_point_X,int nb_point_Y,int nb_temps);//Initialiser la température à t=0 pour la diffusion de la chaleur 2D
float*** Diffusion_2D_DF(source_2D source,int nb_temps);//Calculer la diffusion de la chaleur 2D en utilisant la méthode Différences finies
float calcul_laplacien(float DeriveeSecondeX, float DeriveeSecondeY);//Caculer le laplacien
float*** Diffusion_2D_RK2(source_2D source,int nb_temps);//Calculer la diffusion de la chaleur 2D en utilisant la méthode Runge-Kutta 2
void Affichage_Diffusion_2D(float*** diffusion,int nb_temps,source_2D source);//Afficher la diffusion de la chaleur 2D

void ecrireFichier_Diffuion1D(char *fName,float** diffusion,source_1D source);//Écrire les valeurs de diffusion 1D dans le fichier
void ecrireFichier_Diffuion2D(char *fName,float*** diffusion,source_2D source);//Écrire les valeurs de diffusion 2D dans le fichier
#endif // EDP_h
