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
    //Server::InitServer();
}

void mainv2(){

    string codify = BinaryConverter::String_toBinary("HOLA CEROBOT");
    cout << "\n" << codify << endl;
    string decodify = BinaryConverter::Binary_toString(codify);
    cout << "\n" << decodify << endl;
}
int main() {

    thread runs(RunServer);
    thread main(mainv2);
    runs.join();
    main.join();

    return 0;
}
