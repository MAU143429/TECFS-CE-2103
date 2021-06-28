//
// Created by mau on 6/26/21.
//
#include "Server.h"
Server* Server::unique_instance{nullptr};
mutex Server::mutex_;
/**
 * @brief constructor for Server class.
 */
Server::Server() {}

/**
 * @brief destructor for Server class.
 */
Server::~Server() {}

/**
 * @brief singleton getter for Server class.
 * @return the unique instance for server.
 */
Server *Server::getInstance() {
    lock_guard<std::mutex> lock(mutex_);
    if (unique_instance == nullptr){unique_instance = new Server();}
    return unique_instance;
}
