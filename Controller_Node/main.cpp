#include <iostream>
#include <thread>
#include "src/Algorithms/HuffmanCompression.h"
#include "src/Objects/Huffman_Message.h"
#include "src/UtilJSON/JSON_Management.h"
#include "src/Socket/Server.h"

using namespace std;

void RunServer() {
    cout << "Server is running" << endl;
    Server::InitServer();
}

void mainv2(){
    auto newSMS = new TypeMessage();
    newSMS->setMessage("SOY EL STRING DE PRUEBA DE PALABRA");
    string prueba = JSON_Management::TypeMessageToJSON(newSMS);
    pair<string,SimplyLinkedList<Huffman_pair*>*> print;
    print = HuffmanCompression::buildHuffmanTree(prueba);
    string mau = HuffmanCompression::Decode_Huffman(print.first,print.second);
    
}
int main() {

    thread runs(RunServer);
    thread main(mainv2);
    runs.join();
    main.join();

    return 0;
}
