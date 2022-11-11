#include "EDP.h"
#include <math.h>
#include <stdlib.h>

//Créer la matrice qui adapte à la diffusion de la chaleur 1D. x représente le fil et y représente le temps
float** creerMatrice(int dimX,int dimY)
{
    float **mat;
    int i=0;

    mat = malloc(dimY * sizeof(float*));
    for(i=0; i<dimY; i++)
    {
        mat[i]=calloc(dimX, sizeof(float));
    }
    return mat;
}

//Initialiser la température à t=0 pour la diffusion de la chaleur 1D
float** Init_condition_1D(int nb_point,int nb_temps)
{
    float** etat_init;
    int i=0;
    
    etat_init=creerMatrice(nb_point, nb_temps);
    for (i=0; i<nb_point; i++) {
        etat_init[0][i]=290;
    }
    for (i=0; i<nb_temps; i++) {
        etat_init[i][0]=290;
        etat_init[i][nb_point-1]=290;
    }
    
    return etat_init;
}

//valeur_avant = T(x-delta_x,t)
//valeur_centre = T(x,t)
//valeur_arriere = T(x+delta_x,t)
//caculer la dérivée seconde en x
float calculDeriveeSeconde_X (float valeur_avant,float valeur_centre,float valeur_arriere)
{
    float result=0;
    result=( valeur_avant - 2*valeur_centre + valeur_arriere )/( delta_x*delta_x );
    return result;
}

//Calculer la dérivée seconde en y
float calculDeriveeSeconde_Y (float valeur_avant,float valeur_centre,float valeur_arriere)
{
    float result=0;
    result=( valeur_avant - 2*valeur_centre + valeur_arriere )/( delta_y*delta_y );
    return result;
}

//Calculer la diffusion de la chaleur 1D en utilisant la méthode Différences Finies
float** Diffusion_1D(source_1D source,int nb_temps)
{
    int i=0,j=0;
    float** MatResult;
    float valeurDeriveeSeconde=0;
    
    MatResult=Init_condition_1D(nb_points,nb_temps);
    
    //remplir la matrice
    //T(x,t+delta_t) = delta_t*(f+alpha*A) + T(x,t) A est la derivee seconde par rapport au x
    for(i=1; i<nb_temps; i++)
    {
        for(j=1; j<source.nb_point-1; j++)
        {
            valeurDeriveeSeconde=calculDeriveeSeconde_X(MatResult[i-1][j-1],MatResult[i-1][j],MatResult[i-1][j+1]);
            //printf("%.2f ",valeurDeriveeSeconde);
            MatResult[i][j]=MatResult[i-1][j] + delta_t * (alpha_Alu * valeurDeriveeSeconde + source.data[j]);
            //printf("%.2f ",MatResult[i][j]);
        }
        //printf("\n");
    }
    
    return MatResult;
}
//Afficher la diffusion de la chaleur 1D
void Affichage_Diffusion_1D(float** diffusion,int nb_temps,source_1D source)
{
    int i=0,j=0;
    
    for (i=0; i<nb_temps;i++) {
        for (j=0; j<source.nb_point; j++) {
            printf("%.2f ",diffusion[i][j]);
        }
        printf("\n");
    }
    printf("\n");		
}


//Créer la volume qui adapte à la diffusion de la chaleur 2D. x et y représente le plan et z représente le temps
float*** creerVolume(int dimX,int dimY,int dimT)
{
    int i=0,j=0;
    float*** volume;

    volume = malloc(dimX * sizeof(float**));
    for (i=0; i<dimX; i++) {
        volume[i]=malloc(dimY * sizeof(float*));
        for (j=0; j<dimY; j++) {
            volume[i][j]=calloc(dimT, sizeof(float));
        }
    }
    return volume;
    
}

//Initialiser la température à t=0 pour la diffusion de la chaleur 2D
float*** Init_condition_2D(int nb_point_X,int nb_point_Y,int nb_temps)
{
    float*** etat_initial;
    int i=0,j=0,k=0;
    
    etat_initial=creerVolume(nb_point_X, nb_point_Y, nb_temps);

    for (i=1; i<nb_temps; i++) {
        for (j=0;j<nb_point_Y; j++) {
            etat_initial[j][0][i]=290;
            etat_initial[j][nb_point_X-1][i]=290;
        }
        for (k=0;k<nb_point_X; k++) {
            etat_initial[0][k][i]=290;
            etat_initial[nb_point_Y-1][k][i]=290;
        }
        
    }
    for (i=0; i<nb_point_Y; i++) {
        for (j=0; j<nb_point_X; j++) {
            etat_initial[i][j][0]=290;
        }
    }
    return etat_initial;
}

