//
// Created by mau on 6/14/21.
//

#ifndef TEC_FS_HUFFMAN_PAIR_H
#define TEC_FS_HUFFMAN_PAIR_H
#include <iostream>
using namespace std;

class Huffman_pair
{
public:

    string code;
    char character;

    const string& getCode() const {
        return code;
    }

    void setCode(const string& newcode) {
        code = newcode;
    }

    const char& getCH() const {
        return character;
    }

    void setCH(const char& newch) {
        character = newch;
    }
};

#endif //TEC_FS_HUFFMAN_PAIR_H
