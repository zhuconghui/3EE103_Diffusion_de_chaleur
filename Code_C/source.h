#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int nb_point;
    float* data;
}source_1D;

typedef struct{
    int nb_point_X;
    int nb_point_Y;
    float** data;
}source_2D;

source_1D creer_source1D_ponctuelle(int nb_point);//Création de la source 1D ponctuelle. la position de la source est au milieu
source_2D creer_source2D_ponctuelle(int nb_point_X,int nb_point_Y);//Création de la source 2D ponctuelle. la position de la source est au centre
source_2D creer_source2D_lineaire(int nb_point_X,int nb_point_Y);//Création de la source 2D linéaire. la position de la source est la colonne au milieu
source_2D variation_source(source_2D source);//Fonction pour rendre une source 2D varaible
void affichage_source1D(source_1D source);//Afficher la source 1D dans la console
void affichage_source2D(source_2D source);//Afficher la source 2D dans la console
void freeSource1D(source_1D source);//Libérer l'espace alloué
void freeSource2D(source_2D source);//Libérer l'espace alloué
#endif // SOURCE_H_INCLUDED
