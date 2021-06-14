#include "project.h"
#include "die_with_error.h"
#define numOfProcesses 3
// #define arr 2

void die_with_error(char *msg); // Function Prototype

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex5 = PTHREAD_MUTEX_INITIALIZER;



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
	printf("\n\n*************************FCFS*************************\n\n");
	/* The struct d2 should contain the burst and arrival time of all the processes */
	data *dt = safe_calloc( (sizeof *dt) * numOfProcesses);
	memcpy(dt, dt_main, (sizeof *dt) * numOfProcesses);

	// for (int t = 0; t < numOfProcesses; t++) {
	// 	printf("%d %d %d %d\n", dt[t].burstTime, dt[t].arrivalTime, dt[t].priority, dt[t].quantumTime);
	// }

	// free(dt);

	// pthread_detach(pthread_self());

	int waitingTime[ASIZE] = {};
	int processes[ASIZE] = {};
	// int waitingTime[ASIZE] = {};
	int turnAroundTime[ASIZE] = {};
	int total_waiting_time = 0;
	int total_turnAround_time = 0;
	int position = 0, tempVal = 0, total = 0, i = 0, j = 0;
	double waitingAvg = 0.0, turnAroundAvg = 0.0;

	//pthread_mutex_lock(&mutex);
	for (int p = 0; p < numOfProcesses; p++) {
		printf("Enter Burst Time For Process[%d]:	%d\n", p+1, dt[p].burstTime);
		processes[p] = p+1;
	}

	/* First we find the waiting time */
	/* The waiting time of the first process is always zero */
	waitingTime[0] = 0;

	for (i = 0; i < numOfProcesses; i++)
		waitingTime[i] = dt[i].burstTime + waitingTime[i-1];

	/* Now we calculate the average turnAround time
	 * TurnAround time is calculated by adding the burst time with the waitingtime
	 * BurstTime + waitingTime;
	 */

	for (i = 0; i < numOfProcesses; i++)
		turnAroundTime[i] = dt[i].burstTime + waitingTime[i];

	/* Now we display each processes's information
	 * Burst time, waiting time and turnAround time
	 */

	printf("\nProcesses	Burst time	Waiting time	TurnAround time\n\n");


	for (i = 0; i < numOfProcesses; i++) {

		total_waiting_time += waitingTime[i];
		total_turnAround_time += turnAroundTime[i];

		printf("Process	[%d] ", (i+1));
		printf("	   %d ", dt[i].burstTime);
		printf("		%d ", waitingTime[i]);
		printf("		     %d\n", turnAroundTime[i]);

	}

	waitingAvg = (double)total_waiting_time / numOfProcesses;
	turnAroundAvg = (double)total_turnAround_time / numOfProcesses;

	printf("\nAverage waiting time = %.6f\n", waitingAvg);
	printf("Average turn around time = %.6f\n", turnAroundAvg);

	//pthread_mutex_unlock(&mutex);

	free(dt);

	return NULL;
}
/* Shortest Job First Preemptive Scheduling Algorithm */
void *sjfPreemptive(void *arg) {
	printf("\n\n*************************Shortest Job Preemptive*************************\n\n");
	/* The struct d2 should contain the burst and arrival time of all the processes */
	data *dt = safe_calloc( (sizeof *dt) * numOfProcesses);
	memcpy(dt, dt_main, (sizeof *dt) * numOfProcesses);

	// for (int t = 0; t < numOfProcesses; t++) {
	// 	printf("%d %d %d %d\n", dt[t].burstTime, dt[t].arrivalTime, dt[t].priority, dt[t].quantumTime);
	// }

	// free(dt);

	// pthread_detach(pthread_self());

	
	int waitingTime[ASIZE] = {};
	int processes[ASIZE] = {};
	int waitTime = 0;
	int turnAroundTime[ASIZE] = {};
	int tempArr[ASIZE] = {};
	int total_waiting_time = 0;
	int total_turnAround_time = 0;
	int position = 0, tempVal = 0, total = 0, closing_descriptor = 0;
	double waitingAvg = 0.0, turnAroundAvg = 0.0;
	int time = 0, count = 0, end = 0;
	int i = 0, smallest = 0;

	dt[numOfProcesses].burstTime = 9999;

	//pthread_mutex_lock(&mutex1);

	for (time = 0; count != numOfProcesses; time++) {

		smallest = numOfProcesses;
		for (i = 0; i < numOfProcesses; i++) {

			if (dt[i].arrivalTime <= time && dt[i].burstTime < dt[smallest].burstTime && dt[i].burstTime > 0)
				smallest = i;

		}
		dt[smallest].burstTime--;
		if (dt[smallest].burstTime == 0) {
			count++;
			end = time + 1;
			waitTime += end - dt[smallest].arrivalTime;
			total_turnAround_time += end - dt[smallest].arrivalTime;
		}

	}

	waitingAvg = waitTime / numOfProcesses;
	turnAroundAvg = total_turnAround_time / numOfProcesses;

	printf("\nAverage Waiting Time:		%lf\n", waitingAvg);
	printf("Average TurnAround Time:	%lf\n", turnAroundAvg);

	//pthread_mutex_unlock(&mutex1);
	free(dt);

	return NULL;
}
/* Shortest job first Non-Preemptive Scheduling Algorithm */
void *sjfNon(void *arg) {
	printf("\n\n*************************Shortest Job NonPreemptive*************************\n\n");
	/* The struct d2 should contain the burst and arrival time of all the processes */
	data *dt = safe_calloc( (sizeof *dt) * numOfProcesses);
	memcpy(dt, dt_main, (sizeof *dt) * numOfProcesses);

	// for (int t = 0; t < numOfProcesses; t++) {
	// 	printf("%d %d %d %d\n", dt[t].burstTime, dt[t].arrivalTime, dt[t].priority, dt[t].quantumTime);
	// }

	// free(dt);

	// pthread_detach(pthread_self());
	

	int waitingTime[ASIZE] = {};
	int processes[ASIZE] = {};
	// int waitingTime[ASIZE] = {};
	int turnAroundTime[ASIZE] = {};
	int total_waiting_time = 0;
	int total_turnAround_time = 0;
	int position = 0, tempVal = 0, total = 0, closing_descriptor = 0, i = 0, j = 0;
	double waitingAvg = 0.0, turnAroundAvg = 0.0;

	//pthread_mutex_lock(&mutex2);
	
	for (int p = 0; p < numOfProcesses; p++) {
		printf("Enter Burst Time For Process[%d]:	%d\n", p+1, dt[p].burstTime);
		processes[p] = p+1;
	}
	
	/* Sorting algorithm of the burst time */
	/* The burst times are being sorted using the selection sort algorithm */
	for (i = 0; i < numOfProcesses; i++) {
		position = i;
		for (j = i; j < numOfProcesses; j++) {
			if (dt[i].burstTime < dt[position].burstTime)
				position = j;
		}

		/* Swapping */
		tempVal = dt[i].burstTime;
		dt[i].burstTime = dt[position].burstTime;
		dt[position].burstTime = tempVal;

		tempVal = processes[i];
		processes[i] = processes[i];
		processes[position] = tempVal;
	}

	/* The waiting time of the first element is always zero */
	waitingTime[0] = 0;

	/* The waiting time is computed by adding the burst time with the waiting time */
	for (i = 1; i < numOfProcesses; i++) {
		waitingTime[i] = 0;
		for (j = 0; j < i; j++)
			waitingTime[i] += dt[j].burstTime;
		/* The total variable contains the sun of all the waiting time */
		total += waitingTime[i];
	}
	/* 
	 * Now that we have the sum of the waiting time and the number of processes 
	 * We can compute the average of the waiting time
	 */
	waitingAvg = (double)total / numOfProcesses; 

	/* re-initialize the variable to be used again for the turn around time calculation */
	total = 0;
	
	printf("\nProcess ID		Burst Time		Waiting Time		TurnAround Time\n");
	for (i = 0; i < numOfProcesses; i++) {
		turnAroundTime[i] = dt[i].burstTime + waitingTime[i];
		total += turnAroundTime[i];
		printf("\nProcess[%d]		%d			%d			%d\n", processes[i], dt[i].burstTime, waitingTime[i], turnAroundTime[i]);
	}

	/* The turn around time is the additon of the burst time with the waiting time */
	turnAroundAvg = (double)total / numOfProcesses;

	printf("\nAverage Waiting Time = %f\n", waitingAvg);
	printf("\nAverage TurnAround Time = %f\n", turnAroundAvg);
	
	//pthread_mutex_unlock(&mutex2);

	free(dt);

	return NULL;
}


