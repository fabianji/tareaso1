
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h> 
#include <string.h>
#include <time.h>
#include <sys/wait.h>

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
	char directorio_actual[50] = "./";
	strcat(directorio_actual,directorio_elegido);

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
    		strcpy(direccion_carta_eliminada2,direccion_carta_eliminada1);
    		printf("%d. De la carpeta de direccion %s\n",j,direccion_carta_eliminada2);
    		j++;

    	}
	}

	closedir(d);

}

void vaciar_4carpetas()
{
	
	
	char nombre_carpetas[6][20]={"mazo","mano1","mano2","mano3","mano4","revelada"};
	int i;
	char directorio_elegido[20];
	for(i=0;i<6;i++)
	{

	

		
		strcpy(directorio_elegido,nombre_carpetas[i]); 
		char directorio_actual[50] = "./";
		strcat(directorio_actual,directorio_elegido);
		DIR *d = opendir(directorio_actual);
		struct dirent *dir;	
		char direccion_carta_eliminada1[50];
		strcpy(direccion_carta_eliminada1,directorio_actual);
		char direccion_carta_eliminada2[50];
		strcpy(direccion_carta_eliminada2,direccion_carta_eliminada1);
		int j = 0; 
		while((dir = readdir(d)) != NULL)
		{
			if(strstr(dir->d_name,".txt")!=NULL)
			{
				strcat(direccion_carta_eliminada2,"/");
				strcat(direccion_carta_eliminada2,dir->d_name);
				remove(direccion_carta_eliminada2);
				strcpy(direccion_carta_eliminada2,direccion_carta_eliminada1);
				j++;
			}
		}

		closedir(d);
	}

}

