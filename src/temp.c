// #include "project.h"
// #include "die_with_error.h"

// void die_with_error(char *msg); // Function Prototype

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// typedef struct data {
// 	int numOfProcesses;
// 	int burstTime[] = {};
// 	int arrivalTime[] = {};
// 	int processPriority[] = {};
// 	int quantumTime[] = {};
// }data;


// /* First Come First Serve Scheduling Algorithm */
// void *fcfs(void *arg) {

// 	/* The struct d2 should contain the burst and arrival time of all the processes */
// 	data *d2;
// 	d2 = (data*)*arg;

// 	int waitingTime[ASIZE] = {};
// 	int processes[ASIZE] = {};
// 	int waitingTime[SIZE] = {};
// 	int turnAroundTime{ASIZE} = {};
// 	int total_waiting_time = 0;
// 	int total_turnAround_time = 0;
// 	int position = 0, tempVal = 0, total = 0, closing_descriptor = 0;
// 	double waitingAvg = 0.0, turnAroundAvg = 0.0;


// 	for (int p = 0; p < dt.numOfProcesses; p++) {
// 		printf("Enter Burst Time For Process[%d]:	%d\n", p+1, dt.burstTime[p]);
// 		processes[p] = p+1;
// 	}

// 	/* First we find the waiting time */
// 	/* The waiting time of the first process is always zero */
// 	waitingTime[0] = 0;

// 	for (i = 0; i < dt.numOfProcesses; i++)
// 		waitingTime[i] = dt.burstTime[i-1] + waitingTime[i-1];

// 	/* Now we calculate the average turnAround time
// 	 * TurnAround time is calculated by adding the burst time with the waitingtime
// 	 * BurstTime + waitingTime;
// 	 */

// 	for (i = 0; i < dt.numOfProcesses; i++)
// 		turnAroundTime[i] = dt.burstTime[i] + waitingTime[i];

// 	/* Now we display each processes's information
// 	 * Burst time, waiting time and turnAround time
// 	 */

// 	printf("\nProcesses	Burst time	Waiting time	TurnAround time\n\n");


// 	for (i = 0; i < dt.numOfProcesses; i++) {

// 		total_waiting_time += waitingTime[i];
// 		total_turnAround_time += turnAroundTime[i];

// 		printf("Process	[%d] ", (i+1));
// 		printf("	   %d ", dt.burstTime[i]);
// 		printf("		%d ", waitingTime[i]);
// 		printf("		     %d\n", turnAroundTime[i]);

// 	}

// 	waitingAvg = (double)total_waiting_time / (double)numOfProcesses;
// 	turnAroundAvg = (double)total_turnAround_time / (double)numOfProcesses;

// 	printf("\nAverage waiting time = %.6f\n", waitingAvg);
// 	printf("Average turn around time = %.6f\n", turnAroundAvg);


// 	return NULL;
// }
// /* Shortest Job First Preemptive Scheduling Algorithm */
// void *sjfPreemptive(void *arg) {

// 	/* The struct d2 should contain the burst and arrival time of all the processes */
// 	data *d2;
// 	d2 = (data*)*arg;

// 	int waitingTime[ASIZE] = {};
// 	int processes[ASIZE] = {};
// 	int waitingTime[SIZE] = {};
// 	int turnAroundTime{ASIZE} = {};
// 	int tempArr[ASIZE] = {};
// 	int total_waiting_time = 0;
// 	int total_turnAround_time = 0;
// 	int position = 0, tempVal = 0, total = 0, closing_descriptor = 0;
// 	double waitingAvg = 0.0, turnAroundAvg = 0.0;
// 	int time = 0, count = 0;
// 	int i = 0, smallest = 0;

// 	dt.burstTime[9] = 9999;

// 	for (time = 0; count != dt.numOfProcesses; time++) {

// 		smallest = 9;
// 		for (i = 0; i < dt.numOfProcesses; i++) {

// 			if (dt.arrivalTime[i] <= time && dt.burstTime[i] < dt.burstTime[smallest] && dt.burstTime[i] > 0)
// 				smallest = i;

// 		}
// 		dt.burstTime[smallest]--;
// 		if (dt.burstTime[smallest] == 0) {
// 			count++;
// 			end = time + 1;
// 			waitTime += end - dt.arrivalTime[smallest];
// 			turnAroundtime += end - dt.arrivalTime[smallest];
// 		}

