/* This is the source code of the non-preemtive Shortest Job First Scheduling */
#include "project.h"
#include "die_with_error.h"
void die_with_error(char *msg);

int main() {
	int burstTime[ASIZE] = {};
	int processes[ASIZE] = {};
	int waitingTime[ASIZE] = {};
	int turnAroundTime[ASIZE] = {};
	int i, j, fd, numOfProcesses;
	int k, l, closing_descriptor = 0;
	char *region;
	char *temp;
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
		
	printf("%s\n", buff);
	/* Extracting the number of processes from the file */
	temp = strtok(buff, "\n");
	numOfProcesses = atoi(temp);
	printf("%d\n", numOfProcesses);
	


	closing_descriptor = close(fd);
	if (closing_descriptor < 0)
		die_with_error("Error closing the file");

	munmap(region, sizeof(region));
		
	return 0;

}
