//
// Created by mau on 6/17/21.
//

#ifndef TEC_FS_APP_CONTROLLER_H
#define TEC_FS_APP_CONTROLLER_H
using namespace std;


class App_Controller{

public:

    static void Save_Info(const string& jsonString){
        string path = JSON_Management::GetJSONString("Path",jsonString);

        //Sacar lista de txt en carpeta y procesarlo uno a uno

    }

    static void  Extract_txt(const string& jsonString){


    }
    static SimplyLinkedList<string>* Search_Words(string keyword) {

        // kw = mate
        
        //[tomo1,  tomo2  ,ciencias7 ]
        //["","",ciencias7,"",""'','''',""]
    }

    static string File_Decompression(const string& jsonString){


    }

    static string File_Compression(const string& jsonString){


    }

};

#endif //TEC_FS_APP_CONTROLLER_H