//Calculer la diffusion de la chaleur 2D en utilisant la méthode Différences finies
float*** Diffusion_2D(source_2D source,int nb_temps)
{
    int i=0,j=0,k=0;
    float*** MatResult;
    float valeurDeriveeSeconde_X=0,valeurDeriveeSeconde_Y=0;
    
    MatResult=Init_condition_2D(nb_points, nb_points, nb_temps);

    for(i=1; i<nb_temps; i++)
    {
        for(j=1; j<source.nb_point_Y-1; j++)
        {
            for (k=1; k<source.nb_point_X-1; k++) {
                valeurDeriveeSeconde_X=calculDeriveeSeconde_X(MatResult[k-1][j][i-1],MatResult[k][j][i-1],MatResult[k+1][j][i-1]);
                //printf("%.2f ",valeurDeriveeSeconde_X);
                valeurDeriveeSeconde_Y=calculDeriveeSeconde_Y(MatResult[k][j-1][i-1],MatResult[k][j][i-1],MatResult[k][j+1][i-1]);
                //printf("%.2f ",valeurDeriveeSeconde_Y);
                MatResult[k][j][i]=MatResult[k][j][i-1] + delta_t * (alpha_Alu * (valeurDeriveeSeconde_X + valeurDeriveeSeconde_Y) + source.data[k][j]);
            }
            
            //printf("%.2f ",valeurDeriveeSeconde);
            
            //printf("%.2f ",MatResult[i][j]);
        }

    }
    
    return MatResult;
}

//Caculer le laplacien
float calcul_laplacien(float DeriveeSecondeX, float DeriveeSecondeY)
{
    float result;
    
    result=DeriveeSecondeX+DeriveeSecondeY;
    
    return result;
}


//Calculer la diffusion de la chaleur 2D en utilisant la méthode Runge-Kutta 2
float *** Diffusion_2D_RK2(source_2D source,int nb_temps)
{
    float deltaT_X_avant,deltaT_X_Y_centre,deltaT_X_arriere,deltaT_Y_avant,deltaT_Y_arriere;
    float T_undemi_X_avant,T_undemi_X_Y_centre,T_undemi_X_arriere,T_undemi_Y_avant,T_undemi_Y_arriere;
    float delta_T_undemi;
    int i=0,j=0,k=0,q=0;
    float*** MatResult;
    

    MatResult=Init_condition_2D(nb_points, nb_points, nb_temps);
     for(i=1; i<nb_temps; i++)
     {
        for(j=2; j<source.nb_point_Y-2; j++)
        {
            for (k=2; k<source.nb_point_X-2; k++)
            {
                deltaT_X_avant=calcul_laplacien(calculDeriveeSeconde_X(MatResult[k-2][j][i-1], MatResult[k-1][j][i-1], MatResult[k][j][i-1]),calculDeriveeSeconde_Y(MatResult[k-1][j-1][i-1], MatResult[k-1][j][i-1], MatResult[k-1][j+1][i-1]));//delta T(x-1,y,t)
                
                deltaT_X_Y_centre=calcul_laplacien(calculDeriveeSeconde_X(MatResult[k-1][j][i-1], MatResult[k][j][i-1], MatResult[k+1][j][i-1]),calculDeriveeSeconde_Y(MatResult[k][j-1][i-1], MatResult[k][j][i-1], MatResult[k][j+1][i-1]));//delta T(x,y,t)
                
                deltaT_X_arriere=calcul_laplacien(calculDeriveeSeconde_X(MatResult[k][j][i-1], MatResult[k+1][j][i-1], MatResult[k+2][j][i-1]),calculDeriveeSeconde_Y(MatResult[k+1][j-1][i-1], MatResult[k+1][j][i-1], MatResult[k+1][j+1][i-1]));//delta T(x+1,y,t)
                
                deltaT_Y_avant=calcul_laplacien(calculDeriveeSeconde_X(MatResult[k-1][j-1][i-1], MatResult[k][j-1][i-1], MatResult[k+1][j-1][i-1]),calculDeriveeSeconde_Y(MatResult[k][j-2][i-1], MatResult[k][j-1][i-1], MatResult[k][j][i-1]));//delta T(x,y-1,t)
                
                deltaT_Y_arriere=calcul_laplacien(calculDeriveeSeconde_X(MatResult[k-1][j+1][i-1], MatResult[k][j+1][i-1], MatResult[k+1][j+1][i-1]),calculDeriveeSeconde_Y(MatResult[k][j][i-1], MatResult[k][j+1][i-1], MatResult[k][j+2][i-1]));//delta T(x,y+1,t)
                
                T_undemi_X_arriere=MatResult[k+1][j][i-1]+0.5 * delta_t * (alpha_Alu * deltaT_X_arriere +source.data[k+1][j]);//T1/2(x+1,y)
                T_undemi_X_avant=MatResult[k-1][j][i-1]+0.5 * delta_t * (alpha_Alu * deltaT_X_avant +source.data[k-1][j]);//T1/2(x-1,y)
                T_undemi_X_Y_centre=MatResult[k][j][i-1]+0.5 * delta_t * (alpha_Alu * deltaT_X_Y_centre +source.data[k][j]);//T1/2(x,y)
                T_undemi_Y_arriere=MatResult[k][j+1][i-1]+0.5 * delta_t * (alpha_Alu * deltaT_Y_arriere +source.data[k][j+1]);//T1/2(x,y+1)
                T_undemi_Y_avant=MatResult[k][j-1][i-1]+0.5 * delta_t * (alpha_Alu * deltaT_Y_avant +source.data[k][j-1]);//T1/2(x,y-1)

                delta_T_undemi=calcul_laplacien(calculDeriveeSeconde_X(T_undemi_X_avant, T_undemi_X_Y_centre, T_undemi_X_arriere), calculDeriveeSeconde_Y(T_undemi_Y_avant, T_undemi_X_Y_centre, T_undemi_Y_arriere));//delta T1/2(x,y)
                
                MatResult[k][j][i]=T_undemi_X_Y_centre + 0.5 * delta_t * (alpha_Alu * delta_T_undemi + source.data[k][j]);//T(x,y,t+1)
            }
        }
         for (q=1; q<nb_points-1; q++) {
             MatResult[q][1][i]=290;
             MatResult[q][nb_points-2][i]=290;
         }
         for (q=1; q<nb_points-1; q++) {
             MatResult[1][q][i]=290;
             MatResult[nb_points-2][q][i]=290;
         }
         source.data[(nb_points-1)/2][(nb_points-1)/2]+=0.1;
    }
 return MatResult;
    }