/* Round Robin Scheduling Algorithm */
void *roundRobin(void *arg) {
	printf("\n\n*************************Round Robin*************************\n\n");
	/* The struct d2 should contain the burst and arrival time of all the processes */
	data *dt = safe_calloc( (sizeof *dt) * numOfProcesses);
	memcpy(dt, dt_main, (sizeof *dt) * numOfProcesses);

	int temp[ASIZE];
	int count = 0, sum = 0;
	int wt = 0, tat = 0;
	double avg_wt, avg_tat;
	int i = 0, y = 0;
	// Use for loop to enter the details of the process like Arrival time and the Burst Time
	//pthread_mutex_lock(&mutex3);

	for(i=0; i< numOfProcesses; i++) {
	
		printf("\n Enter the Arrival and Burst time of the Process[%d]\n", i+1);
		printf(" Arrival time is: \t%d", dt[i].arrivalTime); 
		printf(" \nBurst time is: \t%d", dt[i].burstTime);
		temp[i] = dt[i].burstTime; // store the burst time in temp array
	}
	
	// Accept the Time qunat
	printf("Enter the Time Quantum for the process: \t%d", dt[i].quantumTime);
	// Display the process No, burst time, Turn Around Time and the waiting time
	printf("\n Process No \t\t Burst Time \t\t TAT \t\t Waiting Time ");
	
	for(sum=0, i = 0; y!=0;) {
	
		if(temp[i] <= dt[i].quantumTime && temp[i] > 0) { // define the condition 
	    		sum = sum + temp[i];
	    		temp[i] = 0;
	    		count=1;
    		} else if(temp[i] > 0) {
			
        		temp[i] = temp[i] - dt[i].quantumTime;
        		sum = sum + dt[i].quantumTime;
    		}
    		
		if(temp[i]==0 && count==1) {
			
        		y--; //decrement the process no.
        		printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", i+1, dt[i].burstTime, sum-dt[i].arrivalTime, sum-dt[i].arrivalTime-dt[i].burstTime);
        		wt = wt+sum-dt[i].arrivalTime-dt[i].burstTime;
       	 		tat = tat+sum-dt[i].arrivalTime;
        		count =0;
  	  	}
  	  
		if(i==numOfProcesses-1) {
  	      		i=0;
  	  	} else if(dt[i+1].arrivalTime<=sum) {
       	 		i++;
    		  } else {
        		i=0;
 	   		}
	}
	
	// represents the average waiting time and Turn Around time
	avg_wt = wt * 1.0/numOfProcesses;
	avg_tat = tat * 1.0/numOfProcesses;
	printf("\n Average Turn Around Time: \t%f", avg_wt);
	printf("\n Average Waiting Time: \t%f", avg_tat);
	// getch();  
	//pthread_mutex_unlock(&mutex3);
	free(dt);
	return NULL;
}

