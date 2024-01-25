#include<stdio.h>
#include<math.h>
#include "EVO.h"


main(){
	int ent,nos,ger,qp,ttvd,i,j;		//ent=entradas	nos=nos	ger=geracoes	qp=quantidade de posicoes TRUE na tabvdd	ttvd=tamanho da tabvdd
	
	printf("\nQuantidade de entradas: ");
	scanf("%i",&ent);
	printf("\nQuantidade de nos: ");
	scanf("%i",&nos);
	printf("\nQuantidade de geracoes: ");
	scanf("%i",&ger);	
	printf("\nQuantidade de posicoes verdadeiras na tab vdd: ");
	scanf("%i",&qp);
	
	ttvd=pow(2,ent);
	
	int pos[qp],tvd[ttvd],mae[(nos*4)+2],son[(nos*4)+2],*sol;
	
	
	for(i=0; i<ttvd; i++){					//Preenche a TVD com zeros
		tvd[i]=0;
	}	
	printf("\n");
	for(i=0; i<qp; i++){					//Preenche as posicoes verdadeiras
		printf("\nPosicao verdadeira: ");
		scanf("%i",&j);
		tvd[j]=1;
	}
	
	sol=evo(ent,nos,ger,ttvd,tvd,mae,son);
	
	printf("\n\n\tENT1\tENT2\tPORTA");
	for(i=0; i<nos; i++){
		printf("\n\t");
		for(j=0; j<4; j++){
			printf("%i\t",sol[(i*4)+j]);
		}
	}
	printf("\t\t%i",sol[(nos*4)]);
	
	
	
}
