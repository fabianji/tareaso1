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
	int i,j,k;
	char colores[4][50]={"azul.txt","rojo.txt","verde.txt","amarillo.txt"};
	char colores2[4][50]={"azul(2).txt","rojo(2).txt","verde(2).txt","amarillo(2).txt"};
	//*****Pueden haber archivos con igual nombre?
	char color[4][50]={"mazo/color(1).txt","mazo/color(2).txt","mazo/color(3).txt","mazo/color(4).txt"};
	char mas_4[4][50]={"mazo/+4(1).txt","mazo/+4(2).txt","mazo/+4(3).txt","mazo/+4(4).txt"};
	char numeros[12][10]={"1 ","2 ","3 ","4 ","5 ","6 ","7 ","8 ","9 ","+2 ","reversa ","salto "}; //Ya tienen el espacio del append
    char cartas[108][10]; 

    char direccion_cartas[50];
    for(j=0;j<4;j++)
    {
   		for(i=0;i<12;i++)
   		{
   			
   			FILE *fp;
   			char direccion_cartas[50]="mazo/";
   			strcat(direccion_cartas,numeros[i]);
   			strcat(direccion_cartas,colores[j]);
			fp=fopen(direccion_cartas,"w");
			fclose(fp);

			
   			char direccion_cartas2[50]="mazo/";
   			strcat(direccion_cartas2,numeros[i]);
   			strcat(direccion_cartas2,colores2[j]);
			fp=fopen(direccion_cartas2,"w");
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

void opciones(char archivos_o_carpetas[200][50], DIR *d, int es_carpeta[200], int *volver) //es carpeta=1
{
	struct dirent *dir;	
	int ra=1; //Recorre archivos
	strcpy(archivos_o_carpetas[0],"Salir.");
	printf("%d %s\n",0,archivos_o_carpetas[0]);
	
	char nombre_carpetas[20][20]={"mazo","mano1","mano2","mano3","mano4","rebelada",".."};
	int i;
	int es_carpeta_posible=0; 
	int es_txt=0;
	if (d) 
    {
	    while ((dir = readdir(d)) != NULL) 
	    {
	    	
	    	for(i=0;i<7;i++){
	    		if(strcmp(nombre_carpetas[i],dir->d_name)==0)
	    		{
	    			es_carpeta_posible=1;
	    			es_carpeta[ra]=1;
	    		}
	    	}
	    	if(strstr(dir->d_name,".txt")!=NULL)
	    	{
	    		es_txt=1;
	    		es_carpeta[ra]=0;
	    	}
	    	if(es_txt || es_carpeta_posible)
	    	{
	    		strcpy(archivos_o_carpetas[ra],dir->d_name);
	    		if(!strcmp(dir->d_name,"..")){
	    			*volver=ra;
	    			printf("(Volver)=>");
	    		}

	        	printf("%d %s\n",ra,archivos_o_carpetas[ra]);
	        	ra++;
	    	}

	    	es_carpeta_posible=0; 
			es_txt=0;
	    	
    	}
	        
	}

	closedir(d);


	//La estoy haciendo en otro c , casi...
}

void barajar()
{
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

void navegar(){
	char archivos[200][50]; //el nombre de los archivos no superaran 50 caracteres
	int es_carpeta[200]; //Guarda si es carpeta o archivo 1 o 0
	
	char directorio_actual[50]=".";
	int eleccion=1;
	
	int volver;
	while(eleccion != 0)
	{
		printf("Ingrese el numero del archivo al que desea acceder:\n");
		DIR *d = opendir(directorio_actual);
		opciones(archivos, d, es_carpeta,&volver);
		printf("\nSalir = 0, Volver = %d\n",volver);
		scanf("%d",&eleccion);
		//*FALTA DECIR SI NO ES NUMERO...
		if(eleccion ==0)
		{
			printf("Adios.\n");
		}
		else
		{
			if (es_carpeta[eleccion]==0)
			{  
				printf("Eligio la carta:%s\n",archivos[eleccion]);
			}
			else
			{
				printf("Eligio la carpeta:%s\n",archivos[eleccion]);
				strcat(directorio_actual,"/");
				strcat(directorio_actual,archivos[eleccion]);
			}
		}
		
		
	}
}

void navegar2(char carta_seleccionada[50]){
	char archivos[200][50]; //el nombre de los archivos no superaran 50 caracteres
	int es_carpeta[200]; //Guarda si es carpeta o archivo 1 o 0
	
	char directorio_actual[50]=".";
	int eleccion=1;
	
	int volver;
	while(eleccion != 0)
	{
		printf("Ingrese el numero del archivo al que desea acceder:\n");
		DIR *d = opendir(directorio_actual);
		opciones(archivos, d, es_carpeta,&volver);
		printf("\nSalir = 0, Volver = %d\n",volver);
		scanf("%d",&eleccion);
		//*FALTA DECIR SI NO ES NUMERO...
		if(eleccion ==0)
		{
			printf("Adios.\n");
		}
		else
		{
			if (es_carpeta[eleccion]==0)
			{  
				printf("Eligio la carta:%s\n",archivos[eleccion]);
				strcpy(carta_seleccionada,archivos[eleccion]);
				eleccion=0;
			}
			else
			{
				printf("Eligio la carpeta:%s\n",archivos[eleccion]);
				strcat(directorio_actual,"/");
				strcat(directorio_actual,archivos[eleccion]);
			}
		}
		
		
	}
}


int main(int argc, char **argv)
{

	
	char *carta_seleccionada;
	int opcion=-1;
	
	while(opcion != 0){
		printf("Ingrese el numero de lo que desea hacer:\n");
		printf("0. Salir.\n");
		printf("1. Crear carpetas y cartas.\n");
		printf("2. Navegar (se detendra hasta que quiera salir).\n");
		printf("3. Seleccionar alguna carta.\n");
		scanf("%d",&opcion);
		


		if(opcion==0)
		{
			printf("ADIOS!\n");
		}
		else if(opcion==1)
		{
			creacion_carpetas_vacias();
			creacion_cartas();
		}
		else if(opcion==2)
		{
			navegar();
		}
		else if(opcion==3)
		{
			navegar2(carta_seleccionada);
			//*************ACA PODRIAS PONER LO DE ELEGIR CARTA
			
		}
		else {
			printf("OPCION NO VALIDA.\n");

		}
		


	}

	
	

	navegar(); 
	return 0;

}