/* Priority Non-Preemptive Schedling Algorithm */
void *priorityNon(void *arg) {
		printf("\n\n*************************Non Preemptive Priority*************************\n\n");
	/* The struct d2 should contain the burst and arrival time of all the processes */

		data *dt = safe_calloc( (sizeof *dt) * numOfProcesses);
		memcpy(dt, dt_main, (sizeof *dt) * numOfProcesses);

		
		int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,total=0,pos,temp,avg_wt,avg_tat;
		//pthread_mutex_lock(&mutex4);

		printf("\nEnter Burst Time and Priority\n");
		for(i=0;i<numOfProcesses;i++) {
	
			printf("\nP[%d]\n",i+1);
			printf("Burst Time: %d\n", dt[i].burstTime);
			printf("Priority: %d\n", dt[i].priority);
			p[i]=i+1; //contains process number
		}

		//sorting burst time, priority and process number in ascending order using selection sort
		for(i=0;i<numOfProcesses;i++) {

			pos=i;
			for(j=i+1;j<numOfProcesses;j++) {
				if(pr[j]<pr[pos])
					pos=j;
			}

			temp=dt[i].priority;
			dt[i].priority=dt[pos].priority;
			dt[pos].priority=temp;

			temp=dt[i].burstTime;
			dt[i].burstTime=dt[pos].burstTime;
			dt[pos].burstTime=temp;
	
			temp=p[i];
			p[i]=p[pos];
			p[pos]=temp;
		}

		wt[0]=0;	//waiting time for first process is zero

		//calculate waiting time
		for(i=1;i<numOfProcesses;i++) {
			wt[i]=0;
			for(j=0;j<i;j++)
					wt[i]+=dt[j].burstTime;

			total+=wt[i];
		}

		avg_wt=total/numOfProcesses;//average waiting time
		total=0;

		printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
		for(i=0;i<numOfProcesses;i++) {
		
			tat[i]=dt[i].burstTime+wt[i]; //calculate turnaround time
			total+=tat[i];
			printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d",p[i],dt[i].burstTime,wt[i],tat[i]);
		}

		avg_tat=total/numOfProcesses; //average turnaround time
		printf("\n\nAverage Waiting Time=%d",avg_wt);
		printf("\nAverage Turnaround Time=%d\n",avg_tat);

		//pthread_mutex_unlock(&mutex4);
		free(dt);
		return NULL;
}

