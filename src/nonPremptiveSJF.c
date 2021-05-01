/* This is the source code of the non-preemtive Shortest Job First Scheduling */
#include "project.h"
#include "die_with_error.h"
void die_with_error(char *msg);

int main() {
	int burstTime[ASIZE] = {};
	int processes[ASIZE] = {};
	int waitingTime[ASIZE] = {};
	int turnAroundTime[ASIZE] = {};
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
	
	/* Sorting algorithm of the burst time */
	/* The burst times are being sorted using the selection sort algorithm */
	for (i = 0; i < numOfProcesses; i++) {
		position = i;
		for (j = i; j < numOfProcesses; j++) {
			if (burstTime[j] < burstTime[position])
				position = j;
		}

		/* Swapping */
		tempVal = burstTime[i];
		burstTime[i] = burstTime[position];
		burstTime[position] = tempVal;

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
			waitingTime[i] += burstTime[j];
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
		turnAroundTime[i] = burstTime[i] + waitingTime[i];
		total += turnAroundTime[i];
		printf("\nProcess[%d]		%d			%d			%d\n", processes[i], burstTime[i], waitingTime[i], turnAroundTime[i]);
	}

	/* The turn around time is the additon of the burst time with the waiting time */
	turnAroundAvg = (double)total / numOfProcesses;

	printf("\nAverage Waiting Time = %f\n", waitingAvg);
	printf("\nAverage TurnAround Time = %f\n", turnAroundAvg);
	

	closing_descriptor = close(fd);
	if (closing_descriptor < 0)
		die_with_error("Error closing the file");

	munmap(region, sizeof(region));
		
	return 0;

}
