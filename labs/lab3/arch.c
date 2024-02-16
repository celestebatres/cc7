#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#define SIZE 20
#define N 29
#define FILE_SCHEDULE "listProcess.cpu"

// Header del FILE
struct process
{
	char *pxx;
	int at;
	int bt;
	int v;
}

struct process arr_process[N];
char *tokens[4];

// Functions
int pow(int x, int y){
	int result = 1;
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

int to_int(char* chars) {
    int sum = 0;
    int len = strlen(chars);

    for (int i = len - 1; i >= 0; i--) {
        int digit = chars[i] - '0';
        sum += pow(digit, len - 1 - i);
    }

    return sum;
}

void output(void *vargp) {
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|PXX\t|QU\t|QM\t|AT\t|BT\t|ET\t|WT\t|RT\t|TT\t|\n");
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n\n");
} 

void read_file(){
	FILE *file = fopen(FILE_SCHEDULE, "r");

	if (file == NULL) {
        printf("\n### Not able to open the file. ###\n\n");
    }

	char buffer[SIZE];

	
	int i = 0;

	output(0);

	fgets(buffer, SIZE, file);

	while (fgets(buffer, SIZE, archivo) != NULL) {
		strtok(buffer, "\n");
		tokens[0] = strtok(buffer, "\t");
		for (int j = 1; j < 4; j++) {
            tokens[j] = strtok(NULL, "\t");
        }
		arr_process[i].pxx = tokens[0];
		arr_process[i].at = parse_int(tokens[1]);
		arr_process[i].bt = parse_int(tokens[2]);
		arr_process[i].v = parse_int(tokens[3]);
		i++;
	}
	fclose(file);

}


void FCFS(void *vargp) {
	printf(" --> FCFS\n");
	read_file();
	for(int i = 0; i<28; i++){
		printf("%s", process[i].pxx);
	}
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