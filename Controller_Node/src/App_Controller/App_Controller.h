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
#include "../UtilJSON/JSON_Management.h"
#include <dirent.h>


using namespace std;


static bool SAVE_FILES;
static bool OPEN_FILES;
static bool SEND_FILES;

static SimplyLinkedList<string> *stringList = new SimplyLinkedList<string>();
static string DISK1_INFO;
static string DISK2_INFO;
static string PARITY_DISK_INFO;
class App_Controller{

public:

    static void Save_Info(const string& jsonString){

        const char *path = JSON_Management::GetJSONString("Path", jsonString).c_str();
        string dirpath = JSON_Management::GetJSONString("Path", jsonString);

        auto filesList = new SimplyLinkedList<string>();
        DIR *dir;
        struct dirent *file;
        if ((dir = opendir(path)) != NULL) {
            while ((file = readdir(dir)) != NULL) {
                if ( !strcmp( file->d_name, "."   )) continue;
                if ( !strcmp( file->d_name, ".."  )) continue;
                filesList->append(file->d_name);
            }
            closedir (dir);
        } else {
            cout<<"No se pudo abrir el directorio\n";
        }
        for (int i = 0; i < filesList->getLen(); ++i) {

            size_t lastindex = filesList->get(i).find_last_of(".");
            stringList->append(filesList->get(i).substr(0, lastindex));
            cout << filesList->get(i) << "\n";
            cout << stringList->get(i) << "\n";
        }

        for (int i = 0; i < filesList->getLen(); ++i) {
            string txt_info = Read_File((dirpath + "/" + filesList->get(i)));
            string filename = stringList->get(i);
            string txt_binary = File_Compression(txt_info);
            Divide_files(txt_binary);
            SAVE_FILES = true;
            //Sender::Save_Call(DISK1_INFO,DISK2_INFO,PARITY_DISK_INFO,filename);
        }

    }

    static void  Extract_txt(const string& jsonString){

        string tag =  JSON_Management::GetJSONString("Filename", jsonString);
        OPEN_FILES = true;
        //Sender::Open_Call(tag);
        string binary_code = Build_files(DISK1_INFO,DISK2_INFO);
        string text  = File_Decompression(binary_code);
        SEND_FILES = true;
        //Sender::Send_File(text);
    }

    static SimplyLinkedList<string>* Search_Words(string keyword) {

        auto tempList = new SimplyLinkedList<string>();
        string empty = "";
        for (int i = 0; i < stringList->getLen(); ++i) {
            string stringCompare = stringList->get(i);
            if (stringCompare.find(keyword) != string::npos) {
                tempList->append(stringCompare);
                cout << "\nSOY LA COINCIDENCIA: " << stringCompare << endl;
            }else{
                cout << "\nNO HAY COINCIDENCIA: " <<  endl;
                tempList->append(empty);
            }
        }
        while (tempList->getLen()!= 8){
            tempList->append(empty);
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
        char d1,d2,p3;
        for (int i = 0; i < binary_code.size(); i = i+2) {
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
        string merge;
        for (int i = 0; i < code1.length(); ++i) {
            c1 = code1[i];
            c2 = code2[i];
            merge.push_back(c1);
            merge.push_back(c2);
            result += merge;
            merge.clear();

            cout << "SOY EL C1" << c1 << endl;
            cout << "SOY EL C2" << c2 << endl;
            cout << "SOY EL MERGE" << merge << endl;
            cout << "SOY EL Result" << result << endl;
        }
        return result;

    }

    static string getDisk1_Info(){
        return DISK1_INFO;
    }
    static string getDisk2_Info(){
        return DISK2_INFO;

    }static string getParityD_Info(){
        return PARITY_DISK_INFO;
    }
    static void setDisk1_Info(string info){
        DISK1_INFO = info;
    }
    static void setDisk2_Info(string info){
        DISK2_INFO = info;

    }static void setParityD_Info(string info){
        PARITY_DISK_INFO = info;
    }

    static SimplyLinkedList<string> getStringList(){
        return *stringList;
    }
    static void setStringList(string in){
        stringList->append(in);
    }


};

#endif //TEC_FS_APP_CONTROLLER_H
