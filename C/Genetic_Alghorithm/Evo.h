#ifndef EVO
#define EVO

#include "L_GATE.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int *evo(int ent,int nos,int ger,int ttvd,int *tvd,int *mae,int *son);
void gm(int *mae,int nos,int ent);
void gtd(int ent,int ttvd,int *tve);
void gs(int *mae,int *son,int nos,int ent);
void gtn(int nos,int ent,int ttvd,int *mae,int *tve,int *tvd);


int *evo(int ent,int nos,int ger,int ttvd,int *tvd,int *mae,int *son){
	/*	tvs = tab vdd saida pai e son
		tve = tab vdd das entradas*/
	int i,j,gen=0,p/*,mae[(nos*4)+2],son[(nos*4)+2]son1[(nos*4)+1],son2[(nos*4)+1],son3[(nos*4)+1]*/,tve[ttvd*ent];
	gtd(ent,ttvd,tve);
	gm(mae,nos,ent);
	gtn(nos,ent,ttvd,mae,tve,tvd);
	printf("\n\t%i",mae[(nos*4)+1]);
	
	while(mae[(nos*4)+1]!=ttvd && gen<ger){
		for(i=0; i<4; i++){
			gs(mae,son,nos,ent);
			gtn(nos,ent,ttvd,son,tve,tvd);
			printf("\n\t%i",son[(nos*4)+1]);
			
			if(son[(nos*4)+1]==ttvd){
				printf("\n\n\tSON\tgen: %i\t filho: %i",gen,i);
				return son;
			}else{
				if(son[(nos*4)+1]>=mae[(nos*4)+1]){
					for(j=0; j<nos; j++){
						for(p=0; p<4; p++){
							mae[(i*4)+p]=son[(i*4)+p];
						}
					}
					mae[(nos*4)]=son[(nos*4)];
					mae[(nos*4)+1]=son[(nos*4)+1];
				}
			}
		}
		gen++;
	}
	printf("\n\n\tMAE\tgen: %i",gen);
	return mae;
	
}




void gm(int *mae,int nos,int ent){
	int i;
	srand(time(NULL));
	for(i=0; i<nos; i++){
		mae[i*4]=rand()%(i+ent);
		mae[(i*4)+1]=rand()%(i+ent);
		mae[(i*4)+2]=rand()%3;
		mae[(i*4)+3]=0;
	}
	mae[(nos*4)]=rand()%(ent+nos);
}




void gtd(int ent,int ttvd,int *tve){
	int c,v,b,i,j;
	srand(time(NULL));
	for(i=0; i<ent; i++){
		c=pow(2,(ent-i))/2;
		v=0;
		b=0;
		for(j=0; j<ttvd; j++){
			if(v==c && b==1){
				v=0;
				b=0;
			}else{
				if(v==c && b==0){
					v=0;
					b=1;
				}
			}
			v++;
			tve[(i*ttvd)+j]=b;
		}
	}
}




void gs(int *mae,int *son,int nos,int ent){
	int i,j;
	for(i=0; i<nos; i++){
		if(rand()%2==1){
			son[(i*4)]=rand()%(i+ent);
		}else{
			son[(i*4)]=mae[(i*4)];
		}
		if(rand()%2==1){
			son[(i*4)+1]=rand()%(i+ent);
		}else{
			son[(i*4)+1]=mae[(i*4)+1];
		}
		if(rand()%2==1){
			son[(i*4)+2]=rand()%3;
		}else{
			son[(i*4)+2]=mae[(i*4)+2];
		}
		son[(i*4)+3]=0;
	}
	son[(nos*4)]=rand()%(ent+nos);
}




void gtn(int nos,int ent,int ttvd,int *mae,int *tve,int *tvd){
	int i,j,tn[(nos+ent)*ttvd];
	for(i=0; i<(nos+ent)*ttvd; i++){
		tn[i]=5;
	}
	
	for(i=0; i<ent; i++){
		for(j=0; j<ttvd; j++){
			tn[(i*ttvd)+j]=tve[(i*ttvd)+j];
		}
	}
	
	/*for(i=ent; i<nos+ent; i++){
		for(j=0; j<ttvd; j++){
		
		ERRO
			aumentando a quantidade de loops no J quando é o caso 0 ou caso 1
			
			switch(mae[((i-ent)*4)+2]){
				case 0:
					printf("\n%i%i",mae[(i-ent)*4],mae[((i-ent)*4)+1]);
					tn[(i*ttvd)+j]= gor(tn[(mae[(i-ent)*4]*ttvd)+j],tn[(mae[((i-ent)*4)+1]*ttvd)+j]);
				case 1:
					printf("\n%i%i",mae[(i-ent)*4],mae[((i-ent)*4)+1]);
					tn[(i*ttvd)+j]= gand(tn[(mae[(i-ent)*4]*ttvd)+j],tn[(mae[((i-ent)*4)+1]*ttvd)+j]);
				case 2:
					printf("\n%i%i",mae[(i-ent)*4],mae[((i-ent)*4)+1]);
					tn[(i*ttvd)+j]= gxor(tn[(mae[(i-ent)*4]*ttvd)+j],tn[(mae[((i-ent)*4)+1]*ttvd)+j]);
			}
		}
	}
	*/
	for(i=ent; i<nos+ent; i++){
		for(j=0; j<ttvd; j++){
			if(mae[((i-ent)*4)+2]==0){	
				tn[(i*ttvd)+j]= gor(tn[(mae[(i-ent)*4]*ttvd)+j],tn[(mae[((i-ent)*4)+1]*ttvd)+j]);
			}
			if(mae[((i-ent)*4)+2]==1){		
				tn[(i*ttvd)+j]= gand(tn[(mae[(i-ent)*4]*ttvd)+j],tn[(mae[((i-ent)*4)+1]*ttvd)+j]);
			}
			if(mae[((i-ent)*4)+2]==2){
				tn[(i*ttvd)+j]= gxor(tn[(mae[(i-ent)*4]*ttvd)+j],tn[(mae[((i-ent)*4)+1]*ttvd)+j]);
			}
		}
	}
	
	/*
	Printa as tbvdds dos nos
	for(i=0; i<nos+ent; i++){
		printf("\n\t");
		for(j=0; j<ttvd; j++){
			printf("%i",tn[(i*ttvd)+j]);
		}
	}*/

	j=0;
	for(i=0; i<ttvd; i++){
		
		if(tvd[i]==tn[(mae[nos*4]*ttvd)+i]){
			j++;
		}
		mae[(nos*4)+1]=j;
	}
	
	
}


#endif /*EVO*/
