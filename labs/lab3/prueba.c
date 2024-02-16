#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO "listProcess.cpu"
#define SIZE 20
#define N 29

char *tokens[] = {" ", " ", " ", " "};

struct array{
	char *pxx;
	int at;
	int bt;
	int v;
};

struct array process[N];

int powInt(int x, int y){
    for (int i = 0; i < y; i++){
        x *= 10;
    }
    return x;
}

int parseInt(char* chars){
    int sum = 0;
    int len = strlen(chars);
    for (int x = 0; x < len; x++){
        int n = chars[len - (x + 1)] - '0';
        sum = sum + powInt(n, x);
    }
    return sum;
}

void output(void *vargp) {
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|PXX\t|QU\t|QM\t|AT\t|BT\t|ET\t|WT\t|RT\t|TT\t|\n");
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n\n");
} 

void readFile(){
	FILE *archivo = fopen(ARCHIVO, "r");
	char buffer[SIZE];
	output(0);
	fgets(buffer, SIZE, archivo);
	int i,j = 0;
	char *arr[28];
	char *val[28][3];

	while(fgets(buffer, SIZE, archivo)){
		strtok(buffer, "\n");
		tokens[0]=strtok(buffer, "	");
		tokens[1]= strtok(NULL,"	");
		tokens[2]= strtok(NULL,"	");
		tokens[3]= strtok(NULL,"	");
		
		process[i].pxx = tokens[0];
		process[i].at = parseInt(tokens[1]);
		process[i].bt = parseInt(tokens[2]);
		process[i].v = parseInt(tokens[3]);

		//printf("\n%s", process[0].pxx);
		i++;
	}
	fclose(archivo);
}

void FCFS(void *vargp) {
	printf(" --> FCFS\n");
	readFile();
	for(int i = 0; i<28; i++){
		printf("%s", process[i].pxx);
	}	
	printf("%s", process[0].pxx);
} 

void PS(void *vargp) {
	printf(" --> PS\n");
	readFile();
} 

void RR(void *vargp) {
	printf(" --> RR\n");
	readFile();
} 

void MLFQS(void *vargp) {
	printf(" --> MLFQS\n");
	readFile();
} 

int menu(){
	int tmp;
	printf("############\n1 - FCFS\n2 - PS\n3 - RR\n4 - MLFQS\n0 - EXIT\n\nSeleccione Opción: ");
	scanf("%d", &tmp);
	return tmp;
}

// C Concepts 
// https://gist.github.com/Integralist/6c35d4f26c0c7bf5bdce7b95cfa906b3
int main ( int argc , char * argv []) {
	int op = 9;
	pid_t pid;
	while (op > 0){
		op = menu();
		printf("Procesando opción: %d\n", op);
		if ( op >5 || op<=0 ){
			printf("### END ###\n");
			break;
		}
		printf("### BEGIN ###\n");
		switch(op){
			case 1:
			FCFS(0);
			break;
			case 2:
			PS(0);
			break;
			case 3:
			RR(0);
			break;
			default:
			case 4:
			MLFQS(0);
			break;
		}
	}
	return 0;
}