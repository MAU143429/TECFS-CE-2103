//
// Created by mau on 6/22/21.
//

#ifndef DISK_NODE_DISK_MANAGER_H
#define DISK_NODE_DISK_MANAGER_H
#include <iostream>
#include "../../../lib/DataStructures/SimplyList.h"
#include "Block.h"


using namespace std;

static Block *block1;
static Block *block2;
static Block *block3;
static Block *block4;
static Block *block5;
static Block *block6;
static Block *block7;
static Block *block8;
SimplyLinkedList<Block*> *BlockList;


class Disk_Manager
{
public:

    static string Disk_Path;

    /**
     * @brief This method created 8 blocks in a specific path of the system
     * @param path the path of the directory
     */
    static void InitDisk(string path){

        block1 = new Block;
        block2 = new Block;
        block3 = new Block;
        block4 = new Block;
        block5 = new Block;
        block6 = new Block;
        block7 = new Block;
        block8 = new Block;
        block1->InitBlock(1,path);
        block2->InitBlock(2,path);
        block3->InitBlock(3,path);
        block4->InitBlock(4,path);
        block5->InitBlock(5,path);
        block6->InitBlock(6,path);
        block7->InitBlock(7,path);
        block8->InitBlock(8,path);
        BlockList = new SimplyLinkedList<Block*>();
        BlockList->append(block1);
        BlockList->append(block2);
        BlockList->append(block3);
        BlockList->append(block4);
        BlockList->append(block5);
        BlockList->append(block6);
        BlockList->append(block7);
        BlockList->append(block8);

    }
    /**
     * @brief This method save the binary content in specific book in a specific block of the raid
     * @param binary_code is a string that contain binary number of the file
     * @param name is the name of the txt file
     * @return number that confirm the operation save
     */
    static int Save_Info(string binary_code,string name){

        for (int i = 0; i < BlockList->getLen(); ++i){

            if(BlockList->get(i)->getUse() == false){
                BlockList->get(i)->setUse(true);
                BlockList->get(i)->Write(binary_code);
                BlockList->get(i)->setMetadata(name);
                return 1;
            }
        }
    }

    /**
     * @brief This method recieved the messages of the server and divide the different calls in differents methods.
     * @param jsonstring is the message of the server
     * @param client_type is the number of disk
     * @return is the answer of the request.
     */
    static string Select_Request(const string& jsonstring,string client_type){
        cout << "ENTRE AL SELECT REQUEST\n";
        auto huffmanMessage = new Huffman_Message();
        huffmanMessage = JSON_Management::DeserializetoHuffmanMessage(jsonstring);
        string msg = HuffmanCompression::Decode_Huffman(huffmanMessage->getCompress_Code(),huffmanMessage->getHuffman_Table());
        string type = JSON_Management::GetJSONString("Request",msg);
        auto response = new TypeMessage();

        if(type == "SAVE"){
            cout << "ENTRE AL SAVE\n";
            string save_msg = JSON_Management::GetJSONString("Binary_Script",msg);
            cout << "COGI EL MENSAJE\n";
            string name = JSON_Management::GetJSONString("Filename",msg);
            cout << "TENGO EL NOMBRE DEL ARCHIVO\n";
            int status = Save_Info(save_msg,name);
            if(status == 1) {
                cout << "GUARDE LA INFO\n";
            }
            response->setClient("DISK");
            response->setSave("TRUE");
            if(client_type == "1"){
                response->setSpecific("D1");
            }else if(client_type == "2"){
                response->setSpecific("D2");
            }else{
                response->setSpecific("P1");
            }
            string result = JSON_Management::TypeMessageToJSON(response);
            cout << "HICE LA RESPUESTA\n" << result << endl;
            return result;
        }else{
            string meta = JSON_Management::GetJSONString("Filename",msg);
            string numblock = Locate_Block(meta);
            string binary_code = Extract_BinaryCode(numblock);
            response->setClient("DISK");
            response->setBinaryCode(binary_code);
            response->setSave("FALSE");
            if(client_type == "1"){
                response->setSpecific("D1");
            }else if(client_type == "2"){
                response->setSpecific("D2");
            }else{
                response->setSpecific("P1");
            }
            string result = JSON_Management::TypeMessageToJSON(response);
            return result;
        }


    }
    /**
     * @brief This method locate a number of a block using the metadata.
     * @param filename the name of the file
     * @return the number of block
     */
    static string Locate_Block(string filename){
        for (int i = 1; i < 9; ++i) {
             string name = BlockList->get(i)->getMetadata();
             if(filename == name){
                return to_string(i);
             }
             return to_string(i);
        }
    }
    /**
     * @brief This method extract the context of a specific block
     * @param numblock is the number of block
     * @return the text inside the txt file
     */
    static string Extract_BinaryCode(string numblock){
        string binary_txt;
        if(numblock == "1"){
            binary_txt = block1->Read();
            return binary_txt;
        }else if(numblock == "2"){
            binary_txt = block2->Read();
            return binary_txt;
        }else if(numblock == "3"){
            binary_txt = block3->Read();
            return binary_txt;
        }else if(numblock == "4"){
            binary_txt = block4->Read();
            return binary_txt;
        }else if(numblock == "5"){
            binary_txt = block5->Read();
            return binary_txt;
        }else if(numblock == "6"){
            binary_txt = block6->Read();
            return binary_txt;
        }else if(numblock == "7"){
            binary_txt = block7->Read();
            return binary_txt;
        }else{
            binary_txt = block8->Read();
            return binary_txt;
        }


    }

};
#endif //DISK_NODE_DISK_MANAGER_H
