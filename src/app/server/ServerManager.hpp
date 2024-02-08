#ifndef SERVERMANAGER_HPP
#define SERVERMANAGER_HPP

#include <pthread.h>
#include <vector>
#include <unordered_map>

class ServerManager {
public:
    static std::vector<std::unordered_map<int, int>> client_auth;
    static pthread_mutex_t mutex;
    static std::vector<int> roomsActiveClock;
};

#endif 
