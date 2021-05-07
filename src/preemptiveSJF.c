/* This is the source code of the nonpreemtive Shortest Job First Scheduling */
#include "project.h"
#include "die_with_error.h"
void die_with_error(char *msg);

int main() {
	int burstTime[ASIZE] = {};
	int processes[ASIZE] = {};
	int waitingTime[ASIZE] = {};
	int turnAroundTime[ASIZE] = {};
	int arrivalTime[] = {};
	int tempArr[] = {};
	char buffer[MAXBUF];
	bzero(buffer, sizeof(buffer));
	int i, j, fd, numOfProcesses, position, tempVal, total=0;
	double waitingAvg, turnAroundAvg, end;
	double waitTime, turnAroundtime = 0;
	int k, l, closing_descriptor = 0;
	int time, count=0, smallest;
	char *region;
	char *temp;
	char *temp2;
	char *arrival;
	struct stat info;
	char buff[MAXBUF];
	bzero(buff, sizeof(buff));

	fd = open("preemptive.txt", O_RDONLY, 0);

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
	printf("Enter Details of %d processes\n", numOfProcesses);

	arrival = strcat(&buff[2], "");
	arrivalTime[0] = atoi(arrival);

	temp2 = strcat(&buff[4], &buff[5]);
	burstTime[0] = atoi(temp2);

        arrival = strcat(&buff[7], "");
        arrivalTime[1] = atoi(arrival);

        temp2 = strcat(&buff[9], &buff[10]);
        burstTime[1] = atoi(temp2);


        arrival = strcat(&buff[12], "");
        arrivalTime[2] = atoi(arrival);

        temp2 = strcat(&buff[14], &buff[15]);
        burstTime[2] = atoi(temp2);

	printf("\nEnter Arrival Time:	%d\n", arrivalTime[0]);
	printf("Enter Burst Time:	%d\n", burstTime[0]);

	printf("\nEnter Arrival Time:	%d\n", arrivalTime[1]);
	printf("Enter Burst Time:	%d\n", burstTime[1]);
	
	printf("\nEnter Arrival Time:	%d\n", arrivalTime[2]);
        printf("Enter Burst Time:	%d\n", burstTime[2]);
	
	burstTime[9] = 9999;

	for (time = 0; count != numOfProcesses; time++) {
	
		smallest = 9;
		for (i = 0; i < numOfProcesses; i++) {
			
			if (arrivalTime[i] <= time && burstTime[i] < burstTime[smallest] && burstTime[i] > 0)
				smallest = i;
			
		}
		burstTime[smallest]--;
		if (burstTime[smallest] == 0) {
			count++;
			end = time + 1;
			waitTime += end - arrivalTime[smallest];
			turnAroundtime += end - arrivalTime[smallest];
		}
	
	}

	waitingAvg = waitTime / numOfProcesses;
	turnAroundAvg = turnAroundtime / numOfProcesses;
	
	printf("\nAverage Waiting Time:		%lf\n", waitingAvg);
	printf("Average TurnAround Time:	%lf\n", turnAroundAvg);

	closing_descriptor = close(fd);
	if (closing_descriptor < 0)
		die_with_error("Error closing the file");

	munmap(region, sizeof(region));
		
	return 0;

}
