#include "project.h"
#include "die_with_error.h"
// #define numOfProcesses 600
// #define arr 2

// global variable to define the quantum time
int quantumTime = 0;
// global variable to store the number of lines read from the file
int numberOfLines = 0;
// global file pointer
FILE *filePtr = NULL;
// global job counter
int job_counter = 0;

void die_with_error(char *msg); // Function Prototype

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex5 = PTHREAD_MUTEX_INITIALIZER;



typedef struct data {
	int pid;
	int burstTime;
	int arrivalTime;
	int priority;	
} data;


data *dt_main;


void *safe_calloc(size_t size) {
	void *temp = calloc(numberOfLines, size);

	if (temp == NULL)
		die_with_error("Error Allocating Data");
	
	return temp;
}

void *fcfs(void *arg) {
	printf("\n\n*************************FCFS*************************\n\n");
	/* The struct d2 should contain the burst and arrival time of all the processes */
	data *dt = safe_calloc( (sizeof *dt) * numberOfLines);
	memcpy(dt, dt_main, (sizeof *dt) * numberOfLines);

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
	for (int p = 0; p < numberOfLines; p++) {
		printf("Enter Burst Time For Process[%d]:	%d\n", p+1, dt[p].burstTime);
		processes[p] = p+1;
	}

	/* First we find the waiting time */
	/* The waiting time of the first process is always zero */
	waitingTime[0] = 0;

	for (i = 0; i < numberOfLines; i++) {
		waitingTime[i] = dt[i].burstTime + waitingTime[i-1];
		pthread_mutex_lock(&mutex);
		job_counter++;
		printf("\n\nThe Job Counter has just been updated:\nJob Counter for Process[%d]: %d\n\n", i+1, job_counter);
		pthread_mutex_unlock(&mutex);
	}
	/* Now we calculate the average turnAround time
	 * TurnAround time is calculated by adding the burst time with the waitingtime
	 * BurstTime + waitingTime;
	 */

	for (i = 0; i < numberOfLines; i++)
		turnAroundTime[i] = dt[i].burstTime + waitingTime[i];

	/* Now we display each processes's information
	 * Burst time, waiting time and turnAround time
	 */

	printf("\nProcesses	Burst time	Waiting time	TurnAround time\n\n");


	for (i = 0; i < numberOfLines; i++) {

		total_waiting_time += waitingTime[i];
		total_turnAround_time += turnAroundTime[i];

		printf("Process	[%d] ", (i+1));
		printf("	   %d ", dt[i].burstTime);
		printf("		%d ", waitingTime[i]);
		printf("		     %d\n", turnAroundTime[i]);

	}

	waitingAvg = (double)total_waiting_time / numberOfLines;
	turnAroundAvg = (double)total_turnAround_time / numberOfLines;

	// printf("\nThe Job Counter for the FirstComeFirstServe : %d\n", job_counter);
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
	data *dt = safe_calloc( (sizeof *dt) * numberOfLines);
	memcpy(dt, dt_main, (sizeof *dt) * numberOfLines);

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

	dt[numberOfLines].burstTime = 9999;

	//pthread_mutex_lock(&mutex1);

	for (time = 0; count != numberOfLines; time++) {

		pthread_mutex_lock(&mutex);
		job_counter++;
		printf("\n\nThe Job Counter has just been updated:\nJob Counter for Process[%d]: %d\n\n", i+1, job_counter);
		pthread_mutex_unlock(&mutex);

		smallest = numberOfLines;
		for (i = 0; i < numberOfLines; i++) {

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

	waitingAvg = waitTime / numberOfLines;
	turnAroundAvg = total_turnAround_time / numberOfLines;

	// printf("\nThe Job Counter for the ShortestJobFirst-Preemptive: %d\n", job_counter);
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
	data *dt = safe_calloc( (sizeof *dt) * numberOfLines);
	memcpy(dt, dt_main, (sizeof *dt) * numberOfLines);

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
	
	for (int p = 0; p < numberOfLines; p++) {
		printf("Enter Burst Time For Process[%d]:	%d\n", p+1, dt[p].burstTime);
		processes[p] = p+1;
	}
	
	/* Sorting algorithm of the burst time */
	/* The burst times are being sorted using the selection sort algorithm */
	for (i = 0; i < numberOfLines; i++) {

		pthread_mutex_lock(&mutex);
		job_counter++;
		printf("\n\nThe Job Counter has just been updated:\nJob Counter for Process[%d]: %d\n\n", i+1, job_counter);
		pthread_mutex_unlock(&mutex);		

		position = i;
		for (j = i; j < numberOfLines; j++) {
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
	for (i = 1; i < numberOfLines; i++) {
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
	waitingAvg = (double)total / numberOfLines; 

	/* re-initialize the variable to be used again for the turn around time calculation */
	total = 0;
	
	printf("\nProcess ID		Burst Time		Waiting Time		TurnAround Time\n");
	for (i = 0; i < numberOfLines; i++) {
		turnAroundTime[i] = dt[i].burstTime + waitingTime[i];
		total += turnAroundTime[i];
		printf("\nProcess[%d]		%d			%d			%d\n", processes[i], dt[i].burstTime, waitingTime[i], turnAroundTime[i]);
	}

	/* The turn around time is the additon of the burst time with the waiting time */
	turnAroundAvg = (double)total / numberOfLines;
	// printf("\nThe Job Counter for the ShortestJobFirst-NonPreemptive: %d\n", job_counter);
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
	data *dt = safe_calloc( (sizeof *dt) * numberOfLines);
	memcpy(dt, dt_main, (sizeof *dt) * numberOfLines);

	int temp[ASIZE];
	int count = 0, sum = 0;
	int wt = 0, tat = 0;
	double avg_wt, avg_tat;
	int i = 0, y = numberOfLines;
	// Use for loop to enter the details of the process like Arrival time and the Burst Time
	//pthread_mutex_lock(&mutex3);

	for(i=0; i< numberOfLines; i++) {
	
		printf("\nEnter the Arrival and Burst time of the Process[%d]\n", i+1);
		printf("\nArrival time is: \t%d\n", dt[i].arrivalTime); 
		printf("\nBurst time is: \t%d\n", dt[i].burstTime);
		temp[i] = dt[i].burstTime; // store the burst time in temp array

		pthread_mutex_lock(&mutex);
		job_counter++;
		printf("\n\nThe Job Counter has just been updated:\nJob Counter for Process[%d]: %d\n\n", i+1, job_counter);
		pthread_mutex_unlock(&mutex);
	}
	
	// Accept the Time qunat
	printf("Enter the Time Quantum for the process: \t%d\n", quantumTime);
	// Display the process No, burst time, Turn Around Time and the waiting time
	printf("\nProcess No \t\tBurst Time \t\tTAT \t\tWaiting Time ");
	
	for(sum=0, i = 0; y!=0;) {
	
		if(temp[i] <= quantumTime && temp[i] > 0) { // define the condition 
	    		sum = sum + temp[i];
	    		temp[i] = 0;
	    		count = 1;
    		} else if(temp[i] > 0) {
			
        		temp[i] = temp[i] - quantumTime;
        		sum = sum + quantumTime;
    		}
    		
		if(temp[i]==0 && count==1) {
			
        		y--; //decrement the process no.
        		printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d\n", i+1, dt[i].burstTime, sum-dt[i].arrivalTime, sum-dt[i].arrivalTime-dt[i].burstTime);
        		wt = wt + sum - dt[i].arrivalTime - dt[i].burstTime;
       	 		tat = tat + sum - dt[i].arrivalTime;
        		count =0;
  	  	}
  	  
		if(i == numberOfLines-1) {
  	      		i=0;
  	  	} else if(dt[i+1].arrivalTime<=sum) {
       	 		i++;
    		  } else {
        		i=0;
 	   		}
	}
	
	// printf("\nThe Job Counter for the Round-Robin: %d\n", job_counter);
	// represents the average waiting time and Turn Around time
	avg_wt = (double)wt/numberOfLines;
	avg_tat = (double)tat/numberOfLines;
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

		data *dt = safe_calloc( (sizeof *dt) * numberOfLines);
		memcpy(dt, dt_main, (sizeof *dt) * numberOfLines);

		
		int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,total=0,pos,temp,avg_wt,avg_tat;
		//pthread_mutex_lock(&mutex4);

		printf("\nEnter Burst Time and Priority\n");
		for(i=0;i<numberOfLines;i++) {
	
			printf("\nP[%d]\n",i+1);
			printf("Burst Time: %d\n", dt[i].burstTime);
			printf("Priority: %d\n", dt[i].priority);
			p[i]=i+1; //contains process number
			
			pthread_mutex_lock(&mutex);
			job_counter++;
			printf("\n\nThe Job Counter has just been updated:\nJob Counter for Process[%d]: %d\n\n", i+1, job_counter);
			pthread_mutex_unlock(&mutex);
		}

		//sorting burst time, priority and process number in ascending order using selection sort
		for(i=0;i<numberOfLines;i++) {

			pos=i;
			for(j=i+1;j<numberOfLines;j++) {
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
		for(i=1;i<numberOfLines;i++) {
			wt[i]=0;
			for(j=0;j<i;j++)
					wt[i]+=dt[j].burstTime;

			total+=wt[i];
		}

		avg_wt=total/numberOfLines;//average waiting time
		total=0;

		printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
		for(i=0;i<numberOfLines;i++) {
		
			tat[i]=dt[i].burstTime+wt[i]; //calculate turnaround time
			total+=tat[i];
			printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d",p[i],dt[i].burstTime,wt[i],tat[i]);
		}

		// printf("\nThe Job Counter for the Priority-NonPreemptive: %d\n", job_counter);
		avg_tat=total/numberOfLines; //average turnaround time
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
	data *dt = safe_calloc( (sizeof *dt) * numberOfLines);
	memcpy(dt, dt_main, (sizeof *dt) * numberOfLines);
	int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,total=0,pos,temp= 0;
	double avg_wt,avg_tat;


	//pthread_mutex_lock(&mutex5);
	for(i=0;i<numberOfLines;i++) {

	printf("Enter process %d burst time: %d\n",i+1, dt[i].burstTime);

	printf("Enter process %d priority: %d\n",i+1, dt[i].priority);

	pthread_mutex_lock(&mutex);
	job_counter++;
	printf("\n\nThe Job Counter has just been updated:\nJob Counter for Process[%d]: %d\n\n", i+1, job_counter);
	pthread_mutex_unlock(&mutex);

	}

	for(i=0;i<numberOfLines;i++) {

		for(j=i+1;j<numberOfLines;j++) {

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

	for(i=0;i<numberOfLines;i++) {

		for(j=0;j<i;j++) {

			wt[i]=wt[i]+dt[j].burstTime;

		}

		tat[i]=wt[i]+dt[i].burstTime;

	}

	printf("\nProcess\tP\tBT\tWT\tTAT\n");

	for(i=0;i<numberOfLines;i++) {

		printf("\t%d\t%d\t%d\t%d\n",dt[i].priority,dt[i].burstTime,wt[i],tat[i]);

		avg_wt=avg_wt+wt[i];

		avg_tat=avg_tat+tat[i];

	}

	avg_wt=avg_wt/numberOfLines;

	avg_tat=avg_tat/numberOfLines;

	// printf("\nThe Job Counter for the Priority-Preemptive: %d\n", job_counter);

	printf("Average Waiting Time: %f\n",avg_wt);

	printf("\nAverage Turnaround Time: %f",avg_tat);

	//pthread_mutex_unlock(&mutex5);
	free(dt);
	return NULL;	

}



int main (void) {
		/* Considering that the data is to be read from a text file and shared among all thread */

	char *region = calloc(MAXBUF, sizeof(char));
	char buffer[MAXBUF];
	memset(buffer, 0, MAXBUF);
	

	int bt[ASIZE] = {};
	int at[ASIZE] = {};
	int pt[ASIZE] = {};
	int qt = 0;

	// struct stat info;
	int i = 0, j = 0;

	// int fd = 0;
	// fd = open("proj.txt", O_RDONLY, 0);
	// if (fd < 0)
	// 	die_with_error("Error opening the file");
	
	// fstat(fd, &info);
	// printf("The size of the file is: %ld\n", info.st_size);
	// region = mmap(NULL, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);


	filePtr = fopen("data_100.txt", "r");

	fgets(buffer, MAXBUF - 1, filePtr);
	sscanf(buffer, "%d", &quantumTime);


	while ( fgets(buffer, MAXBUF - 1, filePtr) != NULL) {
		memset(buffer, 0, MAXBUF - 1);
		numberOfLines++;
	}

	printf("Number Of Processes: %d\n", numberOfLines);
	printf("Quantum time: %d\n", quantumTime);

	rewind(filePtr);
	fgets(buffer, MAXBUF - 1, filePtr);

	dt_main = safe_calloc( (sizeof *dt_main) * numberOfLines);

	for (int i = 0; i < numberOfLines; i++) {
		memset(buffer, 0, MAXBUF);

		dt_main[i].pid = (i + 1);

		fgets(buffer, MAXBUF - 1, filePtr);

		sscanf(buffer, "%d %d %d", &dt_main[i].burstTime, &dt_main[i].arrivalTime, &dt_main[i].priority);

		
	}

	// printf("****************Printing the struct********************\n");
	// for (i = 0; i < numberOfLines; i++) {
	// 	printf("%d %d %d\n", dt_main[i].burstTime, dt_main[i].arrivalTime, dt_main[i].priority);
	// }


	pthread_mutex_init(&mutex, NULL);
	// pthread_mutex_init(&mutex1);

	// dt_address = &dt;
	pthread_t tid1, tid2, tid3, tid4, tid5, tid6;
	
	/* The six threads each to represent one scheduling algorithm */

	/* First Come First Serve Scheduling Algorithm*/
	//pthread_mutex_lock(&mutex);
	pthread_create(&tid1, NULL, fcfs,  NULL);	
	//pthread_mutex_unlock(&mutex);

	/* Shortest Job First Preemptive Scheduling Algorithm */
	//pthread_mutex_lock(&mutex1);
	pthread_create(&tid2, NULL, sjfPreemptive, NULL);
	//pthread_mutex_unlock(&mutex1);
	
	/* Shortest Job First Non-Preemptive Scheduling Algorithm */
	//pthread_mutex_lock(&mutex2);
	pthread_create(&tid3, NULL, sjfNon,  NULL);
	//pthread_mutex_unlock(&mutex2);

	/* Round Robin Scheduling Algorithm */
	//pthread_mutex_lock(&mutex3);
	pthread_create(&tid4, NULL, roundRobin, NULL);
	//pthread_mutex_unlock(&mutex3);

	/* Priority Non-Preemptive Scheduling Algorithm*/
	//pthread_mutex_lock(&mutex4);
	pthread_create(&tid5, NULL, priorityNon, NULL);
	//pthread_mutex_unlock(&mutex4);

	/* Priority Preemptive Scheduling Algorithm */
	//pthread_mutex_lock(&mutex5);
	pthread_create(&tid6, NULL, priorityPre, NULL);
	//pthread_mutex_unlock(&mutex5);
	


	/* Looping over each created thread to reap them */
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	pthread_join(tid5, NULL);
	pthread_join(tid6, NULL);


	pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex1);
	fclose(filePtr);
	// munmap(region, sizeof(region));
	/*free(temp);
	free(temp2);
	free(temp3);*/
	return 0;
}

