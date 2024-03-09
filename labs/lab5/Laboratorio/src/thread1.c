#include<stdio.h>
#include<pthread.h>

unsigned int sleep (unsigned int seconds);

/* this function is run by the Example 1 */
void *say_hello(void *data) {
	char *str = (char *) data;
	while(1){
		printf("%s\n", str);
		sleep(1);
	}
}

/* this function is run by the second thread */
void *inc_x(void *x_void_ptr) {
	/* increment x to 100 */
	int *x_ptr = (int *)x_void_ptr;
	while(++(*x_ptr) < 15){
		printf("X:%d\n", (*x_ptr) );
		sleep(0.3);
	}
	printf("x increment finished\n");
	/* the function must return something - NULL will do */
	return NULL;
}

int Example1() {
	pthread_t t1,t2;

	pthread_create(&t1,NULL,say_hello,"Hello from Thread 1");
	pthread_create(&t2,NULL,say_hello,"hello from Thread 2");

	pthread_join(t1,NULL);

	return 0;
}

int Example2() {
	int x = 0, y = 0;

	/* this variable is our reference to the second thread */
	pthread_t inc_x_thread;

	/* show the initial values of x and y */
	printf("x: %d, y: %d\n", x, y); 

	/* create a second thread which executes inc_x(&x) */
	if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	/* increment y to 15 in the first thread */
	while(++y < 15){
		printf("Y:%d\n", y);
		sleep(0.5);
	};
	printf("y increment finished\n");

	/* wait for the second thread to finish */
	if(pthread_join(inc_x_thread, NULL)) {
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}

	/* show the results - x is now 15 thanks to the second thread */
	printf("x: %d, y: %d\n", x, y);

	/* return EXIT_SUCCESS (traditionally 0) we hope something worked well */
	return 0;
}

int main() {
	int example, flag;
	flag = 1;
	while(flag){
		printf("\n### THREAD EXAMPLES ###\n\t1) Example 1\n\t2) Example 2\n\t3) Exit\nChoose a number: ");
		scanf("%d",&example);
		switch(example) {
			case 1: Example1();
			case 2: Example2();
			case 3: flag = 0;
		}
		
	}
	return(0);
}
