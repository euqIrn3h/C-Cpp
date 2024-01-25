#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "L_GATE.h"
#include "EVO.h"



main(){
	int i,j,v=1,b,c,ent=3,nos=100,ger=100000,ttvd=pow(2,ent),tve[ttvd*ent],mae[(nos*4)+2],son[(nos*4)+2],*sol;
	int tvd[8]={0,1,0,1,1,0,0,0};
	
	sol=evo(ent,nos,ger,ttvd,tvd,mae,son);
	
	/*if(v==1){
		sol=son;
	}else{
		sol=mae;
	}*/
	printf("\n\n");
	for(i=0; i<nos; i++){
		printf("\n\t");
		for(j=0; j<4; j++){
			printf("%i\t",sol[(i*4)+j]);
		}
	}
	printf("\t\t%i",sol[(nos*4)]);

}



