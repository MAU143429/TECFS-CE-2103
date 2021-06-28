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

MetaData *metadata;
Book *book;
static bool inUse;

class Block
{
public:

    static string file_path;

    /**
     * @brief This method initialize a block in specific path of the system and create a book and metadata inside this path.
     * @param num_block is the number of block
     * @param path the route of the system to create the file
     */
    static void InitBlock(int num_block,string path){

        inUse = false;
        metadata = new MetaData();
        book = new Book();
        string file = (path +"block" + to_string(num_block)+".txt");
        book->setBook(file);
    }
    /**
     * @brief This method access to the book of the block and write inside it.
     * @param newtxt the text to write in book
     */
    static void Write(string newtxt){
        book->Write(newtxt);
    }

    /**
     * @brief This method access to the txt file and read the content in it
     * @return the content of the txt file
     */
    static string Read(){
        string result;
        result = book->Read();
        return result;
    }

    static string getMetadata(){
        metadata->getName();
    }

    static void setMetadata(string newdata){
        metadata->setName(newdata);
    }
    static bool getUse(){
        return inUse;
    }

    static void setUse(bool newdata){
        inUse = newdata;
    }

};


#endif //DISK_NODE_BLOCK_H