//
// Created by mau on 6/17/21.
//

#ifndef TEC_FS_APP_CONTROLLER_H
#define TEC_FS_APP_CONTROLLER_H

#include "../../../lib/DataStructures/SimplyList.h"

using namespace std;

static SimplyLinkedList<string> *stringList = new SimplyLinkedList<string>();
class App_Controller{

public:

    static void Save_Info(const string& jsonString){
        string path = JSON_Management::GetJSONString("Path",jsonString);

        //Sacar lista de txt en carpeta y procesarlo uno a uno

    }

    static void  Extract_txt(const string& jsonString){


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
    static void addToList(){
        stringList->append("tomo1");
        stringList->append("tomo2");
        stringList->append("Ciencias");
        stringList->append("Angosto se la come");
        stringList->append("tomo cinco");

    }

    static string File_Decompression(const string& jsonString){


    }

    static string File_Compression(const string& jsonString){


    }


};

#endif //TEC_FS_APP_CONTROLLER_H
