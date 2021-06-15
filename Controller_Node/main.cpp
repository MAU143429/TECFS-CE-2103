#include <iostream>
#include "src/Algorithms/HuffmanCompression.h"
#include "src/Objects/Huffman_Message.h"
#include "src/UtilJSON/JSON_Management.h"

using namespace std;
int main() {

    //Server::InitServer();
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

    return 0;
}
