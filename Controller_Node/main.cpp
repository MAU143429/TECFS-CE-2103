#include <iostream>
#include "src/Socket/Server.h"
#include "src/Algorithms/HuffmanCompression.h"
#include <unordered_map>
using namespace std;
int main() {
    pair<string,SimplyLinkedList<Huffman_pair*>*> print;
    //Server::InitServer();
    string prueba = "HOLA SOY EL STRING DE PRUEBA";
    print = HuffmanCompression::buildHuffmanTree(prueba);
    cout<< "SOY EL FIRST DEL MAIN " << print.first <<endl;
    cout<< "SOY EL SECOND DEL MAIN Y NO ME PRINTEO PORQUE SOY UNA TABLA " << endl;

    return 0;
}
