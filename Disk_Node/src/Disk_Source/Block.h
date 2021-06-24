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
#include <experimental/filesystem>

using namespace std;


class Block
{

public:

    static string file_path;



    static void InitBlock(int num_block,string path){

        auto metadata = new MetaData();
        auto book = new Book();
        string file = (path +"block" + to_string(num_block)+".txt");
        book->setBook(file);



    }

    static void Write(string newtxt){
        //book->Write(newtxt);
    }

    static string Read(string newtxt){
        string result;
        //result = book->Read();
        return result;
    }


};


#endif //DISK_NODE_BLOCK_H