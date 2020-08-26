#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdbool.h>
#define MAXPARTICLES 100000
#define MAXSWEEP 100000
#define MAXDISPLACEMENT 10000

//double DeltaE( double x );

int main(int argc, char *argv[]){
	
	//Physical variables
	int Boltzmann_const = 1;
	double Temperature;
	double DeltaE;
	int check_time = 1;
	int MaxRight,MaxLeft;
	int DisplacementNeg[MAXDISPLACEMENT],DisplacementPos[MAXDISPLACEMENT];
	int *Particles;
	//double *Particles_New;

	Particles = (int*)malloc(MAXPARTICLES*sizeof(int));
	//Particles_New = (double*)malloc(MAXPARTICLES*sizeof(double));
	
	//Normal variables
	int i,j,k;
	char Buffer[30];
	char *File_Distribution;
	FILE *Distribution_File;

	printf("Enter the Temperature...\n");
	scanf("%lf",&Temperature);

	//initialising the particle location
	for(j=0;j<MAXPARTICLES;j++)
		Particles[j] = 0;
	
	srand((unsigned)time(NULL));
	check_time = 1;
	//simulation starts
		for(i=0;i<MAXSWEEP;i++){
	//randomly allocating the locations of particles
			for(j=0;j<MAXPARTICLES;j++){

	if( rand() > RAND_MAX/2 ){  /// move toward right-hand side

		DeltaE = cos( Particles[j] + 1) - cos ( Particles[j] );
	
		if( (double)exp( -DeltaE/((Boltzmann_const)*(Temperature)) )	> (double)rand()/RAND_MAX ) {
						Particles[j]++; } 
			}
	else{ 			   /// move toward left-hand side
		DeltaE = cos( Particles[j] - 1) - cos( Particles[j] );
			
	if( (double)exp( -DeltaE/((Boltzmann_const)*(Temperature)) )	> (double)rand()/RAND_MAX ) { 
					Particles[j]--; }
			}	
		}
	File_Distribution = "Distribution";
	if( i%(int)pow(2,check_time) == 0 ){
		sprintf(Buffer,"%s_%d", File_Distribution, check_time);

		printf("check point %d\tdone\n", i);
	
		check_time++;
	
		Distribution_File = fopen(Buffer,"w");
			fprintf(Distribution_File,"#Time passed : %d\t%lfK\n", i, Temperature);

	////// initialising the positions of Particles
	for(k=0;k<MAXDISPLACEMENT;k++){
		DisplacementNeg[k] = 0;
		DisplacementPos[k] = 0;	}

	MaxRight = 0; 
	MaxLeft  = 0;

		for(j=0;j<MAXPARTICLES;j++){
			
			if( Particles[j] >= 0 ){
				DisplacementPos[ Particles[j] ] += 1;////val of Dis* >>> notates size of histogram
				if( Particles[j] >= MaxRight )
					MaxRight = Particles[j];
			}

			else{
				DisplacementNeg[ -Particles[j] ] += 1;

				if( -Particles[j] >= MaxLeft )
				       MaxLeft = -Particles[j];
			}
		}
	
		for(k=MaxLeft;k>0;k--){
			if(DisplacementNeg[k] > 0)
				fprintf(Distribution_File,"%d\t%d\n", -k,DisplacementNeg[k]);
		}
		for(k=0;k<=MaxRight;k++){
			if(DisplacementPos[k] > 0)
				fprintf(Distribution_File,"%d\t%d\n", k,DisplacementPos[k]);
		}
		fclose(Distribution_File);
		}///end of data printing

		}//end of sweep

		free(Particles);

			return 0;
}


				
			
		
	//end of sweep

		/*/DeltaE = cos( Particle[j] + or - 1 ) - cos( Particles[j] ) ??
double DeltaE( double x ){
	if ( rand() > RAND_MAX/2 )

		return cos( Particle[j] + 1 ) - cos( Particle[j] );
	else
		return cos( Particle[j] - 1 ) - cos( Particle[j] );	
}
*/