// 	}

// 	waitingAvg = waitTime / dt.numOfProcesses;
// 	turnAroundAvg = turnAroundtime / dt.numOfProcesses;

// 	printf("\nAverage Waiting Time:		%lf\n", waitingAvg);
// 	printf("Average TurnAround Time:	%lf\n", turnAroundAvg);

// 	closing_descriptor = close(fd);
// 	if (closing_descriptor < 0)
// 		die_with_error("Error closing the file");


// 	return NULL;
// }
// /* Shortest job first Non-Preemptive Scheduling Algorithm */
// void *sjfNon(void *arg) {

// 	/* The struct d2 should contain the burst and arrival time of all the processes */
// 	data *d2;
// 	d2 = (data*)*arg;

// 	int waitingTime[ASIZE] = {};
// 	int processes[ASIZE] = {};
// 	int waitingTime[SIZE] = {};
// 	int turnAroundTime{ASIZE} = {};
// 	int total_waiting_time = 0;
// 	int total_turnAround_time = 0;
// 	int position = 0, tempVal = 0, total = 0, closing_descriptor = 0, i = 0, j = 0;
// 	double waitingAvg = 0.0, turnAroundAvg = 0.0;


// 	for (int p = 0; p < dt.numOfProcesses; p++) {
// 		printf("Enter Burst Time For Process[%d]:	%d\n", p+1, dt.burstTime[p]);
// 		processes[p] = p+1;
// 	}
	
// 	/* Sorting algorithm of the burst time */
// 	/* The burst times are being sorted using the selection sort algorithm */
// 	for (i = 0; i < dt.numOfProcesses; i++) {
// 		position = i;
// 		for (j = i; j < dt.numOfProcesses; j++) {
// 			if (dt.burstTime[j] < dt.burstTime[position])
// 				position = j;
// 		}

// 		/* Swapping */
// 		tempVal = dt.burstTime[i];
// 		dt.burstTime[i] = dt.burstTime[position];
// 		dt.burstTime[position] = tempVal;

// 		tempVal = processes[i];
// 		processes[i] = processes[i];
// 		processes[position] = tempVal;
// 	}

// 	/* The waiting time of the first element is always zero */
// 	waitingTime[0] = 0;

// 	/* The waiting time is computed by adding the burst time with the waiting time */
// 	for (i = 1; i < dt.numOfProcesses; i++) {
// 		waitingTime[i] = 0;
// 		for (j = 0; j < i; j++)
// 			waitingTime[i] += dt.burstTime[j];
// 		/* The total variable contains the sun of all the waiting time */
// 		total += waitingTime[i];
// 	}
// 	/* 
// 	 * Now that we have the sum of the waiting time and the number of processes 
// 	 * We can compute the average of the waiting time
// 	 */
// 	waitingAvg = (double)total / dt.numOfProcesses;

// 	/* re-initialize the variable to be used again for the turn around time calculation */
// 	total = 0;
	
// 	printf("\nProcess ID		Burst Time		Waiting Time		TurnAround Time\n");
// 	for (i = 0; i < dt.numOfProcesses; i++) {
// 		turnAroundTime[i] = dt.burstTime[i] + waitingTime[i];
// 		total += turnAroundTime[i];
// 		printf("\nProcess[%d]		%d			%d			%d\n", processes[i], dt.burstTime[i], waitingTime[i], turnAroundTime[i]);
// 	}

// 	/* The turn around time is the additon of the burst time with the waiting time */
// 	turnAroundAvg = (double)total / dt.numOfProcesses;

// 	printf("\nAverage Waiting Time = %f\n", waitingAvg);
// 	printf("\nAverage TurnAround Time = %f\n", turnAroundAvg);
	

// 	closing_descriptor = close(fd);
// 	if (closing_descriptor < 0)
// 		die_with_error("Error closing the file");


// 	return NULL;
// }

// /* Round Robin Scheduling Algorithm */
// void *roundRobin(void *arg) {

// 	/* The struct d2 should contain the burst and arrival time of all the processes */
// 	data *d2;
// 	d2 = (data*)*arg;

// 	// Use for loop to enter the details of the process like Arrival time and the Burst Time
// 	for(i=0; i<NOP; i++) {
	
