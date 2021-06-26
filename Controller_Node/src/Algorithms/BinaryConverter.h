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
            bitset<7> bits;
            sstream >> bits;
            cout << "SOY BITS" << bits <<endl;
            if(bits == 1000001){
                output += "_";
            }else{
                char c = char(bits.to_ulong());
                output += c;
            }

        }
        output.erase(prev(output.end()));
        cout << output;
        return output;

    }

    static string String_toBinary(string txt){

        int n = txt.length();
        string result;
        for (int i = 0; i <= n; i++)
        {
            // convert each char to
            // ASCII value
            int val = int(txt[i]);

            // Convert ASCII value to binary
            string bin = "";
            while (val > 0)
            {
                (val % 2)? bin.push_back('1') :
                bin.push_back('0');
                val /= 2;
            }
            reverse(bin.begin(), bin.end());

            cout << bin << " ";
            result = result+bin;
        }
        return result;

    }


};
#endif //TEC_FS_BINARYCONVERTER_H
