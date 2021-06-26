//
// Created by mau on 6/17/21.
//

#ifndef TEC_FS_DISK_CONTROLLER_H
#define TEC_FS_DISK_CONTROLLER_H


using namespace std;


class Disk_Controller{

public:

    static void Controller_Disk(const string& jsonString){
        auto app_response = new AppMessage();
        string response = JSON_Management::GetJSONString("Save",jsonString);
        if(response  == "TRUE"){
            app_response->setStatus("TRUE");
            /**
             * ENVIAR MENSAJES DE CONFIRMACION DE GUARDADO
             */

        }else{
            string binarycode = JSON_Management::GetJSONString("Save",jsonString);

        }


    }

    static void Save_Call(string DISK1TXT,string DISK2TXT,string PDTXT){
        /**
         * ENVIA SMS A CADA DISCO CON US RESPECTIVO MENSAJE A GUARDAR
         */

    }

    static string Open_Call(){

        /**
         * PIDE LOS STRINGS DE CADA UNO DE LOS DISCOS, LOS UNE Y LOS DEVUELVE EN BINARIO
         */

    }


};
#endif //TEC_FS_DISK_CONTROLLER_H