// 		printf("\n Enter the Arrival and Burst time of the Process[%d]\n", i+1);
// 		printf(" Arrival time is: \t");  // Accept arrival time
// 		scanf("%d", &at[i]);
// 		printf(" \nBurst time is: \t"); // Accept the Burst time
// 		scanf("%d", &bt[i]);
// 		temp[i] = bt[i]; // store the burst time in temp array
// 	}
	
// 	// Accept the Time qunat
// 	printf("Enter the Time Quantum for the process: \t");
// 	scanf("%d", &quant);
// 	// Display the process No, burst time, Turn Around Time and the waiting time
// 	printf("\n Process No \t\t Burst Time \t\t TAT \t\t Waiting Time ");
	
// 	for(sum=0, i = 0; y!=0;) {
	
// 		if(temp[i] <= quant && temp[i] > 0) { // define the condition 
// 	    		sum = sum + temp[i];
// 	    		temp[i] = 0;
// 	    		count=1;
//     		} else if(temp[i] > 0) {
			
//         		temp[i] = temp[i] - quant;
//         		sum = sum + quant;
//     		}
    		
// 		if(temp[i]==0 && count==1) {
			
//         		y--; //decrement the process no.
//         		printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", i+1, bt[i], sum-at[i], sum-at[i]-bt[i]);
//         		wt = wt+sum-at[i]-bt[i];
//        	 		tat = tat+sum-at[i];
//         		count =0;
//   	  	}
  	  
// 		if(i==NOP-1) {
//   	      		i=0;
//   	  	} else if(at[i+1]<=sum) {
//        	 		i++;
//     		  } else {
//         		i=0;
//  	   		}
// 	}
	
// 	// represents the average waiting time and Turn Around time
// 	avg_wt = wt * 1.0/NOP;
// 	avg_tat = tat * 1.0/NOP;
// 	printf("\n Average Turn Around Time: \t%f", avg_wt);
// 	printf("\n Average Waiting Time: \t%f", avg_tat);
// 	getch();  

// 	return NULL;
// }

// /* Priority Non-Preemptive Schedling Algorithm */
// void *priorityNon(void *arg) {

// 	/* The struct d2 should contain the burst and arrival time of all the processes */
// 	data *d2;
// 	d2 = (data*)*arg;

//     	int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,total=0,pos,temp,avg_wt,avg_tat;
//     	printf("Enter Total Number of Process:");
//     	scanf("%d",&n);
//  
//     	printf("\nEnter Burst Time and Priority\n");
//     	for(i=0;i<n;i++) {
	
// 		printf("\nP[%d]\n",i+1);
//         	printf("Burst Time:");
//         	scanf("%d",&bt[i]);
//         	printf("Priority:");
//         	scanf("%d",&pr[i]);
//         	p[i]=i+1;           //contains process number
//     	}
//  
//     	//sorting burst time, priority and process number in ascending order using selection sort
//     	for(i=0;i<n;i++) {
//         
// 		pos=i;
//         	for(j=i+1;j<n;j++) {
//             		if(pr[j]<pr[pos])
//                 		pos=j;
//         	}
//  
//         	temp=pr[i];
//         	pr[i]=pr[pos];
//         	pr[pos]=temp;
//  
//         	temp=bt[i];
//         	bt[i]=bt[pos];
//         	bt[pos]=temp;
//  	
//   	        temp=p[i];
//         	p[i]=p[pos];
//         	p[pos]=temp;
//     	}
//  
//     	wt[0]=0;	//waiting time for first process is zero
//  
//     	//calculate waiting time
//     	for(i=1;i<n;i++) {
//        		wt[i]=0;
//         	for(j=0;j<i;j++)
//             		wt[i]+=bt[j];
//  
//  	       	total+=wt[i];
//     	}
//  
//     	avg_wt=total/n;      //average waiting time
//     	total=0;
//  
//     	printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
//     	for(i=0;i<n;i++) {
//         
// 		tat[i]=bt[i]+wt[i];     //calculate turnaround time
//         	total+=tat[i];
//         	printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
//     	}
//  
//     	avg_tat=total/n;     //average turnaround time
//     	printf("\n\nAverage Waiting Time=%d",avg_wt);
//    	printf("\nAverage Turnaround Time=%d\n",avg_tat);

