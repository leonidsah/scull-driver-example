#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define DEV1 "/dev/scull0"
#define DEV2 "/dev/scull1"
#define WRITE_SIZE 1
#define BUFF_SIZE WRITE_SIZE + 1

int main()
{
	FILE *fs1, *fs2;
	fs1 = popen("./p1.o", "r");
	fs2 = popen("./p2.o", "r");
	int fd1, fd2;
	char dev1_read[BUFF_SIZE], dev2_read[BUFF_SIZE],
		P1_read[BUFF_SIZE], P1_write[BUFF_SIZE],
		P2_read[BUFF_SIZE], P2_write[BUFF_SIZE];
	dev1_read[BUFF_SIZE-1] = '\0';
	dev2_read[BUFF_SIZE-1] = '\0';
	P1_read[BUFF_SIZE-1] = '\0';
	P1_write[BUFF_SIZE-1] = '\0';
	P2_read[BUFF_SIZE-1] = '\0';
	P2_write[BUFF_SIZE-1] = '\0';
	if (errno != 0)
		perror("popen fs1 / fs2 error");
	fd1 = open(DEV1, O_RDWR);
	fd2 = open(DEV2, O_RDWR);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Error opening fd1 or fd2\n");
		return -1;
	}
	printf(" P1_w   ║ P2_r   ║ P2_w   ║ P1_r   ║ P3_r (dev1,dev2)\n");
	printf("════════╬════════╬════════╬════════╬═════════════════\n");
	while (1)
	{
		int r1, r2;
		r1 = read(fd1, dev1_read, sizeof(char) * WRITE_SIZE);
		r2 = read(fd2, dev2_read, sizeof(char) * WRITE_SIZE);
		fread(P1_read, sizeof(char), WRITE_SIZE, fs1);
		fread(P1_write, sizeof(char), WRITE_SIZE, fs1);
		fread(P2_read, sizeof(char), WRITE_SIZE, fs2);
		fread(P2_write, sizeof(char), WRITE_SIZE, fs2);
		if (ferror(fs1) || ferror(fs2) || r1 == -1 || r2 == -1)
		{
			perror("Error reading the data");
			return 0;
		}
		printf("  %2s    ║   %2s   ║   %2s   ║   %2s   ║  %2s,%2s\n", P1_write, P2_read, P1_read, P2_write, dev1_read, dev2_read);
		sleep(1);
	}
	pclose(fs1);
	pclose(fs2);
	return 0;
}
