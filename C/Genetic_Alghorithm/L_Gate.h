#ifndef L_GATE
#define L_GATE

char gand(char a, char b){
	if(a==1 && b==1){
		return 1;
	}else{
		return 0;
	}
}

char gor(char a, char b){
	if(a==1 || b==1){
		return 1;
	}else{
		return 0;
	}
}

char gnot(char a){
	if(a==0){
		return 1;
	}else{
		return 0;
	}
}

char gxor(char a, char b){
	if(a==b){
		return 0;
	}else{
		return 1;
	}
}


#endif /*L_GATE*/
