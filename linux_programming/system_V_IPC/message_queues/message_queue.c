#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <linux/ipc.h>
#include <linux/msg.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int open_queue(key_t keyval)
{
	int qid;
	return qid = msgget(keyval, IPC_CREAT | 0660);
}

int send_message(int qid, struct msgbuf *qbuf)
{
	int result, length = sizeof(struct msgbuf) - sizeof(long);
	return result = msgsnd(qid, qbuf, length, 0);
}

int read_message(int qid, long type, struct msgbuf *qbuf)
{
	int result, length;
	length = sizeof(struct msgbuf) - sizeof(long);
	result = msgrcv(qid, qbuf, length, type, 0);
	printf("Message: %s\n", qbuf->mtext);
	return result;
}

int remove_queue(int qid)
{
        return msgctl(qid, IPC_RMID, 0);
}

int main (int argc, char *argv[])
{
	int qid;
	key_t msgkey;
	char *message = "Towa e syobshtenieto";
	struct msgbuf *msg = (struct msgbuf *)malloc(sizeof(struct msgbuf) + strlen(message));
	struct msgbuf *rmsg = (struct msgbuf *)malloc(sizeof(struct msgbuf) + strlen(message));
	
	msgkey = ftok("/tmp/msgtool", 'm');
	
	if ((qid = open_queue(msgkey) == -1))
	{
		DEATH("open msg failed\n");
	}
	
	msg->mtype = 1;
	strcpy(msg->mtext, message);
	
	if (send_message(qid, msg) == -1)
	{
		DEATH("send msg failed\n");
	}
	
	sleep(10);
	printf("Time to read\n");
	
	if (read_message(qid, 1, msg) == -1)
	{
		DEATH("recv msg failed\n");
	}
	
	printf("Message queue will be removed in ten seconds\n");
	sleep(10);
	printf("Time to remove\n");
	if (remove_queue(qid) == -1)
	{
		DEATH("remove msg failed\n");
	}
	exit(0);
}