/* Priority Preemptive Scheduling Algorithm */
void *priorityPre(void *arg) {
	printf("\n\n*************************Preemptive Priority*************************\n\n");
	/* The struct d2 should contain the burst and arrival time of all the processes */
	data *dt = safe_calloc( (sizeof *dt) * numOfProcesses);
	memcpy(dt, dt_main, (sizeof *dt) * numOfProcesses);
	int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,total=0,pos,temp= 0;
	double avg_wt,avg_tat;


	//pthread_mutex_lock(&mutex5);
	for(i=0;i<numOfProcesses;i++) {

	printf("Enter process %d burst time: %d",i+1, dt[i].burstTime);

	printf("Enter process %d priority: %d",i+1, dt[i].priority);

	}

	for(i=0;i<numOfProcesses;i++) {

		for(j=i+1;j<numOfProcesses;j++) {

			if(dt[i].priority>dt[j].priority) {

				temp = dt[i].priority;
				dt[i].priority = dt[j].priority;
				dt[j].priority = temp;

				temp = dt[i].burstTime;
				dt[i].burstTime = dt[j].burstTime;
				dt[j].burstTime = temp;

			}

		}

		wt[i]=0;

	}

	for(i=0;i<numOfProcesses;i++) {

		for(j=0;j<i;j++) {

			wt[i]=wt[i]+dt[j].burstTime;

		}

		tat[i]=wt[i]+dt[i].burstTime;

	}

	printf("Process\tP\tBT\tWT\tTAT\n");

	for(i=0;i<numOfProcesses;i++) {

		printf("%d\t%d\t%d\t%d\n",dt[i].priority,dt[i].burstTime,wt[i],tat[i]);

		avg_wt=avg_wt+wt[i];

		avg_tat=avg_tat+tat[i];

	}

	avg_wt=avg_wt/numOfProcesses;

	avg_tat=avg_tat/numOfProcesses;

	printf("Average Waiting Time: %f\n",avg_wt);

	printf("\nAverage Turnaround Time: %f",avg_tat);

	//pthread_mutex_unlock(&mutex5);
	free(dt);
	return NULL;	

}



