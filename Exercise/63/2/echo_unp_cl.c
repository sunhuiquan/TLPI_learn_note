#include <sys/socket.h>
#include <arpa/inet.h>
#include <tlpi_hdr.h>

#define MAXBUF 1024

int main()
{
	int cfd, readn;
	struct sockaddr_in addr;
	char buf[MAXBUF];

	if ((cfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		errExit("socket");

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7);
	if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) == -1)
		errExit("inet_pton");

	for (int i = 0; i < 100; ++i)
	{
		if (sendto(cfd, "unp\n", 4, 0, (struct sockaddr *)&addr, sizeof(addr)) != 4)
			errExit("sendto");

		if ((readn = recv(cfd, buf, MAXBUF, 0)) != 4)
			errExit("recv");
		if (write(STDOUT_FILENO, buf, readn) != readn)
			errExit("write");
		sleep(1);
	}

	return 0;
}