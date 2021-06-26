//
// Created by mau on 6/17/21.
//

#ifndef TEC_FS_APP_CONTROLLER_H
#define TEC_FS_APP_CONTROLLER_H
#include "../../../lib/DataStructures/SimplyList.h"
#include <fstream>
#include "string"
#include <iostream>
#include "../Algorithms/BinaryConverter.h"
using namespace std;

static SimplyLinkedList<string> *stringList = new SimplyLinkedList<string>();
static string DISK1_INFO;
static string DISK2_INFO;
static string PARITY_DISK_INFO;
class App_Controller{

public:

    static void Save_Info(const string& jsonString){
        string path = JSON_Management::GetJSONString("Path",jsonString);

        //Sacar lista de txt en carpeta y procesarlo uno a uno

    }

    static void  Extract_txt(const string& jsonString){

        string tag =  JSON_Management::GetJSONString("Keyword", jsonString);


        /**
         * solicita a los 3 discos la informacion de un archivo en especifico
         */
    }
    static SimplyLinkedList<string>* Search_Words(string keyword) {

        auto tempList = new SimplyLinkedList<string>();
        string empty = "";
        addToList();
        for (int i = 0; i < stringList->getLen(); ++i) {
            string stringCompare = stringList->get(i);
            if (stringCompare.find(keyword) != string::npos) {
                tempList->append(stringCompare);
            }else{
                tempList->append(empty);
            }
        }
        return tempList;
    }
    static string Read_File(string fullpath){

        ifstream newbook;
        newbook.open(fullpath);
        string line;
        string output;
        bool f1 = true;
        if (newbook.is_open())
        {
            while ( getline (newbook,line) )
            {
                if(f1){
                    output += (line);
                    f1= false;
                }else{
                    output += (":" + line);
                }
    static string File_Decompression(const string& jsonString){

            }
            newbook.close();
        }

        return output;

    }

    static string File_Compression(string text){
        string result;
        result = BinaryConverter::String_toBinary(text);
        return result;
    }
    static string File_Decompression(string text){
        string result;
        result = BinaryConverter::Binary_toString(text);
        return result;
    }

    static void Divide_files(string binary_code){
        int half = binary_code.size()/2;
        char d1,d2,p3;
        for (int i = 0; i < half; ++i) {
            d1 = binary_code[i];
            d2 = binary_code[i+1];
            if(d1 == '1' && d2 == '0' or d1 == '0' && d2 == '1'){
                p3 = '0';
            }else if(d1 == '1' && d2 == '1' or d1 == '0' && d2 == '0'){
                p3 = '1';
            }

            DISK1_INFO.push_back(d1);
            DISK2_INFO.push_back(d2);
            PARITY_DISK_INFO.push_back(p3);

        }
    }

    static string Build_files(string code1,string code2){
        char c1,c2;
        string result;
        for (int i = 0; i < code1.length(); ++i) {
            c1 = code1[i];
            c2 = code2[i];
            result += (c1+c2);
        }
        return result;

    }
};

#endif //TEC_FS_APP_CONTROLLER_H
