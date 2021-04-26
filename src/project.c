

#include "project.h"
#include "die_with_error.h"


void *thread_function1(void *arg) {

	long *ID = (long *)arg;
	printf("Testing thread1 tid: %ld\n", *ID);

	return NULL;
}

void *thread_function2(void *arg) {

	long *ID = (long *)arg;
	printf("Testing thread2 tid: %ld\n", *ID);

	return NULL;
}

void *thread_function3(void *arg) {

	long *ID = (long *)arg;
	printf("Testing thread2 tid: %ld\n", *ID);


	return NULL;
}


int main (void) {

	pthread_t tid0, tid1, tid2;
	int i = 0;
	
	
	pthread_create(&tid0, NULL, thread_function1, (void *)&tid0);	
	pthread_create(&tid1, NULL, thread_function2, (void *)&tid1);
	pthread_create(&tid2, NULL, thread_function3, (void *)&tid2);


	pthread_exit(NULL);

	return 0;
}
