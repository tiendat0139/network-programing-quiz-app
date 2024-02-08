#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <unistd.h>
#include "../Model/User.hpp"
#include "../../library/json.hpp"

class ClientManager {
public:
    static int client_sock;
    static json authUser;
    static void close_client_sock();
    static json responseStartRoom;
};

inline void ClientManager::close_client_sock()
{
    close(ClientManager::client_sock);
}

#endif // CLIENTMANAGER_H
