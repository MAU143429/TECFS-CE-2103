//
// Created by mau on 6/25/21.
//

#ifndef DISK_NODE_CLIENT_H
#define DISK_NODE_CLIENT_H
#include <iostream>
#include <string>
#include <mutex>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include "../../../lib/DataStructures/SimplyList.h"
#include "../Objects/Huffman_Message.h"
#include "../Algorithms/HuffmanCompression.h"
#include "../UtilJSON/JSON_Management.h"

using namespace std;



class Client {
protected:
    Client();

    ~Client();

private:
    static Client *unique_instance;
    static mutex mutex_;
    string server_response;

public:

    int clientSocket = socket(AF_INET,SOCK_STREAM,0);

    static Client *getInstance();

    int InitClient();

    void Send(const char *msg);

    string ReadString();

    string setResponse(string newresponse);

    void operator=(const Client &) = delete;

    Client(Client &other) = delete;


};

#endif //DISK_NODE_CLIENT_H
