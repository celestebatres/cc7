#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20
#define N 29
#define FILE_SCHEDULE "listProcess.cpu"


char *tokens[] = {" ", " ", " ", " "};
// Header del FILE
struct process
{
	char *pxx;
	int at;
	int bt;
	int v;
};

struct process arr_process[N];
// Functions
int powI(int x, int y){
	int result = 1;
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

int to_int(char* chars) {
    int sum = 0;
    int len = strlen(chars);
    for (int x = 0; x < len; x++){
        int n = chars[len - (x + 1)] - '0';
        sum = sum + powI(n, x);
    }
    return sum;
}

void output(void *vargp) {
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|PXX\t|QU\t|QM\t|AT\t|BT\t|ET\t|WT\t|RT\t|TT\t|\n");
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n\n");
} 

void read_file(){
	FILE *file_s = fopen(FILE_SCHEDULE, "r");
	char buffer[SIZE];
	output(0);
	fgets(buffer, SIZE, file_s); //Linea 0
	int i = 0;

	while(fgets(buffer, SIZE, file_s)){
		strtok(buffer, "\n");
		tokens[0]=strtok(buffer, "	");
		for (int j = 1; j < 4; j++) {
            tokens[j] = strtok(NULL, "\t");
        }

		arr_process[i].pxx = tokens[0];
		arr_process[i].at = to_int(tokens[1]);
		arr_process[i].bt = to_int(tokens[2]);
		arr_process[i].v = to_int(tokens[3]);

		i++;
	}
	printf("%s  ", arr_process[1].pxx);
	fclose(file_s);
}


void FCFS(void *vargp) {
	printf(" --> FCFS\n");
	read_file();
	for(int i = 1; i<=28; i++){
		printf("%s  ", arr_process[i].pxx);
		
		printf("%i  ", arr_process[i].bt);
		printf("%i  ", arr_process[i].v);
		printf("\n");
	}
	printf("%s", arr_process[0].pxx);
} 

void PS(void *vargp) {
	printf(" --> PS\n");
	read_file();
} 

void RR(void *vargp) {
	printf(" --> RR\n");
	read_file();
} 

void MLFQS(void *vargp) {
	printf(" --> MLFQS\n");
	read_file();
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

	// Menu 
	int op = 9;
	pid_t pid;
	while (op > 0){
		op = menu();
		printf(">> Procesando opción: %d\n\n", op);
		if ( op >5 || op<=0 ){
			printf("### END ###\n\n");
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