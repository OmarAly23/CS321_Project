#include "project.h"
#include "die_with_error.h"
#define numOfProcesses 3
// #define arr 2

void die_with_error(char *msg); // Function Prototype

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct data {
	int burstTime;
	int arrivalTime;
	int priority;
	int quantumTime;
} data;

data dt_main[numOfProcesses];


void *safe_calloc(size_t size) {
	void *temp = calloc(numOfProcesses, size);

	if (temp == NULL)
		die_with_error("Error Allocating Data");
	
	return temp;
}

void *fcfs(void *arg) {

	/* The struct d2 should contain the burst and arrival time of all the processes */
	data *dt = safe_calloc( (sizeof *dt) * numOfProcesses);
	memcpy(dt, dt_main, (sizeof *dt) * numOfProcesses);

	for (int t = 0; t < numOfProcesses; t++) {
		printf("%d %d %d %d\n", dt[t].burstTime, dt[t].arrivalTime, dt[t].priority, dt[t].quantumTime);
	}

	free(dt);

	pthread_detach(pthread_self());


	// int waitingTime[ASIZE] = {};
	// int processes[ASIZE] = {};
	// // int waitingTime[ASIZE] = {};
	// int turnAroundTime[ASIZE] = {};
	// int total_waiting_time = 0;
	// int total_turnAround_time = 0;
	// int position = 0, tempVal = 0, total = 0, i = 0, j = 0;
	// double waitingAvg = 0.0, turnAroundAvg = 0.0;


	// for (int p = 0; p < numOfProcesses; p++) {
	// 	printf("Enter Burst Time For Process[%d]:	%d\n", p+1, dt[p].burstTime);
	// 	processes[p] = p+1;
	// }

	// /* First we find the waiting time */
	// /* The waiting time of the first process is always zero */
	// waitingTime[0] = 0;

	// for (i = 0; i < numOfProcesses; i++)
	// 	waitingTime[i] = dt[i].burstTime + waitingTime[i-1];

	// /* Now we calculate the average turnAround time
	//  * TurnAround time is calculated by adding the burst time with the waitingtime
	//  * BurstTime + waitingTime;
	//  */

	// for (i = 0; i < numOfProcesses; i++)
	// 	turnAroundTime[i] = dt[i].burstTime + waitingTime[i];

	// /* Now we display each processes's information
	//  * Burst time, waiting time and turnAround time
	//  */

	// printf("\nProcesses	Burst time	Waiting time	TurnAround time\n\n");


	// for (i = 0; i < numOfProcesses; i++) {

	// 	total_waiting_time += waitingTime[i];
	// 	total_turnAround_time += turnAroundTime[i];

	// 	printf("Process	[%d] ", (i+1));
	// 	printf("	   %d ", dt[i].burstTime);
	// 	printf("		%d ", waitingTime[i]);
	// 	printf("		     %d\n", turnAroundTime[i]);

	// }

	// waitingAvg = (double)total_waiting_time / numOfProcesses;
	// turnAroundAvg = (double)total_turnAround_time / numOfProcesses;

	// printf("\nAverage waiting time = %.6f\n", waitingAvg);
	// printf("Average turn around time = %.6f\n", turnAroundAvg);


	return NULL;
}
/* Shortest Job First Preemptive Scheduling Algorithm */
void *sjfPreemptive(void *arg) {

	/* The struct d2 should contain the burst and arrival time of all the processes */
	data *dt = safe_calloc( (sizeof *dt) * numOfProcesses);
	memcpy(dt, dt_main, (sizeof *dt) * numOfProcesses);

	for (int t = 0; t < numOfProcesses; t++) {
		printf("%d %d %d %d\n", dt[t].burstTime, dt[t].arrivalTime, dt[t].priority, dt[t].quantumTime);
	}

	free(dt);

	pthread_detach(pthread_self());

	// int waitingTime[ASIZE] = {};
	// int processes[ASIZE] = {};
	// int waitTime = 0;
	// int turnAroundTime[ASIZE] = {};
	// int tempArr[ASIZE] = {};
	// int total_waiting_time = 0;
	// int total_turnAround_time = 0;
	// int position = 0, tempVal = 0, total = 0, closing_descriptor = 0;
	// double waitingAvg = 0.0, turnAroundAvg = 0.0;
	// int time = 0, count = 0, end = 0;
	// int i = 0, smallest = 0;

	// dt[numOfProcesses].burstTime = 9999;

	// for (time = 0; count != numOfProcesses; time++) {

	// 	smallest = numOfProcesses;
	// 	for (i = 0; i < numOfProcesses; i++) {

	// 		if (dt[i].arrivalTime <= time && dt[i].burstTime < dt[smallest].burstTime && dt[i].burstTime > 0)
	// 			smallest = i;

	// 	}
	// 	dt[smallest].burstTime--;
	// 	if (dt[smallest].burstTime == 0) {
	// 		count++;
	// 		end = time + 1;
	// 		waitTime += end - dt[smallest].arrivalTime;
	// 		total_turnAround_time += end - dt[smallest].arrivalTime;
	// 	}

	// }

	// waitingAvg = waitTime / numOfProcesses;
	// turnAroundAvg = total_turnAround_time / numOfProcesses;

	// printf("\nAverage Waiting Time:		%lf\n", waitingAvg);
	// printf("Average TurnAround Time:	%lf\n", turnAroundAvg);



	return NULL;
}
/* Shortest job first Non-Preemptive Scheduling Algorithm */
void *sjfNon(void *arg) {

	/* The struct d2 should contain the burst and arrival time of all the processes */
	data *dt = safe_calloc( (sizeof *dt) * numOfProcesses);
	memcpy(dt, dt_main, (sizeof *dt) * numOfProcesses);

	for (int t = 0; t < numOfProcesses; t++) {
		printf("%d %d %d %d\n", dt[t].burstTime, dt[t].arrivalTime, dt[t].priority, dt[t].quantumTime);
	}

	free(dt);

	pthread_detach(pthread_self());

	// int waitingTime[ASIZE] = {};
	// int processes[ASIZE] = {};
	// // int waitingTime[ASIZE] = {};
	// int turnAroundTime[ASIZE] = {};
	// int total_waiting_time = 0;
	// int total_turnAround_time = 0;
	// int position = 0, tempVal = 0, total = 0, closing_descriptor = 0, i = 0, j = 0;
	// double waitingAvg = 0.0, turnAroundAvg = 0.0;


	// for (int p = 0; p < numOfProcesses; p++) {
	// 	printf("Enter Burst Time For Process[%d]:	%d\n", p+1, dt[p].burstTime);
	// 	processes[p] = p+1;
	// }
	
	// /* Sorting algorithm of the burst time */
	// /* The burst times are being sorted using the selection sort algorithm */
	// for (i = 0; i < numOfProcesses; i++) {
	// 	position = i;
	// 	for (j = i; j < numOfProcesses; j++) {
	// 		if (dt[i].burstTime < dt[position].burstTime)
	// 			position = j;
	// 	}

	// 	/* Swapping */
	// 	tempVal = dt[i].burstTime;
	// 	dt[i].burstTime = dt[position].burstTime;
	// 	dt[position].burstTime = tempVal;

	// 	tempVal = processes[i];
	// 	processes[i] = processes[i];
	// 	processes[position] = tempVal;
	// }

	// /* The waiting time of the first element is always zero */
	// waitingTime[0] = 0;

	// /* The waiting time is computed by adding the burst time with the waiting time */
	// for (i = 1; i < numOfProcesses; i++) {
	// 	waitingTime[i] = 0;
	// 	for (j = 0; j < i; j++)
	// 		waitingTime[i] += dt[j].burstTime;
	// 	/* The total variable contains the sun of all the waiting time */
	// 	total += waitingTime[i];
	// }
	// /* 
	//  * Now that we have the sum of the waiting time and the number of processes 
	//  * We can compute the average of the waiting time
	//  */
	// waitingAvg = (double)total / numOfProcesses; 

	// /* re-initialize the variable to be used again for the turn around time calculation */
	// total = 0;
	
	// printf("\nProcess ID		Burst Time		Waiting Time		TurnAround Time\n");
	// for (i = 0; i < numOfProcesses; i++) {
	// 	turnAroundTime[i] = dt[i].burstTime + waitingTime[i];
	// 	total += turnAroundTime[i];
	// 	printf("\nProcess[%d]		%d			%d			%d\n", processes[i], dt[i].burstTime, waitingTime[i], turnAroundTime[i]);
	// }

	// /* The turn around time is the additon of the burst time with the waiting time */
	// turnAroundAvg = (double)total / numOfProcesses;

	// printf("\nAverage Waiting Time = %f\n", waitingAvg);
	// printf("\nAverage TurnAround Time = %f\n", turnAroundAvg);
	
	return NULL;
}



