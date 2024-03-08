#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lista_enlazada.h"

void printArray(int n, int disk_accesses[]){
	printf("[");
	for(int i=0;i<n;i++){
		printf("%d,",disk_accesses[i]);
	}
	printf("]\n");
}



void printFirst(int n, int disk_accesses[], int head){
    printf("Posicion inicial: %d\n", head);
    printf("Listado: ");
	printf("[");
	for(int i=0;i<n;i++){
		if(i !=n-1){
			printf("%d,",disk_accesses[i]);
		}else{
			printf("%d",disk_accesses[i]);
		}
	}
	printf("]\n");
}

void printLast(float promedio, float desviacion){
	printf("Promedio: %f\n",promedio);
	printf("Desviacion Estandar: %f\n",desviacion);
    printf("\n[--- END ---]\n");
}

void FIFO(int n, int disk_accesses[], int head){  // Works as FCFS - First Come First Serve
	printf("\n%s\n", "FIFO");
	printFirst(n, disk_accesses, head);
	float promedio,desviacion, varianza = 0;
	int seek_time, temp = 0;
	int muestras[n];
	// First Iteration 
	if(head > disk_accesses[0]){
		seek_time = head - disk_accesses[0];
	}else if(head < disk_accesses[0]){
		seek_time = disk_accesses[0] - head;
	}
	muestras[0] = seek_time;
	head = disk_accesses[0];
	//------------------------------------------s
	for(int i=1; i < n; i++){
		if(head > disk_accesses[i]){
			temp = head - disk_accesses[i];
		}else if(head < disk_accesses[i]){
			temp = disk_accesses[i] - head;
		}
		muestras[i] = temp;
		seek_time += temp;
		head = disk_accesses[i];
	}
	
	promedio = seek_time/n;

	// Calculo de Varianza
	for(int i=0; i < n; i++){
		varianza += pow(muestras[i] - promedio, 2);
	}
	varianza = varianza/(n - 1/1.0);

	desviacion = sqrt(varianza);

	printLast(promedio, desviacion);
}

void SCAN(int n, int disk_accesses[], int head) {
	int muestras[n];
	int direccion, j, temp, seek_time = 0;
	float promedio,desviacion, varianza = 0;
	struct Nodo *mayores = NULL;
	struct Nodo *menores = NULL;

	printf("Ingrese direccion de rotacion \nDerecha -	1 \nIzquierda -	2\n");
	printf("Seleccione una opcion: ");
	scanf("%d", &direccion);
	printf("\n%s\n", "SCAN");
	printFirst(n, disk_accesses, head);


	//Dividir el arreglo en 2
	for(int i=0; i<n; i++){
		if(head > disk_accesses[i]){
			insertarAlInicio(&menores, disk_accesses[i]);
		}else if(head < disk_accesses[i]){
			insertarAlInicio(&mayores, disk_accesses[i]);
		}
	}

	ordenarListaDesc(&menores);
	ordenarListaAsc(&mayores);
	imprimirLista(menores);
	imprimirLista(mayores);

	//Derecha
	if(direccion == 1){
		//empieza desde el head con el menor de los mayores
		// Recorre a la Derecha Primero
		while(mayores != NULL){
			printf("%d", mayores->dato );
			temp = mayores->dato - head;
			printf("%d", temp);
			printf("%d", mayores->siguiente->dato);
			head =  mayores->dato;
			if(mayores->siguiente != NULL){
				mayores = mayores->siguiente;
			}
			seek_time += temp;
			muestras[j] = temp;
			j++;
		}

		// Recorre a la Izquierda Luego
		while(menores != NULL){
			temp = head - menores->dato;
			head =  menores->dato;
			if(menores->siguiente != NULL){
				menores = menores->siguiente;
			}
			seek_time += temp;
			muestras[j] = temp;
			j++;
			printf("%i", j);

		}
	}else if(direccion == 2){ // Izquierda
		//empieza desde el head con el mayor de los menores
		// Recorre a la Izquierda Primero
		while(menores != NULL){
			temp = head - menores->dato;
			head =  menores->dato;
			if(menores->siguiente != NULL){
				menores = menores->siguiente;
			}
			seek_time += temp;
			muestras[j] = temp;
			j++;
		}
		// Recorre a la Derecha Luego
		while(mayores != NULL){
			temp = mayores->dato - head;
			head =  mayores->dato;
			if(mayores->siguiente != NULL){
				mayores = mayores->siguiente;
			}
			seek_time += temp;
			muestras[j] = temp;
			j++;
		}
	}

	while (menores != NULL) {
        struct Nodo *temp_l = menores;
        menores = menores->siguiente;
        free(temp_l);
    }

	while (mayores != NULL) {
        struct Nodo *temp_l = mayores;
        mayores = mayores->siguiente;
        free(temp_l);
    }

	promedio = seek_time/n;

	// Calculo de Varianza
	for(int i=0; i < n; i++){
		varianza += pow(muestras[i] - promedio, 2);
	}
	varianza /= n - 1;

	desviacion = sqrt(varianza);

	printLast(promedio, desviacion);
} 

void CSCAN(int n, int disk_accesses[], int head) {
	printf(" --> CSACN\n");
	
} 

void SSTF(int n, int arr[], int head) {
	printf(" --> SSTF\n");
	printArray(n, arr);
} 

int menu(){
	int tmp;
	printf("---------------------------------------\n1 - FIFO\n2 - SCAN\n3 - C-SACN\n4 - SSTF\n0 - EXIT\n\nSeleccione Opcion: ");
	scanf("%d", &tmp);
	return tmp;
}

int main ( int argc , char * argv []) {
	int op = 9;
    int n = 0;
    int head = 0;
	while (op > 0){
		op = menu();
		printf("Procesando opcion: %d\n", op);
		if ( op >5 || op<=0 ){
			printf("--- END ---\n");
			break;
		}

        printf("Numero de requerimientos a ingresar a disco: ");
		scanf("%d",&n);
        int arr[n];
        for(int i= 0; i < n; i++){
		    printf("Ingrese Valor: ");
		    scanf("%d",&arr[i]);
	    }
        printf("Ingrese Posicion inicial de la cabeza lectora: ");
		scanf("%d",&head);
		printf("--- BEGIN ---\n");
		switch(op){
			case 1:
			FIFO(n, arr, head);
			break;
			case 2:
			SCAN(n, arr, head);
			break;
			case 3:
			CSCAN(n, arr, head);
			break;
			default:
			case 4:
			SSTF(n, arr, head);
			break;
		}
	}
	return 0;
}

