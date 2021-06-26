//
// Created by mau on 6/26/21.
//

#ifndef TEC_FS_BINARYCONVERTER_H
#define TEC_FS_BINARYCONVERTER_H

#include <bits/stdc++.h>
using namespace std;


class BinaryConverter{

public:

    static string Binary_toString(string code){
        string result;
        stringstream sstream(code);
        string output;
        while(sstream.good())
        {
            bitset<8> bits;
            sstream >> bits;
            cout << "SOY BITS  ---> " << bits <<endl;
            char c = char(bits.to_ulong());
            output += c;
        }

        output.erase(prev(output.end()));
        cout << output;
        return output;

    }

    static string String_toBinary(string txt){

        string result;
        bitset<8> bits;
        for (std::size_t i = 0; i < txt.size(); ++i)
        {
            cout << bitset<8>(txt.c_str()[i]) << endl;
            bits = bitset<8>(txt.c_str()[i]);
            result += bits.to_string();
        }
        return result;
    }

};
#endif //TEC_FS_BINARYCONVERTER_H
