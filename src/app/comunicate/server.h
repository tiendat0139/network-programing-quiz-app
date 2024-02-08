#ifndef __SERVER_H__
#define __SERVER_H__

#define BUFF_SIZE 65536

void logServer(int clientfd, const char *buff, bool flag);

int sendToClient(int client_fd, const char *buff);

int recvFromClient(int client_fd, char *buff);

#endif