// 	return NULL;
// }

// /* Priority Preemptive Scheduling Algorithm */
// void *priorityPre(void *arg) {
	
// 	/* The struct d2 should contain the burst and arrival time of all the processes */
// 	data *d2;
// 	d2 = (data*)*arg;

// 	for(i=0;i<n;i++) {

// 	printf("Enter process %d id: ",i+1);

// 	scanf("%d",&id[i]);

// 	printf("Enter process %d burst time: ",i+1);

// 	scanf("%d",&bt[i]);

// 	printf("Enter process %d priority: ",i+1);

// 	scanf("%d",&p[i]);

// 	}

// 	for(i=0;i<n;i++) {

// 		for(j=i+1;j<n;j++) {

// 			if(p[i]>p[j]) {

// 				temp=p[i];
// 				p[i]=p[j];
// 				p[j]=temp;
// 				temp=bt[i];
// 				bt[i]=bt[j];
// 				bt[j]=temp;
// 				temp=id[i];
// 				id[i]=id[j];
// 				id[j]=temp;

// 			}

// 		}

// 		wt[i]=0;

// 	}

// 	for(i=0;i<n;i++) {

// 		for(j=0;j<i;j++) {

// 			wt[i]=wt[i]+bt[j];

// 		}

// 		tat[i]=wt[i]+bt[i];

// 	}

// 	float avwt=0,avtat=0;

// 	printf("Process\tP\tBT\tWT\tTAT\n");

// 	for(i=0;i<n;i++) {

// 		printf("%d\t%d\t%d\t%d\t%d\n",id[i],p[i],bt[i],wt[i],tat[i]);

// 		avwt=avwt+wt[i];

// 		avtat=avtat+tat[i];

// 	}

// 	avwt=avwt/n;

// 	avtat=avtat/n;

// 	printf("Average Waiting Time: %f\n",avwt);

// 	printf("\nAverage Turnaround Time: %f",avtat);


// 	return NULL;

// }


// int main (void) {

// 	/* Considering that the data is to be read from a text file and shared among all thread */
// 	data dt;
// 	data *dt_address;

// 	char *region = calloc(MAXBUF, sizeof(char));
// 	char buff[MAXBUF]; bzero(buff, sizeof(buff));
// 	struct stat info;
// 	int counter = 0;

// 	int fd = 0;
// 	fd = open("temp.txt", O_RDONLY, 0);
// 	if (fd < 0)
// 		die_with_error("Error opening the file");
	
// 	fstat(fd, &info);
// 	region = mmap(NULL, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

// 	for (i = 0, j = 0; i < info.st_size; i++, j++)
// 		buff[j] = region[i];
// 	/* buff should now contain the contents of the entire file */

// 	for (i = 0; i < info.st_size; i++)
// 		if (region[i] == '\n')
// 			counter++;

// 	dt.numOfProcesses = counter-1;



// 	dt_address = &dt;
// 	pthread_t tid1, tid2, tid3, tid4, tid5, tid6;
	
// 	/* The six threads each to represent one scheduling algorithm */

// 	/* First Come First Serve Scheduling Algorithm*/
// 	pthread_create(&tid1, NULL, fcfs, &dt_address);
	
// 	/* Shortest Job First Preemptive Scheduling Algorithm */
// 	pthread_create(&tid2, NULL, sjfPreemptive, &dt_address);
	
// 	/* Shortest Job First Non-Preemptive Scheduling Algorithm */
// 	pthread_create(&tid3, NULL, sjfNon, &dt_address);
	
// 	/* Round Robin Scheduling Algorithm */
// 	pthread_create(&tid4, NULL, roundRobin, &dt_address);
	
// 	/* Priority Non-Preemptive Scheduling Algorithm*/
// 	pthread_create(&tid5, NULL, priorityNon, &dt_address);
	
// 	/* Priority Preemptive Scheduling Algorithm */
// 	pthread_create(&tid6, NULL, priorityPre, &dt_address);

	

// 	/* Looping over each created thread to reap them */
// 	for (int i = 1; i <= 6; i++)
// 		pthread_join(tid[i], NULL);

// 	close(fd);
// 	munmap(region, sizeof(region));
// 	return 0;
// }
