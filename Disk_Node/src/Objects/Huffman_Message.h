//
// Created by mau on 6/14/21.
//

#ifndef DISK_NODE_HUFFMAN_MESSAGE_H
#define DISK_NODE_HUFFMAN_MESSAGE_H
#include <string>
#include"../Objects/Huffman_pair.h"
using namespace std;


class Huffman_Message
{
private:
    SimplyLinkedList<Huffman_pair*> *huffman_table = new SimplyLinkedList<Huffman_pair*>();
    string compress_code;
public:

    const string& getCompress_Code() const {
        return compress_code;
    }

    void setCompress_Code(const string& newcode) {
        compress_code = newcode;
    }

    SimplyLinkedList<Huffman_pair*>* getHuffman_Table() {
        return huffman_table;
    }

};
#endif //DISK_NODE_HUFFMAN_MESSAGE_H
