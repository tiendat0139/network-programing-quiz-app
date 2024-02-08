#ifndef __CLIENT_H__
#define __CLIENT_H__

#define BUFF_SIZE 65536

void logClient(const char *buff, bool flag);

int sendToServer(const char *buff);

int recvFromServer(char *buff);

#endif