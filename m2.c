#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h> 
#include <string.h>

void creacion_carpetas_vacias()
{
	char nombre_carpetas[20][20]={"mazo","mano1","mano2","mano3","mano4","rebelada"};
	int i;
	for(i=0;i<6;i++)
	{
		struct stat st = {0};
		if (stat(nombre_carpetas[i], &st) == -1) 
		{
		    mkdir(nombre_carpetas[i], 0700);
		}
	}
}

void creacion_cartas()
{
	int i,j;
	char colores[4][10]={"azul","rojo","verde","amarillo"};
	//*****Pueden haber archivos con igual nombre?
	char color[4][15]={"mazo/color(1)","mazo/color(2)","mazo/color(3)","mazo/olor(4)"};
	char mas_4[4][15]={"mazo/+4(1)","mazo/+4(2)","mazo/+4(3)","mazo/+4(4)"};
	char numeros[12][10]={"1 ","2 ","3 ","4 ","5 ","6 ","7 ","8 ","9 ","+2 ","reversa ","salto "}; //Ya tienen el espacio del append
    char cartas[108][10]; 
    for(j=0;j<4;j++)
    {
   		for(i=0;i<12;i++)
   		{
   			FILE *fp;
   			char direccion_cartas[30]="mazo/";
   			strcat(direccion_cartas,numeros[i]);
   			strcat(direccion_cartas,colores[j]);
			fp=fopen(direccion_cartas,"w");
			fclose(fp);
   		}
   		FILE *fp;
   		char direccion_cartas[30]="mazo/";
   		strcat(direccion_cartas,"0 ");
   		strcat(direccion_cartas,colores[j]);
   		fp=fopen(direccion_cartas,"w");
   		fclose(fp);
 		
   		fp=fopen(color[j],"w");
   		fclose(fp);
   		
   		fp=fopen(mas_4[j],"w");
   		fclose(fp);
   	} 
}

void navegar(){
	//La estoy haciendo en otro c , casi...
}

void barajar(){
	//Tmb la tengo casi...
}

//Cantidad de cartas i que se da al jugador j
void robar_carta(int i, int j){

}

//***IMPORTANTE ver el tema de los fork y comunicación pipes
//Dejar carta en carpeta rebelada y elimina anterior.
//debe cumplir con la restriccion del color y tipo
void colocar_carta_rebelada(){

}




int main(int argc, char **argv)
{
	creacion_carpetas_vacias();
	creacion_cartas();
	
	return 0;

}