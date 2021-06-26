//
// Created by mau on 6/17/21.
//

#ifndef TEC_FS_APP_CONTROLLER_H
#define TEC_FS_APP_CONTROLLER_H
using namespace std;


class App_Controller{

public:

    static string Controller_App(const string& jsonString){
    string app_sms = JSON_Management::GetJSONString("App",jsonString);


    if(app_sms == "CEROBOT"){

        string path = JSON_Management::GetJSONString("Path",jsonString);



    }else{

    };



    }


};




#endif //TEC_FS_APP_CONTROLLER_H
