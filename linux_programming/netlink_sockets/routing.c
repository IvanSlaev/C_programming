#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#define MAX_PAYLOAD 1024
#define DEATH(mess) { perror(mess); exit(errno); }

int read_event(int sock)
{
	int ret;
	struct nlmsghdr *nlh;
	
	nlh = malloc(NLMSG_SPACE(MAX_PAYLOAD));
	memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
	ret = recv(sock, (void *)nlh, NLMSG_SPACE(MAX_PAYLOAD), 0);
	printf("ima ne6to\n");
	switch (nlh->nlmsg_type)
	{
		case RTM_NEWROUTE:
			printf("NEWROUTE\n");
			break;
		case RTM_DELROUTE:
			printf("DELROUTE\n");
			break;
		case RTM_GETROUTE:
			printf("GETROUTE\n");
			break;
		default:
			printf("Unknown\n");
			break;
	}
}

int main (int argc, char *argv[])
{
	int nls = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	struct sockaddr_nl addr;
	
	memset((void *)&addr, 0, sizeof(addr));
	
	addr.nl_family = AF_NETLINK;
	addr.nl_pid = getpid();
	addr.nl_groups = RTMGRP_LINK | RTMGRP_IPV4_IFADDR;
	
	bind(nls, (struct sockaddr *)&addr, sizeof(addr));
	
	while (1)
	{
		read_event(nls);
	}
	
	return 0;
}
