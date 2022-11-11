#include "source.h"
#include "EDP.h"

//Création de la source 1D ponctuelle. la position de la source est au milieu
source_1D creer_source1D_ponctuelle(int nb_point)
{
    source_1D source;
    
    source.data=malloc(nb_point*sizeof(float));
    source.data[(nb_point-1)/2]=1;
    source.nb_point=nb_point;
    
    return source;
}

//Création de la source 2D ponctuelle. la position de la source est au centre
source_2D creer_source2D_ponctuelle(int nb_point_X,int nb_point_Y)
{
    source_2D source;
    int i=0;
    
    source.nb_point_X=nb_point_X;
    source.nb_point_Y=nb_point_Y;
    
    source.data=malloc(nb_point_Y * sizeof(float));
    for (i=0; i<nb_point_Y; i++)
        {
            source.data[i]=calloc(nb_point_X, sizeof(float));
        }
    source.data[(nb_point_X-1)/2][(nb_point_Y-1)/2]=7;
    
    return source;
}

//Création de la source 2D linéaire. la position de la source est la colonne au milieu
source_2D creer_source2D_lineaire(int nb_point_X,int nb_point_Y)
{
    source_2D source;
    int i=0;
    
    source.nb_point_X=nb_point_X;
    source.nb_point_Y=nb_point_Y;
    
    source.data=malloc(nb_point_Y * sizeof(float));
    for (i=0; i<nb_point_Y; i++)
        {
            source.data[i]=calloc(nb_point_X, sizeof(float));
        }
    
    for (i=0; i<nb_point_X; i++)
        {
            source.data[(nb_point_Y-1)/2][i]=5;
        }
    
    /*for (i=0; i<nb_point_Y; i++)
        {
            source.data[i][(nb_point_X-1)/2]=1;
            //printf("%.2f ",source.data[i][3]);
        }*/
    return source;
}

//Fonction pour rendre une source 2D varaible
source_2D variation_source(source_2D source)
{
    source_2D result;
    
    result.nb_point_X=source.nb_point_X;
    result.nb_point_Y=source.nb_point_Y;
    result.data[(nb_points-1)/2][(nb_points-1)/2]=source.data[(nb_points-1)/2][(nb_points-1)/2]+0.1;
    
    return result;
}

//Afficher la source 1D dans la console
void affichage_source1D(source_1D source)
{
    int i=0;
    for (i=0; i<source.nb_point; i++)
        {
            printf("%.2f ",source.data[i]);
        }
    printf("\n");
}

//Afficher la source 2D dans la console
void affichage_source2D(source_2D source)
{
    int i=0,j=0;
    for (i=0; i<source.nb_point_Y; i++)
        {
            for (j=0; j<source.nb_point_X; j++) {
                printf("%.2f ",source.data[i][j]);
            }
            printf("\n");
        }
    printf("\n");
}

//Libérer l'espace alloué
void freeSource1D(source_1D source)
{
    free(source.data);
}

//Libérer l'espace alloué
void freeSource2D(source_2D source)
{
    int i=0;
    for (i=0; i<source.nb_point_Y; i++) {
        free(source.data[i]);
    }
    free(source.data);
    source.data=NULL;
}
