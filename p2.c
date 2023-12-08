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
	char bufff[200];
	fd1 = open(DEV1, O_RDWR);
	fd2 = open(DEV2, O_RDWR);
	int con = open("/dev/pts/2", O_WRONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Error opening fd1 or fd2\n");
		return -1;
	}
	for (int i = 0; i < WRITE_SIZE; i++)
		write_buf[i] = (char)(FIRST_CH + i); // ABC ...
	write(con, "\n\n\n", sizeof("\n\n\n"));
//#define WR_MSG "P2: writing to dev1..."
//#define RE_MSG ".. P2: reading from dev0.."
	while (1)
	{
		//write(con, RE_MSG, sizeof(RE_MSG));
		int rs2 = read(fd1, read_buf, sizeof(char) * WRITE_SIZE);
		//write(con, WR_MSG, sizeof(WR_MSG));
		int rs1 = write(fd2, write_buf, sizeof(char) * WRITE_SIZE);
		if (rs1 == -1)
			perror("P2: write to fd2 failed");
		if (rs2 == -1)
			perror("P2: read from fd1 failed");
		int rs3 = write(STDOUT_FILENO, read_buf, sizeof(read_buf));
		int rs4 = write(STDOUT_FILENO, write_buf, sizeof(write_buf));
		if ((rs1 + rs2 + rs3 + rs4) < 0) {
			perror("P2: failed");
			return -1;
		}
		for (int i = 0; i < WRITE_SIZE; i++)
		{
			write_buf[i] = (write_buf[i] + WRITE_SIZE - FIRST_CH) % ENG_ALPH_C + FIRST_CH;
		}
		//sprintf(bufff, "P2: executing... write_buf[0]: %s", write_buf);
		//perror(bufff);
		sleep(1);
	}
	return 0;
}
