#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void eliminar_espacios(char *s) {
	char * p = s;
	char sp = ' ';

	while(*s){
		while(*s == sp){
			s++;
		}
		*p++ = *s++;
	}
	*p = 0;
}

FILE *dic;

void consultarAux(char *nom_dic, char *s, int linea) {
	char buffer[101];
	char subizq[10], subder[10], llave[20], sig[59];
	char q[] = "palabra no encontrada";
	int izq, der, comp;

	fseek(dic, linea*100, SEEK_SET);
	fread(buffer, 100, 1, dic);

	strncpy(subizq, buffer, 10);
	*(subizq+10)=0;
	izq = atoi(subizq);

	strncpy(subder, buffer+10, 10);
	*(subder+10)=0;
	der = atoi(subder);

	strncpy(llave, buffer+20, 20);
	*(llave+20)=0;
	eliminar_espacios(llave);

	strncpy(sig, buffer+40, 59);
	*(sig+59)=0;
	
	comp = strcmp(s, llave);

	if(comp == 0){
		printf("%s\n", sig);
	}

	else if(comp<0 && izq!=-1){
		consultarAux(nom_dic, s, izq);

	}

	else if(comp>0 && der!=-1) {
		consultarAux(nom_dic, s, der);

	}

	else{
		printf("%s\n", q);
	}
	

}

void consultar(char *nom_dic, char *s) {
	dic = fopen(nom_dic, "r");
	if (dic==NULL) {
		perror("fopen");
    	exit(1);
	}
	consultarAux(nom_dic, s, 0);
	fclose(dic);

}


int main(int argcm, char **argv){
	char* nom_dic = argv[1];
	char* s = argv[2];
	consultar(nom_dic, s);
}




