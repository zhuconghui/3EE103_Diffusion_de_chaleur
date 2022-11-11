#include <stdio.h>
#include <stdlib.h>
#include "EDP.h"
#include "source.h"
#define fNameIn "/Users/zhuconghui/Desktop/Diffusion de chaleur/Diffusion de chaleur/SourcePonctuelle.txt"
#define fNameOut "/Users/zhuconghui/Desktop/Diffusion de chaleur/Diffusion de chaleur/Diffusion.txt"

int main()
{
    //source_1D source;
    //float** diffusion;
    source_2D source;
    float*** diffusion;
    
    //source=creer_source1D_ponctuelle(nb_points);
    //diffusion=Diffusion_1D(source,nb_delta_t);
    //Affichage_Diffusion_1D(diffusion,nb_delta_t,source);
    
    //source=creer_source2D_lineaire(nb_points, nb_points);
    //affichage_source2D(source);
    //diffusion=Diffusion_2D_DF(source, nb_delta_t);
    //Affichage_Diffusion_2D(diffusion, nb_delta_t, source);
    
    //source=creer_source2D_ponctuelle(nb_points, nb_points);
    //affichage_source2D(source);
    //diffusion=Diffusion_2D_DF(source, nb_delta_t);
    //Affichage_Diffusion_2D(diffusion, nb_delta_t, source);
    
    
    source=creer_source2D_ponctuelle(nb_points, nb_points);
    //affichage_source2D(source);
    diffusion=Diffusion_2D_RK2(source, nb_delta_t);
    Affichage_Diffusion_2D(diffusion, nb_delta_t, source);
    
    ecrireFichier_Diffuion2D(fNameOut, diffusion, source);
    //ecrireFichier_Diffuion1D(fNameOut, diffusion, source);
    
    return 0;
}
	