//Afficher la diffusion de la chaleur 2D
void Affichage_Diffusion_2D(float*** diffusion,int nb_temps,source_2D source)
{
    int i=0,j=0,k=0;
    
    for (i=0; i<nb_temps; i++) {
        for (j=0; j<source.nb_point_Y; j++) {
            for (k=0; k<source.nb_point_X; k++) {
                printf("%.2f ",diffusion[k][j][i]);
            }
            printf("\n");
        }
        printf("\n");
    }
}


//Écrire les valeurs de diffusion 1D dans le fichier
void ecrireFichier_Diffuion1D(char *fName,float** diffusion,source_1D source)
{
    FILE *ftxt=NULL;
    int i,j;
    
    ftxt=fopen(fName,"w");
    if (ftxt!=NULL)
    {
        printf("OK!\n");
        for(i=0; i<nb_delta_t; i++)
        {
            for(j=0; j<source.nb_point; j++)
            {
                fprintf(ftxt,"%f ",diffusion[i][j]);
            }
            fprintf(ftxt,"\n");
        }
    }
    fclose(ftxt);
}

//Écrire les valeurs de diffusion 2D dans le fichier
void ecrireFichier_Diffuion2D(char *fName,float*** diffusion,source_2D source)
{
    FILE *ftxt=NULL;
    int i,j,k;
    
    ftxt=fopen(fName,"w");
    if (ftxt!=NULL)
    {
        printf("OK!\n");
        /*for(i=0; i<nb_delta_t; i++)
        {
            for(j=0; j<source.nb_point_Y; j++)
            {
                for (k=0; k<source.nb_point_X; k++) {
                    fprintf(ftxt,"%f ",diffusion[k][j][i]);
                }
                fprintf(ftxt, "\n");
            }
            fprintf(ftxt,"\n");
        }*/
        for(j=0; j<source.nb_point_Y; j++)
        {
            for (k=0; k<source.nb_point_X; k++) {
                fprintf(ftxt,"%f ",diffusion[k][j][nb_delta_t-1]);
            }
            fprintf(ftxt, "\n");
        }
    }
    fclose(ftxt);
}
