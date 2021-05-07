/* Implementation of the First Come First Serve Scheduling Algorithm */

#include "project.h"
#include "die_with_error.h"

void die_with_error(char *msg); /* Function prototype defined in die_with_error.h */


int main (void) {
	int burstTime[ASIZE] = {};
	int processes[ASIZE] = {};
	int waitingTime[ASIZE] = {};
	int turnAroundTime[ASIZE] = {};
	int total_waiting_time = 0;
	int total_turnAround_time = 0;
	int i, j, fd, numOfProcesses, position, tempVal, total=0;
	double waitingAvg, turnAroundAvg;
	int k, l, closing_descriptor = 0;
	char *region;
	char *temp;
	char *temp2;
	struct stat info;
	char buff[MAXBUF];
	bzero(buff, sizeof(buff));

	fd = open("file.txt", O_RDONLY, 0);

	if (fd < 0) 
		die_with_error("Error opening file");

	fstat(fd, &info);
	region = mmap(NULL, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	
	for (k = 0, l = 0; k < info.st_size; k++, l++)
		buff[l] = region[k];
		
	//printf("%s\n", buff);
	/* Extracting the number of processes from the file */
	temp = strtok(buff, "\n");
	numOfProcesses = atoi(temp);
	printf("Enter Total Number of Processes:	%d\n", numOfProcesses);
	
	temp2 = strcat(&buff[2], &buff[3]);
	burstTime[0] = atoi(temp2);

	temp2 = strcat(&buff[5], &buff[6]);
	burstTime[1] = atoi(temp2);

	temp2 = strcat(&buff[8], &buff[9]);
	burstTime[2] = atoi(temp2);

	for (int p = 0; p < numOfProcesses; p++) {
		printf("Enter Burst Time For Process[%d]:	%d\n", p+1, burstTime[p]);
		processes[p] = p+1;
	}

	/* First we find the waiting time */
	/* The waiting time of the first process is always zero */
	waitingTime[0] = 0; 	

	for (i = 0; i < numOfProcesses; i++)
		waitingTime[i] = burstTime[i-1] + waitingTime[i-1];

	/* Now we calculate the average turnAround time 
	 * TurnAround time is calculated by adding the burst time with the waitingtime 
	 * BurstTime + waitingTime;
	 */

	for (i = 0; i < numOfProcesses; i++)
		turnAroundTime[i] = burstTime[i] + waitingTime[i];

	/* Now we display each processes's information
	 * Burst time, waiting time and turnAround time 
	 */

	printf("\nProcesses	Burst time	Waiting time	TurnAround time\n\n");


	for (i = 0; i < numOfProcesses; i++) {

		total_waiting_time += waitingTime[i];
		total_turnAround_time += turnAroundTime[i];

		printf("Process	[%d] ", (i+1));
		printf("	   %d ", burstTime[i]);
		printf("		%d ", waitingTime[i]);
		printf("		     %d\n", turnAroundTime[i]);

	}

	waitingAvg = (double)total_waiting_time / (double)numOfProcesses;
	turnAroundAvg = (double)total_turnAround_time / (double)numOfProcesses;

	printf("\nAverage waiting time = %.6f\n", waitingAvg);
	printf("Average turn around time = %.6f\n", turnAroundAvg);

	return 0;

}
