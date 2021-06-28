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

    /**
     * @brief This method allow to create a new book un specific path of the system
     * @param newbook is the path
     */
    void setBook(const string &newbook) {
        path = newbook;
        book.open(newbook);
        book.close();

    }

    /**
     * @brief This method allow to write different things in a specif txt file
     * @param newtxt is the text that you want to save
     */
    void Write(const string &newtxt){
        book.open(Book::path);
        book << newtxt;
        book.close();

    }
    /**
     * @brief This method allow to read the content of txt files
     * @return the txt file content
     */
    string Read(){
        ifstream RFile(Book::path);
        string output;
        getline(RFile,output);
        return output;
    }



};
#endif //DISK_NODE_BOOK_H