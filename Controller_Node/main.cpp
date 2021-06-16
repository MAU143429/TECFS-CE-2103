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
    newSMS->setMessage("SOY EL MENSAJE QUE QUIEREN ENVIAR");
    string prueba = JSON_Management::TypeMessageToJSON(newSMS);
    pair<string,SimplyLinkedList<Huffman_pair*>*> print;
    print = HuffmanCompression::buildHuffmanTree(prueba);
    auto message = new Huffman_Message();
    message->setCompress_Code(print.first);
    for (int i = 0; i < print.second->getLen(); ++i) {
        message->getHuffman_Table()->append(print.second->get(i));
    }
    string final_result;
    final_result = JSON_Management::HuffmanMessageToJSON(message);
    cout << "\n SOY EL MENSAJE YA LISTO" << final_result << endl;
}
int main() {

    thread runs(RunServer);
    thread main(mainv2);
    runs.join();
    main.join();

    return 0;
}
