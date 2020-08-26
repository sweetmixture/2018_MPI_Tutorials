#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void ReadInput(void);

int main(int argc, char* argv[]){

	FILE *Data;
	int N_Trialmove,N_Oscillator,H_state,MAX_Hstate;
	float Temperature;
	float Kb = 1.,h = 1.;		///Boltzmann_const /// Planck_const
	float Beta,Delta_E;
	int chk_time = 0;
	char Buffer[30];

	int i,j,k,q;

	int *Oscillator;
	int *E_state;
	///////////////////INPUT READ///////////////////
	FILE *INPUT;
	char* dummy_string;
	dummy_string = (char*)malloc(1024*sizeof(char));
	INPUT = fopen("input","r");
	fscanf(INPUT,"%s",dummy_string);
	fscanf(INPUT,"%d",&N_Trialmove);

	printf("\n\tNumber of Trial Move %d\n\n",N_Trialmove);
	
	fscanf(INPUT,"%s",dummy_string);
	fscanf(INPUT,"%f",&Temperature);

	printf("\tTemperature %f K\n\n",Temperature);

	fscanf(INPUT,"%s",dummy_string);
	fscanf(INPUT,"%d",&N_Oscillator);
	
	printf("\tNumber of Oscillator %d\n\n",N_Oscillator);

	fscanf(INPUT,"%s",dummy_string);
	fscanf(INPUT,"%d",&H_state);

	printf("\tHighest state Quantum number %d\n\n",H_state);

	fclose(INPUT);
	free(dummy_string);
	///////////////////END INPUT READ//////////////

	/////MEMORY ALLOC///////////////////////////////////
	Oscillator = (int*)malloc(N_Oscillator*sizeof(int));
	E_state = (int*)malloc(H_state*sizeof(int));
	////////////////////////////////////////////////////
	srand((unsigned)time(NULL));

	////initialising Oscillator////
	for(i=0;i<N_Oscillator;i++)
		Oscillator[i] = 0;
	//////////////////////////////


////////////////////////TRIAL MOVE LOOP////////////////////////////////////////////////////////
		for(i=0;i<N_Trialmove;i++){
			if( i%10000 == 0 )
			printf("%d is done\n",i);//////////////////////////////////////////
		
		//////Metroplis algorithm//////////////////////////////
		for(j=0;j<N_Oscillator;j++){
			if((float)rand()/RAND_MAX < 0.5){		//Trial move toward upper state
		
				Delta_E = h*((float)(Oscillator[j]+1.0)+0.5) - h*((float)Oscillator[j]+0.5);
				Beta = Kb*Temperature;
				
			if( exp(-Delta_E/Beta) > (float)rand()/RAND_MAX )///// the proble point """ -exp(*~ """" notation;;!!
				Oscillator[j]++;

			//else Oscillator[j] = Oscillatior[j];
			}
			else{
				if( Oscillator[j] > 0 )
				Oscillator[j]--;
			}
		}
		//////////////////////////END METROPOLIS///////////////
		//
		//Data printing//
		if( i%(int)pow(2,chk_time) == 0 ){
			sprintf(Buffer,"Distribution_%d",chk_time);
			//printf("\tTime %d has been passed...\n",chk_time);
		
		chk_time++;

		Data = fopen(Buffer,"w");
		fprintf(Data,"Time passed: %d\tAt %fK\n",(int)pow(2,chk_time), Temperature);
		
		//printf("check point\n");//////////////////////////////////////////

		for(j=0;j<H_state;j++)
			E_state[j] = 0;

		MAX_Hstate = 0;
		for(j=0;j<N_Oscillator;j++){
			E_state[ Oscillator[j] ] += 1;
			if( Oscillator[j] > MAX_Hstate )
				MAX_Hstate = Oscillator[j];
		}
		printf("%d\n",MAX_Hstate);
		for(q=0;q<MAX_Hstate;q++){
			fprintf(Data,"%d\t%d\n",q,E_state[q]);
			printf("%d\t%d\n",q,E_state[q]);
		}
		fclose(Data);
			//printf("\tTime %d has been passed...\n",(int)pow(4,chk_time));
		}
		//End Data printing//

	}///////END TRIAL MOVE


	free(E_state);
	free(Oscillator);


	return 0;
}

/*void ReadInput(void)
{	
	FILE *INPUT;
	char* dummy;
	dummy = (char*)malloc(30*sizeof(char));
	INPUT = fopen("input","r");
	fscanf(INPUT,"%s",dummy_string);
	fscanf(INPUT,"%d",%N_Trialmove);
	
	fscanf(INPUT,"%s",dummy_string);
	fscnaf(INPUT,"%f",&Temperature);

	fscanf(INPUT,"%s",dummy_string);
	fscanf("%d",&N_Oscillator);
	
	fscanf(INPUT,"%s",dummy_string);
	fscanf(INPUT,"%d",&H_state);
	fclose(INPUT);
	free(dummy);

}*/
