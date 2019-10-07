#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h> 
#include <string.h>
#include <time.h>


/*
Descripcion: Con esto el padre es el ultimo en ejecutarse.
Falta: Faltaria hacer que se cumpla el orden: padre, hijo1, hijo2, hijo3
Y agregar pipes
*/
void lectura(int canal[2]){
	char buf[1];
	close(canal[1]);
	read(canal[0], buf, sizeof(canal[0]));
	printf("%s\n",buf );
}

void envio(int canal[2], char Msj[1])
{
	close(canal[0]);//Cierro Lectura
	//open(canal[0]);//Abro escritura
	write(canal[1], Msj, 1); //4) ESTA FUNCION ESPERA SI O SI AL HIJO
	close(canal[1]); //Cierro Escritura
}

int main(int argc, char **argv)
{
	int canalTurno1[2], canalTurno2[2], canalTurno3[2];
	int canalTermino1[2], canalTermino2[2], canalTermino3[2];
	pid_t pid;
	pipe(canalTurno1);
	pipe(canalTurno2);
	pipe(canalTurno3);
	for(int i=0; i < 3;i++)
	{
		pid = fork();
		if(pid==0)
		{
			//Como no qro hijos de hijos
			//hijo ejecuta y termina
			break;
		}
	}
	int i=1;
	if (getppid()+1==getpid())
	{
		printf("%d\n",getpid());
		lectura(canalTurno1); //espera mensaje del padre
		return 0;
	}
	else if (getppid()+2==getpid()){
		printf("%d\n",getpid() ); 
		lectura(canalTurno2); //espera mensaje del padre
		return 0;
	}
	else if (getppid()+3==getpid()){
	
		printf("%d\n",getpid() );
		lectura(canalTurno3); //espera mensaje del padre
		return 0;
	}
	while(i<5){
		if (i==1){
			envio(canalTurno1, "1"); //envia mensaje
			i++;
		}
		else if (i==2){
			envio(canalTurno2, "2"); //envia mensaje
			i++;
		}
		else if (i==3){
			envio(canalTurno3, "3"); //envia mensaje
			i++;
		}
		else{
			i=1;
		}
	}
	return 0;
}