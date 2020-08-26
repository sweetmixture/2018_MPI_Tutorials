#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdbool.h>
#define MaxParticles 100000
#define MaxCycles  10000
#define MaxDisplacement 10000

int main(int argc, char *argv[])
{
    clock_t start, end;

	int Boltzmann_const = 1;
	int DeltaE=1;///Potential Energy Barrier _|_|_|_|_|_
	int i,j,k;
	int pow_time = 1;
	int Particles[MaxParticles];
	float Temperature;
	char *FileDistribution;
	char Buffer[40];
	FILE *Distribution_File;
	int MaxRight, MaxLeft;
	int DisplacementNeg[MaxDisplacement], DisplacementPos[MaxDisplacement];
	
	printf(" Enter the Temperature want to scrutinise...\n");
	scanf("%f",&Temperature);

	/////// initialising the walkes
	for(j=0;j<MaxParticles;j++)
		Particles[j] = 0;

	srand((unsigned)time(NULL)); pow_time = 1;
	///////////////////simulation starts
    
    start = clock();

    for(i=0;i<MaxCycles;i++)
    {

        for(j=0;j<MaxParticles;j++)
        {

		//	DeltaE = (float)rand()/RAND_MAX;// Random?
		//Metropolis??
			if( (float)exp(-DeltaE/((Boltzmann_const)*(Temperature))) > (float)rand()/RAND_MAX )
            { //Accept 
				
					if( rand() < RAND_MAX/2 )
						Particles[j]++;	
					
					else	Particles[j]--;
			}
			//else Deny
			///printf("%d\n",Particles[j]);
	    }
	    FileDistribution = "Distribution";

        if( i%(int)(pow(2,pow_time)) == 0 )					/////	
            sprintf(Buffer,"%s_%d", FileDistribution, pow_time);		/////!!!!!!!!!!!!!!!


		printf("checkpoint\t%d done  \n", i);
	
	
		pow_time++;
		Distribution_File	= fopen(Buffer,"w"); ////file name "saved sentence in Buffer
		fprintf(Distribution_File,"#Time(Passed) : %d\t%lfK\n", i, Temperature);
		//initialise the positions of particles
		for(k=0;k<MaxDisplacement;k++)
		{	DisplacementPos[k] = 0;
			DisplacementNeg[k] = 0; }
		
		MaxRight = 0; MaxLeft = 0;
		//////////////////////////////////////////////////////
		for(j=0;j<MaxParticles;j++)
        {
			if( Particles[j] > 0 )
            {
		    	DisplacementPos[ Particles[j] ] += 1;
				if( Particles[j] > MaxRight )
					MaxRight = Particles[j];
		    }
			else
            {
				DisplacementNeg[ -Particles[j] ] += 1;
				//if(j%1000==0) printf("%d\t%d\n", Particles[j], MaxLeft);
				if( -Particles[j] > MaxLeft )
					MaxLeft = -Particles[j];

		//printf("checkpoint\t%d done  \n", i);
			}
		}
		//printf("%d\n", MaxLeft);
		//////////////////////////////////////////////////////
		for(k=MaxLeft;k>0;k--)
        {
			if(DisplacementNeg[k] > 0)///values of histograms
				fprintf(Distribution_File,"%d\t%d\n",-k, DisplacementNeg[k]);
			
		//printf("checkpoint\t%d done  \n", k);
		}	
	

		for(k=0;k<MaxRight;k++)
        {
			if(DisplacementPos[k] > 0)
				fprintf(Distribution_File,"%d\t%d\n",k, DisplacementPos[k]);
		}
		
		fclose(Distribution_File);
			
    }

        end = clock();

        printf("CPU time used: %lf\n",(double)(end-start)/CLOCKS_PER_SEC);
		
		return 0;
}
