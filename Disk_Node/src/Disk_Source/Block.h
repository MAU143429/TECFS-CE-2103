//
// Created by mau on 6/22/21.
//

#ifndef DISK_NODE_BLOCK_H
#define DISK_NODE_BLOCK_H

#include <iostream>
#include "../../../lib/DataStructures/SimplyList.h"
#include "Metadata.h"
#include "Book.h"
#include <fstream>

using namespace std;

class Block
{

public:
    static auto metadata = new MetaData();
    static auto book = new Book();
    static ofstream file;
    static string file_path;

    static void InitBlock(int num_block,string path){

        file_path =(path + to_string(num_block)+".txt");
        file.open(file_path);
        file << mFile.toStdString();
        file.close();

    }

    static void Write(string newtxt){

        file = newtxt;
    }

    static string Read(){
        ifstream RFile(file_path);
        string output;
        getline(RFile,output);
        return output;
    }

};


#endif //DISK_NODE_BLOCK_H