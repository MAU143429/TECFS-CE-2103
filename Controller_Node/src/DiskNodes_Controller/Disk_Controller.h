//
// Created by mau on 6/17/21.
//

#ifndef TEC_FS_DISK_CONTROLLER_H
#define TEC_FS_DISK_CONTROLLER_H

#include "../Objects/AppMessage.h"

using namespace std;

class Disk_Controller{

public:

    static void Controller_Disk(const string& jsonString,int client){
        auto app_response = new AppMessage();
        string response = JSON_Management::GetJSONString("Save",jsonString);

        if(response  == "TRUE"){


        }else{
            string binarycode = JSON_Management::GetJSONString("Binary",jsonString);
            if(client == 1){
                App_Controller::getDisk1_Info() = binarycode;
            }else if(client == 2){
                App_Controller::getDisk2_Info() = binarycode;
            }else{
                App_Controller::getParityD_Info() = binarycode;
            }
        }
    }


};
#endif //TEC_FS_DISK_CONTROLLER_H