int main (void) {
		/* Considering that the data is to be read from a text file and shared among all thread */

	char *region = calloc(MAXBUF, sizeof(char));
	char buff[MAXBUF]; bzero(buff, sizeof(buff));
	struct stat info;
	int i = 0, j = 0;

	int fd = 0;
	fd = open("proj.txt", O_RDONLY, 0);
	if (fd < 0)
		die_with_error("Error opening the file");
	
	fstat(fd, &info);
	region = mmap(NULL, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	for (i = 0, j = 0; i < info.st_size; i++, j++)
		buff[j] = region[i];
	/* buff should now contain the contents of the entire file */


	// for (i = 0; i < info.st_size; i++) {
	// 	printf("%s\n", buff);
	// }

	int bt[numOfProcesses] = {};
	int at[numOfProcesses] = {};
	int pt[numOfProcesses] = {};
	int qt = atoi(buff[0]);

	printf("testing\n");
	char *temp = malloc(sizeof(char) * MAXBUF);
	temp = strcat(&buff[2], &buff[3]);
	bt[0] = atoi(temp);
	temp = strcat(&buff[5], &buff[6]);
	bt[1] = atoi(temp);
	temp = strcat(&buff[8], &buff[9]);
	bt[2] = atoi(temp);

	printf("testing1\n");
	at[0] = buff[10];
	at[1] = buff[12];
	at[2] = buff[14];

	printf("testing2\n");
	pt[0] = buff[15];
	pt[1] = buff[17];
	pt[2] = buff[19];

	
	for (i = 0; i < numOfProcesses; i++) {
		printf("%d %d %d\n", bt[i], at[i], pt[i]);
	}

	for (i = 0; i < numOfProcesses; i++) {
		dt_main[i].quantumTime = qt;
		dt_main[i].burstTime = bt[i];
		dt_main[i].arrivalTime = at[i];
		dt_main[i].priority = pt[i];
	}


	// dt_address = &dt;
	pthread_t tid1, tid2, tid3;
	
	/* The six threads each to represent one scheduling algorithm */

	/* First Come First Serve Scheduling Algorithm*/
	pthread_create(&tid1, NULL, fcfs,  NULL);
	
	/* Shortest Job First Preemptive Scheduling Algorithm */
	pthread_create(&tid2, NULL, sjfPreemptive, NULL);
	
	/* Shortest Job First Non-Preemptive Scheduling Algorithm */
	pthread_create(&tid3, NULL, sjfNon,  NULL);
	
	// /* Round Robin Scheduling Algorithm */
	// pthread_create(&tid4, NULL, roundRobin, &dt_address);
	
	// /* Priority Non-Preemptive Scheduling Algorithm*/
	// pthread_create(&tid5, NULL, priorityNon, &dt_address);
	
	// /* Priority Preemptive Scheduling Algorithm */
	// pthread_create(&tid6, NULL, priorityPre, &dt_address);

	

	/* Looping over each created thread to reap them */
	// pthread_join(tid1, NULL);
	// pthread_join(tid2, NULL);
	// pthread_join(tid3, NULL);



	close(fd);
	munmap(region, sizeof(region));
	return 0;
}
