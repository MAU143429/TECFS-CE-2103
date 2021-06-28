#include <iostream>
#include <thread>
#include "src/Algorithms/HuffmanCompression.h"
#include "src/Objects/Huffman_Message.h"
#include "src/UtilJSON/JSON_Management.h"
#include "src/Socket/Server.h"
#include "src/Algorithms/BinaryConverter.h"

using namespace std;

void RunServer() {
    cout << "Server is running" << endl;
    Server::getInstance()->InitServer();
}

void mainv2(){

}
int main() {

    thread runs(RunServer);
    thread main(mainv2);
    runs.join();
    main.join();

    return 0;
}
