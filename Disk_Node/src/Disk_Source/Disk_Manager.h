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
        B1 = true;
        B2 = true;
        B3 = true;
        B4 = true;
        B5 = true;
        B6 = true;
        B7 = true;
        B8 = true;


    }
    static void Save_Info(const string& jsonstring){

        string save_sms = JSON_Management::GetJSONString("CODE",jsonstring);




    }

};
#endif //DISK_NODE_DISK_MANAGER_H
