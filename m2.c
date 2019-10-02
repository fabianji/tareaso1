#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h> 
#include <string.h>
#include <time.h>

//IMPORTANTE AL NAVEGAR ARREGLAR EL IF SI UNO PONE LETRA
//

//GRAN SUPUESTO, TODAS LAS CARPETAS DENTRO DE LA CARPETA QUE CONTIENE EL M2.C


void creacion_carpetas_vacias()
{
	char nombre_carpetas[20][20]={"mazo","mano1","mano2","mano3","mano4","revelada"};
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
	char colores[4][50]={"azul.txt","rojo.txt","verde.txt","amarillo.txt"};
	char colores2[4][50]={"azul(2).txt","rojo(2).txt","verde(2).txt","amarillo(2).txt"};
	//*****Pueden haber archivos con igual nombre?
	char color[4][50]={"mazo/color(1).txt","mazo/color(2).txt","mazo/color(3).txt","mazo/color(4).txt"};
	char mas_4[4][50]={"mazo/+4(1).txt","mazo/+4(2).txt","mazo/+4(3).txt","mazo/+4(4).txt"};
	char numeros[12][10]={"1 ","2 ","3 ","4 ","5 ","6 ","7 ","8 ","9 ","+2 ","reversa ","salto "}; //Ya tienen el espacio del append
    
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






void opciones(char archivos_o_carpetas[200][100], DIR *d, int es_carpeta[200], int *volver) //es carpeta=1
{
	struct dirent *dir;	
	int ra=1; //Recorre archivos
	strcpy(archivos_o_carpetas[0],"Salir.");
	printf("%d %s\n",0,archivos_o_carpetas[0]);
	
	char nombre_carpetas[20][20]={"mazo","mano1","mano2","mano3","mano4","revelada",".."};
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
	    	if(es_txt || es_carpeta_posible)//ignora los .c etc
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
}



void navegar(){
	char archivos[200][100]; //el nombre de los archivos no superaran 50 caracteres
	int es_carpeta[200]; //Guarda si es carpeta o archivo 1 o 0
	
	char directorio_actual[100]=".";
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

//Para elegir que carta poner
void seleccionar_carta(char carta_seleccionada[100], char dir_carta_seleccionada[100])
{
	char archivos[200][100]; //el nombre de los archivos no superaran 50 caracteres
	int es_carpeta[200]; //Guarda si es carpeta o archivo 1 o 0
	
	char directorio_actual[100]=".";
	int eleccion=1;
	
	int volver;
	int se_ha_seleccionado_carta=0;
	while(se_ha_seleccionado_carta != 1 && (eleccion != 0)) //AGREGAR OPCION DE SALIRSE
	{
		printf("Ingrese el numero del archivo al que desea acceder:\n");
		DIR *d = opendir(directorio_actual);
		opciones(archivos, d, es_carpeta,&volver);
		printf("\nSalir = 0, Volver = %d\n",volver);
		scanf("%d",&eleccion);
		//*FALTA DECIR SI NO ES NUMERO...
		if(eleccion ==0)
		{
			printf("No se eligio carta.\n");
		}
		else
		{
			if (es_carpeta[eleccion]==0)
			{  
				printf("Eligio la carta:%s\n",archivos[eleccion]);
				strcpy(carta_seleccionada,archivos[eleccion]);
				
				strcpy(dir_carta_seleccionada,directorio_actual);
				strcat(dir_carta_seleccionada,"/");
				strcat(dir_carta_seleccionada,carta_seleccionada);
				eleccion=0;
				se_ha_seleccionado_carta=1;
				
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


//OJO: QUE RESTRINJA SOLO A CARPETAS EXISTENTES.
void vaciar_carpeta()
{
	
	
	char nombre_carpetas[20][20]={"mazo","mano1","mano2","mano3","mano4","revelada"};

	printf("Seleccione la carpeta que desea vaciar:\n");
	int i;
	for(i=0;i<6;i++)
	{
		printf("%d. %s\n",i,nombre_carpetas[i]);
	}

	int eleccion=-1;
	while(eleccion < 0 || eleccion >= 6)
	{
		scanf("%d",&eleccion);
	}

	char directorio_elegido[20];

	strcpy(directorio_elegido,nombre_carpetas[eleccion]); 
	//printf("directorio_elegido: %s\n",directorio_elegido);
	char directorio_actual[50] = "./";
	strcat(directorio_actual,directorio_elegido);
	//printf("directorio_actual: %s\n",directorio_actual);

	DIR *d = opendir(directorio_actual);
	struct dirent *dir;	
	char direccion_carta_eliminada1[50];
	strcpy(direccion_carta_eliminada1,directorio_actual);
	
	printf("dir_car_elim1:%s\n",direccion_carta_eliminada1);
	char direccion_carta_eliminada2[50];
	strcpy(direccion_carta_eliminada2,direccion_carta_eliminada1);
	printf("dir_car_elim2:%s\n",direccion_carta_eliminada2);
	//Vaciara carpeta con nombre que deberia estar reservado para la tarea
	//Pero por si acaso se asegurara eliminar solo .txt
	int j = 0; //solo para ver cuantas se eliminan con el print comentado
	while((dir = readdir(d)) != NULL)
	{
		if(strstr(dir->d_name,".txt")!=NULL)
    	{
    		printf("carta:%s\n",dir->d_name);
    		strcat(direccion_carta_eliminada2,"/");
    		strcat(direccion_carta_eliminada2,dir->d_name);
    		printf("%d. Se eliminara carta  de direccion: %s\n",j,direccion_carta_eliminada2);
    		remove(direccion_carta_eliminada2);
    		//para ver que se regreso bien a la carpeta
    		strcpy(direccion_carta_eliminada2,direccion_carta_eliminada1);
    		printf("%d. De la carpeta de direccion %s\n",j,direccion_carta_eliminada2);
    		j++;

    	}
	}

	closedir(d);

}


void seleccionar_carpeta(char carpeta_seleccionada[100], char dir_carpeta_seleccionada[100])
{
	char archivos[200][100]; //el nombre de los archivos no superaran 50 caracteres
	int es_carpeta[200]; //Guarda si es carpeta o archivo 1 o 0
	
	char directorio_actual[100]=".";
	int eleccion=1;
	
	int volver;
	int se_ha_seleccionado_carta=0;
	while(se_ha_seleccionado_carta != 1 && (eleccion != 0)) //AGREGAR OPCION DE SALIRSE
	{
		printf("Ingrese el numero del archivo al que desea acceder:\n");
		DIR *d = opendir(directorio_actual);
		opciones(archivos, d, es_carpeta,&volver);
		printf("\nSalir = 0, Volver = %d\n",volver);
		scanf("%d",&eleccion);
		//*FALTA DECIR SI NO ES NUMERO...
		if(eleccion ==0)
		{
			printf("No se eligio carpeta.\n");
		}
		else
		{
			if (es_carpeta[eleccion]==0)
			{  
				printf("Eligio la carta:%s\n",archivos[eleccion]);
				//strcpy(carta_seleccionada,archivos[eleccion]);
				//strcpy(dir_carta_seleccionada,directorio_actual);
				eleccion=0;
				se_ha_seleccionado_carta=1;
				
			}
			else
			{
				//printf("Eligio la carpeta:%s\n",archivos[eleccion]);
				strcat(directorio_actual,"/");
				strcat(directorio_actual,archivos[eleccion]);
				strcpy(carpeta_seleccionada,archivos[eleccion]);
				strcpy(dir_carpeta_seleccionada,directorio_actual);
				//printf("en la direccion: %s\n",dir_carpeta_seleccionada);
				break;
			}	
		}
	}
}

void cartas_carpeta2(char dir_carpeta[100], char cartas[200][100], char dir_cartas[200][100])
{
	struct dirent *dir;
	DIR *d=opendir(dir_carpeta);
	int ra=0;
	char dir_actual[200];
	strcpy(dir_actual,dir_carpeta);
	


	while ((dir = readdir(d)) != NULL) 
    {

    	if(strstr(dir->d_name,".txt")!=NULL)
    	{
    		strcat(dir_actual,"/");
    		strcpy(cartas[ra],dir->d_name);
    		strcat(dir_actual,dir->d_name);
    		strcpy(dir_cartas[ra],dir_actual);

    		strcpy(dir_actual,dir_carpeta);
    		ra++;
    	}
    }


}

void agregar(char *nombreCarta, char *carpetaDestino, char *carpetaOrigen){
	char comando[40]="mv '";
	strcat(comando, carpetaOrigen);
	strcat(comando, "/");
	strcat(comando, nombreCarta);
	strcat(comando, "' ");
	strcat(comando, carpetaDestino);
	system(comando);
}

int cartas_carpeta(char dir_carpeta[100], char cartas[200][100], char dir_cartas[200][100])
{
	struct dirent *dir;
	DIR *d=opendir(dir_carpeta);
	int ra=0;
	char dir_actual[200];
	strcpy(dir_actual,dir_carpeta);
	


	while ((dir = readdir(d)) != NULL) 
    {

    	if(strstr(dir->d_name,".txt")!=NULL)
    	{
    		strcat(dir_actual,"/");
    		strcpy(cartas[ra],dir->d_name);
    		strcat(dir_actual,dir->d_name);
    		strcpy(dir_cartas[ra],dir_actual);

    		strcpy(dir_actual,dir_carpeta);
    		ra++;
    	}
    }
    return ra;


}


int main(int argc, char **argv)
{

	
	

	int i=0;
	char carta_seleccionada[100];
	char dir_carta_seleccionada[100];
	char carpeta_seleccionada[100];
	char dir_carpeta_seleccionada[100];
	
	int opcion=-1;
	
	char cartas[200][100];
	
	char dir_cartas[200][100];
	int j;

//PARA LA 7
/*
	int jug=-1;
	int l;
	char dir_carpetas_jugadores[4][100]={"./mano1","./mano2","/mano3","./mano4"}
	int n;
	char dir_carpeta_mazo[100]="./mazo";
	char dir_carpeta_jugador_actual[100]="./";
	int r; //random
	char todas_cartas[4][200][100];//MIENTRAS TANTO
*/

	while(opcion != 0){
		printf("Ingrese el numero de lo que desea hacer:\n");
		printf("0. Salir.\n");
		printf("1. Crear carpetas y cartas.\n");
		printf("2. Navegar (se detendra hasta que quiera salir).\n");
		printf("3. Seleccionar alguna carta.\n");
		printf("4. Vaciar carpeta.\n");
		printf("5. Elegir carpeta valida\n");
		printf("6. Crear arreglos de cartas eligiendo carpeta valida \n");
		printf("7. Repartir\n");
		//Podria servir a futuro
		printf("8. Agrega carta fija(2 amarillo.txt) de mazo a mano1.\n ");
		scanf("%d",&opcion);
		


		if(opcion==0)
		{
			printf("ADIOS!\n");
			break;

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
			seleccionar_carta(carta_seleccionada,dir_carta_seleccionada);
			//prueba(carta_seleccionada);
			printf("Tiene la carta: %s\n",carta_seleccionada);
			printf("En direccion: %s\n",dir_carta_seleccionada);


			
		}
		else if(opcion==4)
		{

			vaciar_carpeta();
			
		}
		else if(opcion==5)
		{

			
			printf("Selecciono carpeta\n");
			seleccionar_carpeta(carpeta_seleccionada,dir_carpeta_seleccionada);
			//prueba(carta_seleccionada);
			
			
		}

		else if(opcion==6)
		{

			printf("Seleccione carpeta\n");
			seleccionar_carpeta(carpeta_seleccionada,dir_carpeta_seleccionada);
			//prueba(carta_seleccionada);
			printf("Tiene la carpeta: %s\n",carpeta_seleccionada);
			printf("En direccion: %s\n",dir_carpeta_seleccionada);

			cartas_carpeta2(dir_carpeta_seleccionada,cartas,dir_cartas);
			while(strstr(cartas[i],".txt")!=NULL)
			{
			
				
				printf("%d. carta: %s    dir_carta: %s\n",i,cartas[i],dir_cartas[i]);
				i++;
			}
			//n=i; //SE GUARDA EL TAMAÑO DEL ARREGLO
			i=0;
		}
		else if(opcion ==7)
		{

			//agregar("2 amarillo.txt","mazo","mano1");

			
			srand(time(NULL));
			char jugadores[4][10]={"mano1", "mano2", "mano3", "mano4"};
			printf("Seleccione carpeta\n");
			seleccionar_carpeta(carpeta_seleccionada,dir_carpeta_seleccionada);
			printf("Tiene la carpeta: %s\n",carpeta_seleccionada);
			printf("En direccion: %s\n",dir_carpeta_seleccionada);

			int random;
			for (j = 0; j < 4; j++)
			{
				i=0;
				random=rand()%(cartas_carpeta(dir_carpeta_seleccionada,cartas,dir_cartas)+1);
				while(strstr(cartas[random],".txt")!=NULL && i<7)
				{
					agregar(cartas[random], jugadores[j], "mazo");
					printf("%d La carta obtenida es %s -> %s\n",random, cartas[random], jugadores[j]);
					random=rand()%cartas_carpeta (dir_carpeta_seleccionada,cartas,dir_cartas)+1;
					i++;
				}
			}
			printf("%d\n",cartas_carpeta(dir_carpeta_seleccionada,cartas,dir_cartas));




/*

			printf("Decida jugador:\n");
			for(l=0;l<4;l++)
			{
				printf("%d. Jugador %d\n",l,l);
			}
			scanf("%d",&jug);
			while(jug<0 && jug>4)
			{
				printf("Opcion invalida ingrese nuevamente.\n");
				printf("Decida jugador:\n");
				for(l=0;l<4;l++)
				{
					printf("%d. Jugador %d\n",l,l);
				}
				scanf("%d",&jug);
			}

			//printf("Diga el numero de cartas que tiene que robar (1/2/4/7)");
*/

		}

		else if(opcion==8)
		{
			agregar("2 amarillo.txt","mano1","mazo");
		}
		
		else {
			printf("OPCION NO VALIDA.\n");

		}
		


	}







 
	return 0;

}

