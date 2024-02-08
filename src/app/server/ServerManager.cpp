#include "ServerManager.hpp"

#include <pthread.h>
#include <vector>
#include <unordered_map>

pthread_mutex_t ServerManager::mutex = PTHREAD_MUTEX_INITIALIZER;
std::vector<std::unordered_map<int, int>> ServerManager::client_auth;
std::vector<int> ServerManager::roomsActiveClock;