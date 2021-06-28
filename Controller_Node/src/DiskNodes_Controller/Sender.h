//
// Created by mau on 6/27/21.
//

#ifndef TEC_FS_SENDER_H
#define TEC_FS_SENDER_H
#include "../Algorithms/HuffmanCompression.h"
#include "../UtilJSON/JSON_Management.h"
#include "../Objects/DiskMessage.h"
#include "../Objects/AppMessage.h"
#include "../Socket/Server.h"
#include "../DiskNodes_Controller/Disk_Controller.h"
#include "../App_Controller/App_Controller.h"

class Sender{

public:

/**
 *
 *


    static void Save_Call(string DISK1TXT,string DISK2TXT,string PDTXT,string filename){
        auto d1_save = new DiskMessage();
        auto d2_save = new DiskMessage();
        auto pd_save = new DiskMessage();
        d1_save->setBinary_Code(DISK1TXT);
        d2_save->setBinary_Code(DISK2TXT);
        pd_save->setBinary_Code(PDTXT);
        d1_save->setRequest("SAVE");
        d2_save->setRequest("SAVE");
        pd_save->setRequest("SAVE");
        d1_save->setFilename(filename);
        d2_save->setFilename(filename);
        pd_save->setFilename(filename);
        string d1sms = JSON_Management::DiskMessageToJSON(d1_save);
        string d2sms = JSON_Management::DiskMessageToJSON(d2_save);
        string pdsms = JSON_Management::DiskMessageToJSON(pd_save);
        Server::getInstance()->Send(Server::getInstance()->getDisk1_Client(),d1sms);
        Server::getInstance()->Send(Server::getInstance()->getDisk2_Client(),d2sms);
        Server::getInstance()->Send(Server::getInstance()->getParity_Client(),pdsms);

    }

    static void Open_Call(string keyword){

        auto d1_sms = new DiskMessage();
        auto d2_sms = new DiskMessage();
        d1_sms->setFilename(keyword);
        d1_sms->setRequest("OPEN");
        d2_sms->setFilename(keyword);
        d2_sms->setRequest("OPEN");
        string final_sms1 = JSON_Management::DiskMessageToJSON(d1_sms);
        string final_sms2 = JSON_Management::DiskMessageToJSON(d2_sms);
        Server::getInstance()->Send(Server::getInstance()->getDisk1_Client(),final_sms1);
        Server::getInstance()->Send(Server::getInstance()->getDisk2_Client(),final_sms2);

    }

    static void Confirmation_SMS(string sms){
        Server::getInstance()->Send(Server::getInstance()->getApp_Client(),sms);
    }

    static void Send_File(string text){

        auto filesms = new AppMessage();
        filesms->setText(text);
        string final_sms = JSON_Management::AppMessageToJSON(filesms);
        Server::getInstance()->Send(Server::getInstance()->getApp_Client(),final_sms);
    }
*/
};


#endif //TEC_FS_SENDER_H