void vaciar_revelada()
{
	
	
	char nombre_carpetas[20]="revelada";
	
	char directorio_elegido[20];
	

	

		
	strcpy(directorio_elegido,nombre_carpetas); 
	char directorio_actual[50] = "./";
	strcat(directorio_actual,directorio_elegido);
	DIR *d = opendir(directorio_actual);
	struct dirent *dir;	
	char direccion_carta_eliminada1[50];
	strcpy(direccion_carta_eliminada1,directorio_actual);
	char direccion_carta_eliminada2[50];
	strcpy(direccion_carta_eliminada2,direccion_carta_eliminada1);
	int j = 0; 
	while((dir = readdir(d)) != NULL)
	{
		if(strstr(dir->d_name,".txt")!=NULL)
		{
			strcat(direccion_carta_eliminada2,"/");
			strcat(direccion_carta_eliminada2,dir->d_name);
			remove(direccion_carta_eliminada2);
			strcpy(direccion_carta_eliminada2,direccion_carta_eliminada1);
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

/*
---Descripcion: Se usa dir_carpeta para abrir una carpeta que halla sido
validada antes, por ejemplo ./mano1 , en cartas se guardan todos los .txt


*/
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

/***********************************************************************
Descripcion: Esta funcion reparte las 7 cartas iniciales en las carpetas
			 mano1, mano2, mano3 y mano4
***********************************************************************/
void repartir7cartas()
{

	int i=0;
	int j;	
	char dir_carpeta_seleccionada[100];
	char cartas[200][100];
	char dir_cartas[200][100];
	srand(time(NULL));
	char jugadores[4][10]={"mano1", "mano2", "mano3", "mano4"};
	printf("Seleccione carpeta\n");
	strcpy(dir_carpeta_seleccionada, "./mazo");


	int random;
	for (j = 0; j < 4; j++)
	{
		i=0;
		random=rand()%(cartas_carpeta(dir_carpeta_seleccionada,cartas,dir_cartas)+1);
		while(strstr(cartas[random],".txt")!=NULL && i<7)
		{
			agregar(cartas[random], jugadores[j], "mazo");
			random=rand()%cartas_carpeta (dir_carpeta_seleccionada,cartas,dir_cartas)+1;
			i++;
		}
	}
}


//carta 2 es la revelada
int cumple_restr(char carta1[100], char carta2[100],char color_elegido[100])
{
	

	
	char colores[4][100]={"verde","rojo","amarillo","azul"};
	

	//AGREGAR IF COLOR ELEGIDO
	char numeros[10][100]={"0 ","1 ","2 ","3 ","4 ","5 ","6 ","7 ","8 ","9 "};
	int i;

	if(strstr(carta1,"color")!=NULL)
	{
		return 1;
	}
	if(strstr(carta1,"+4")!=NULL)
	{
		return 1;
	}


	//puede tirar si son mismo numero
	if(carta2[0]== carta1[1])
	{
		return 1;
	}

	//puede tirar +2 sobre +2
	if(carta2[1]=='2' && carta1[1]=='2')
	{
		return 1;
	}
	//puede tirar +4 sobre +4
	if(carta2[1]=='4' && carta1[1]=='4')
	{
		return 1;
	}
	
	if(strstr(carta1,"salto")!=NULL && strstr(carta2,"salto")!=NULL){
		return 1;
	}
	if(strstr(carta1,"reversa")!=NULL && strstr(carta2,"reversa")!=NULL){
		return 1;
	}
	if(strstr(carta1,"color")!=NULL && strstr(carta2,"color")!=NULL){
		return 1;
	}

	
	for(i=0;i<4;i++)
	{
		if(strstr(carta1,colores[i])!=NULL && strstr(carta2,colores[i])!=NULL)
		{
			return 1;
		}
		if(strstr(carta1,numeros[i])!=NULL && strstr(carta2,numeros[i])!=NULL)
		{
			return 1;
		}
	
	}
	for(i=4;i<10;i++)
	{
		if(strstr(carta1,numeros[i])!=NULL && strstr(carta2,numeros[i])!=NULL)
		{
			return 1;
		}
	}
	return 0;
}
int debe_elegir_color(char carta1[100]){
	//es color
	if(strstr(carta1,"color")!=NULL){
		return 1;
	}
	//es +4
	if(carta1[1]=='4')
	{
		return 1;
	}
	return 0;

}

void elegir_color(char color_elegido[100])
{
	char colores[4][100]={"amarillo","azul","rojo","verde"};
	int num_rand= rand()%4;
	strcpy(color_elegido,colores[num_rand]);
}


int main(int argc, char **argv)
{

	printf("*****************INICIACION*****************\n");
	printf("Carpetas vacías, mazo con 108.\n");
	creacion_carpetas_vacias();
	vaciar_4carpetas();
	creacion_cartas();
	printf("Reparten 7 cartas iniciales:\n");
	repartir7cartas();
	printf("*******************************************\n");

	int i=0;
	int terminar=0;
	char color_elegido[100] = "ninguno";

	
	char carpetas[4][200]={"./mano1","./mano2","./mano3","./mano4"};
	char carpetas2[4][200]={"mano1","mano2","mano3","mano4"};
	int cartas_tot[4]={7,7,7,7};
	//de los jugadores
	char cartas[200][100];
	char dir_cartas[200][100];

	int conteo_cartas=0;

	char cartas_rev[200][100];
	char dir_cartas_rev[200][100];

	char cartas_mazo[200][100];
	char dir_cartas_mazo[200][100];
	cartas_carpeta("./mazo",cartas_mazo,dir_cartas_mazo);

	int cumplen=0;
	int num_carta_final=-1;


	//primer turno:
	printf("*****************Primer Turno*****************\n");
	printf("Juega jugador %d:\n\n",i);
	printf("Tengo mano en carpeta %s:\n\n", carpetas[i]);
	printf("Tengo %d cartas las cuales son:\n",cartas_tot[i]);
	cartas_carpeta(carpetas[i],cartas,dir_cartas);
	while(conteo_cartas<cartas_tot[i])
	{
		printf("       %d. carta: %s\n",conteo_cartas,cartas[conteo_cartas]);
		conteo_cartas++;

	}
	conteo_cartas=0;

	printf("Jugador0 coloca primera carta a revelada:\n");
	agregar(cartas[0],"revelada","mano1");
	
	cartas_carpeta("./revelada",cartas_rev,dir_cartas_rev);
	
	cartas_tot[0]--;
	//AGREGAR A LOS DEMAS TURNOS. PERO PRIMERO DEBEN JUGAR
	if(debe_elegir_color(cartas_rev[0]))
	{
		printf("El jugador 0 debe elegir color:\n");
		elegir_color(color_elegido);
		printf("Jugador %d eligio color %s",i,color_elegido);
	}
	

	cartas_carpeta("./mazo",cartas_mazo,dir_cartas_mazo);
	i=1;
	printf("*********************************************\n");
	while(terminar!=1)
	{
		cartas_carpeta("./mazo",cartas_mazo,dir_cartas_mazo);
		conteo_cartas=0;
		cumplen=0;

		printf("--------------------------Juega jugador %d (parte de 0):-----------------------\n",i);
		cartas_carpeta("./revelada",cartas_rev,dir_cartas_rev);
		printf("Se esta revelando la carta:%s\n\n",cartas_rev[0]);

	
		
		if(strstr(cartas_rev[0],"+2")!=NULL)
		{
			printf("jugador %d roba 2 cartas.\n",i);
			agregar(cartas_mazo[0],carpetas2[i],"mazo");
			cartas_tot[i]++;
			agregar(cartas_mazo[0],carpetas2[i],"mazo");
			cartas_tot[i]++;
			
		}
		else if(strstr(cartas_rev[0],"+4")!=NULL)
		{
			printf("jugador %d roba 4 cartas.\n",i);
			agregar(cartas_mazo[0],carpetas2[i],"mazo");
			cartas_tot[i]++;
			agregar(cartas_mazo[0],carpetas2[i],"mazo");
			cartas_tot[i]++;
			agregar(cartas_mazo[0],carpetas2[i],"mazo");
			cartas_tot[i]++;
			agregar(cartas_mazo[0],carpetas2[i],"mazo");
			cartas_tot[i]++;
			
		}
		else if(strstr(cartas_rev[0],"reversa")!=NULL){
			printf("se cambia direccion juego\n");
			
		}
		else if(strstr(cartas_rev[0],"salto")!=NULL){
			printf("se salta al jugador %d \n",i);

		}

		printf("Tengo mano en carpeta %s:\n", carpetas[i]);
		printf("Tengo %d cartas las cuales son:\n",cartas_tot[i]);
		cartas_carpeta(carpetas[i],cartas,dir_cartas);

		//Para ver las cartas.
		while(conteo_cartas<cartas_tot[i])
		{
			printf("       %d. carta: %s\n",conteo_cartas,cartas[conteo_cartas]);
			conteo_cartas++;
			
		
		}
		if(conteo_cartas==1)
		{
			printf("El jugador %d grita UNO!\n",i);
		}
		if(conteo_cartas==0)
		{
			printf("El jugador %d grita GANE!\n",i);
		}
		conteo_cartas=0;

		
		printf("Solo se pueden jugar las siguientes cartas:\n");
		while(conteo_cartas<cartas_tot[i])
		{
			if(cumple_restr(cartas[conteo_cartas],cartas_rev[0],color_elegido)==1)
			{
				printf("       %d. carta: %s\n",conteo_cartas,cartas[conteo_cartas]);
				cumplen++;
				num_carta_final=conteo_cartas;
			}
			
			conteo_cartas++;
		}
		if(cumplen==0)
		{
			printf("EL jugador %d no puede colocar cartas, por lo que tiene que robar del mazo: \n",i);
			



			//********ACA DEBERIA IR LA FUNCION ROBAR CORRECTA AHORA HAGO QUE ROBE PRIMERA
			//QUE SEA ALEATORIO....
			agregar(cartas_mazo[0],carpetas2[i],"mazo");
			cartas_tot[i]++;
			//------------
		}
		else
		{
			//juega la ultima carta . ojo cumplen da 1, => 1 carta=> ultima carta es 0
			//primero eliminar de revelada
			printf("El jugador %d jugara la carta %s\n",i,cartas[num_carta_final]);
			

			printf("se agrega %s a basurero .\n",cartas_rev[0]);
			vaciar_revelada();
			printf("se agrego a basurero\n");

			
			if(debe_elegir_color(cartas[num_carta_final]))
			{
				printf("El jugador %d debe elegir color:\n", i);
				elegir_color(color_elegido);
				printf("Jugador %d eligio color %s",i,color_elegido);
			}
			printf("se agrega %s a revelada .\n",cartas[num_carta_final]);
			
			agregar(cartas[num_carta_final],"revelada",carpetas2[i]);
			printf("se agrego a revelada\n");
			cartas_tot[i]--;
	
		}


		conteo_cartas=0;
		cumplen=0;
			
		
		printf("----------------------------------------------------------------\n");
		


		printf("Presione 1 para salir, otro numero para continuar turno:\n");
		scanf("%d",&terminar);
		conteo_cartas=0;
		i++;
		if (i==4)
		{
			i=0;
		}
	}

	


	return 0;
}