//
// Created by mau on 6/17/21.
//

#ifndef TEC_FS_DISK_CONTROLLER_H
#define TEC_FS_DISK_CONTROLLER_H


using namespace std;


class Disk_Controller{

public:

    static void Controller_Disk(const string& jsonString){

        string response = JSON_Management::GetJSONString("Save",jsonString);

        if(response  == "TRUE"){




        }


    }


};
#endif //TEC_FS_DISK_CONTROLLER_H