int main (void) {
		/* Considering that the data is to be read from a text file and shared among all thread */

	char *region = calloc(MAXBUF, sizeof(char));
	char buff[100]; bzero(buff, sizeof(buff));
	char *temp = malloc(sizeof(char) * MAXBUF);
	char *temp2 = malloc(sizeof(char) * MAXBUF);
	char *temp3 = malloc(sizeof(char) * MAXBUF);
	struct stat info;
	int i = 0, j = 0;

	int fd = 0;
	fd = open("proj.txt", O_RDONLY, 0);
	if (fd < 0)
		die_with_error("Error opening the file");
	
	fstat(fd, &info);
	// printf("The size of the file is: %ld\n", info.st_size);
	region = mmap(NULL, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	for (i = 0, j = 0; i < info.st_size; i++, j++)
		buff[j] = region[i];
	/* buff should now contain the contents of the entire file */


	// for (i = 0; i < info.st_size; i++) {
	// 	printf("%s\n", buff);
	// }

	int bt[3] = {};
	int at[3] = {};
	int pt[3] = {};
	int qt = atoi(&buff[0]);

	// printf("testing\n");
	temp = strcat(&buff[2], &buff[3]);
	bt[0] = atoi(temp);
	temp2 = strcat(&buff[5], &buff[6]);
	bt[1] = atoi(temp);
	// temp3 = strcat(&buff[8], &buff[9]);
	bt[2] = 30;

	// printf("testing1\n");
	at[0] = buff[10];
	at[1] = buff[12];
	at[2] = buff[14];

	// printf("testing2\n");
	pt[0] = buff[15];
	pt[1] = buff[17];
	pt[2] = buff[19];

	
	// for (i = 0; i < numOfProcesses; i++) {
	// 	printf("%d %d %d\n", bt[i], at[i], pt[i]);
	// }

	for (i = 0; i < numOfProcesses; i++) {
		dt_main[i].quantumTime = qt;
		dt_main[i].burstTime = bt[i];
		dt_main[i].arrivalTime = at[i];
		dt_main[i].priority = pt[i];
	}


	// dt_address = &dt;
	pthread_t tid1, tid2, tid3, tid4, tid5, tid6;
	
	/* The six threads each to represent one scheduling algorithm */

	/* First Come First Serve Scheduling Algorithm*/
	pthread_create(&tid1, NULL, fcfs,  NULL);
	
	/* Shortest Job First Preemptive Scheduling Algorithm */
	pthread_create(&tid2, NULL, sjfPreemptive, NULL);
	
	/* Shortest Job First Non-Preemptive Scheduling Algorithm */
	pthread_create(&tid3, NULL, sjfNon,  NULL);
	
	/* Round Robin Scheduling Algorithm */
	pthread_create(&tid4, NULL, roundRobin, NULL);
	
	/* Priority Non-Preemptive Scheduling Algorithm*/
	pthread_create(&tid5, NULL, priorityNon, NULL);
	
	/* Priority Preemptive Scheduling Algorithm */
	pthread_create(&tid6, NULL, priorityPre, NULL);

	

	/* Looping over each created thread to reap them */
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	pthread_join(tid5, NULL);
	pthread_join(tid6, NULL);



	close(fd);
	munmap(region, sizeof(region));
	/*free(temp);
	free(temp2);
	free(temp3);*/
	return 0;
}

