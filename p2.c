#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define DEV1 "/dev/scull0"
#define DEV2 "/dev/scull1"
#define WRITE_SIZE 1
#define FIRST_CH 65
#define ENG_ALPH_C 26

int main()
{
	int fd1, fd2, writeResult;
	char write_buf[WRITE_SIZE], read_buf[WRITE_SIZE];
	fd1 = open(DEV1, O_RDWR);
	fd2 = open(DEV2, O_RDWR);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Error opening fd1 or fd2\n");
		return -1;
	}
	for (int i = 0; i < WRITE_SIZE; i++)
		write_buf[i] = (char)(FIRST_CH + i); // ABC ...
	while (1)
	{
		int rs1 = write(fd2, write_buf, sizeof(char) * WRITE_SIZE);
		int rs2 = read(fd1, read_buf, sizeof(char) * WRITE_SIZE);
		if (rs1 == -1) perror("P2: write to fd2 failed");
		if (rs2 == -1) perror("P2: read from fd1 failed");
		int rs3 = write(STDOUT_FILENO, read_buf, sizeof(read_buf));
		int rs4 = write(STDOUT_FILENO, write_buf, sizeof(write_buf));
		if ((rs3 + rs4) < 0) perror("P2: write to stdout failed");
		if ((rs1 + rs2 + rs3 + rs4) < 0) return -1;

		for (int i = 0; i < WRITE_SIZE; i++) {
			write_buf[i] = (write_buf[i] + WRITE_SIZE - FIRST_CH) % ENG_ALPH_C + FIRST_CH;
		}
		sleep(1);
	}
	return 0;
}
