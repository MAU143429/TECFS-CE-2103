//
// Created by mau on 6/22/21.
//

#ifndef DISK_NODE_DISK_MANAGER_H
#define DISK_NODE_DISK_MANAGER_H
#include <iostream>
#include "../../../lib/DataStructures/SimplyList.h"
#include "Block.h"

using namespace std;

class Disk_Manager
{
public:

    static string Disk_Path;
    static bool B1,B2,B3,B4,B5,B6,B7,B8;

    Disk_Manager() {

        

    }

    static void InitDisk(string path){

        auto block1 = new Block;
        auto block2 = new Block;
        auto block3 = new Block;
        auto block4 = new Block;
        auto block5 = new Block;
        auto block6 = new Block;
        auto block7 = new Block;
        auto block8 = new Block;
        block1->InitBlock(1,path);
        block2->InitBlock(2,path);
        block3->InitBlock(3,path);
        block4->InitBlock(4,path);
        block5->InitBlock(5,path);
        block6->InitBlock(6,path);
        block7->InitBlock(7,path);
        block8->InitBlock(8,path);



    }
    static void Save_Info(string binary_code){





    }

    static void Select_Request(const string& jsonstring){
        auto response = new TypeMessage();
        string type = JSON_Management::GetJSONString("Request",jsonstring);

        if(type == "SAVE"){
            string save_msg = JSON_Management::GetJSONString("Binary_Script",jsonstring);
            Save_Info(save_msg);
            response->setClient("DISK");
            response->setSave("TRUE");
        }else{

            string meta = JSON_Management::GetJSONString("Filename",jsonstring);
            string numblock = Locate_Block(meta);
            string binary_code = Extract_BinaryCode(numblock);
            response->setClient("DISK");
            response->setBinaryCode(binary_code);
            response->setSave("FALSE");
            string result = JSON_Management::TypeMessageToJSON(response);
            Client::getInstance()->Send(result.c_str());
        }

        /**
         *
         *
         * ACA SE DEBE BEVOLVER UN MENSAJE AL SERVIDOR
         */

    }
    static string Locate_Block(string filename){
        for (int i = 1; i < 9; ++i) {
            /**
             * string name = List_Block.get(i).getMetadata().getName();
             * if(filename == name){
             *    return to_string(i);
             * }
             */
             return to_string(i);
        }


    }
    static string Extract_BinaryCode(string numblock){
        string binary_txt;
        if(numblock == "1"){
            //binary_txt = block1->Read();
            return binary_txt;
        }else if(numblock == "2"){
            //binary_txt = block2->Read();
            return binary_txt;
        }else if(numblock == "3"){
            //binary_txt = block3->Read();
            return binary_txt;
        }else if(numblock == "4"){
            //binary_txt = block4->Read();
            return binary_txt;
        }else if(numblock == "5"){
            //binary_txt = block5->Read();
            return binary_txt;
        }else if(numblock == "6"){
            //binary_txt = block6->Read();
            return binary_txt;
        }else if(numblock == "7"){
            //binary_txt = block7->Read();
            return binary_txt;
        }else{
            //binary_txt = block8->Read();
            return binary_txt;
        }


    }

};
#endif //DISK_NODE_DISK_MANAGER_H
