//
// Created by mau on 6/22/21.
//

#ifndef DISK_NODE_BOOK_H
#define DISK_NODE_BOOK_H
#include <iostream>
#include <fstream>
#include "../../../lib/DataStructures/SimplyList.h"
//#include "../Socket/Client.cpp"

using namespace std;

class Book
{
private:
    ofstream book;
    string path;
public:

    void setBook(const string &newbook) {
        path = newbook;
        book.open(newbook);
        book.close();

    }

    void Write(const string &newtxt){
        book.open(Book::path);
        book << newtxt;
        book.close();

    }
    string Read(){
        ifstream RFile(Book::path);
        string output;
        getline(RFile,output);
        return output;
    }



};
#endif //DISK_NODE_BOOK_H