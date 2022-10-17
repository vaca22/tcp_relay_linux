#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Required by event.h. */
#include <sys/time.h>


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Required by event.h. */
#include <sys/time.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>


static struct event_base *evbase;

static struct timeval CLOCK_TV;

static struct timeval TIMER_TV = {1, 0};



static void udp_cb(const int sock, short int which, void *arg)
{
	struct sockaddr_in server_sin;
	socklen_t server_sz = sizeof(server_sin);
	char buf[4]={'a','b','c','d'};
	char buf2[4]={'a','b','c','d'};

		printf("fuck22333\n");

	/* Recv the data, store the address of the sender in server_sin */
	if (recvfrom(sock, &buf, sizeof(buf) - 1, 0, (struct sockaddr *) &server_sin, &server_sz) == -1) {
		return;
	}


printf("Accepted connection from %s    %d    \n", 
	    inet_ntoa(server_sin.sin_addr),server_sin.sin_port);
	// /* Copy the time into buf; note, endianess unspecified! */
	// memcpy(buf, &CLOCK_TV, sizeof(CLOCK_TV));

// server_sin.sin_port=7789;
//server_sin.sin_addr.s_addr=inet_addr("192.168.6.101");
server_sin.sin_port=24664;

	// /* Send the data back to the client */
	if (sendto(sock, buf2, 4, 0, (struct sockaddr *) &server_sin, server_sz) == -1 ) {
		perror("sendto()");
		return;
	}
}

int main(int argc, char **argv)
{
	int listen_fd;
	int ret, port, sock, fd[2];

	struct event timer_event, udp_event;
	struct sockaddr_in sin;
	 evbase = event_base_new();

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(1497);
	
	if (bind(sock, (struct sockaddr *) &sin, sizeof(sin))) {
	
		printf("fuck22\n");
	}


printf("fuck\n");

	
	/* Add the UDP event */
	event_assign(&udp_event, evbase,sock, EV_READ|EV_PERSIST, udp_cb, NULL);
	event_add(&udp_event, NULL);

	/* Enter the event loop; does not return. */
	event_base_dispatch(evbase);
	return 0;
}
