//
// Created by mau on 6/14/21.
//
#ifndef TEC_FS_SERVER_H
#define TEC_FS_SERVER_H
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include <arpa/inet.h>
#include "../App_Controller/App_Controller.h"
#include "../DiskNodes_Controller/Disk_Controller.h"
#include "../UtilJSON/JSON_Management.h"
#include "../Algorithms/HuffmanCompression.h"


#define TRUE 1

using namespace std;
static int Disk1_Client;
static int Disk2_Client;
static int Parity_Disk_Client;
static int App_Client;

class Server{

protected:
    Server();
    ~Server();
private:
    static Server* unique_instance;
    static mutex mutex_;
public:

    static Server* getInstance();
    /**
     * @brief Method that doesn't let the server instance be cloneable.
     */
    void operator=(const Server &) = delete;

    /**
     * @brief Method that doesn't let the server be assignable.
     * @param other
     */
    Server(Server &other) = delete;


    [[noreturn]] void InitServer()
    {
        int clientSocket[30];
        int PORT;
        int max_sd;
        int max_clients = 30;
        int sd;
        int activity;
        int newSocket;
        int valread;
        int addrlen;
        int i;
        int opt = TRUE;

        fd_set readfds;
        char buffer[8192];
        const char *message = "YOU HAVE CONNECT TO SERVER! YOU CAN SEND AND RECIEVE MESSAGES NOW! \n";

        cout << "[-->] Please enter the port number for server to select!" <<  endl;
        cin >> PORT;

        for (int i = 0; i < max_clients; ++i) {
            clientSocket[i] = 0;
        }

        int serverSocket = socket(AF_INET,SOCK_STREAM,0);

        if(serverSocket == -1){
            cerr<<"Could not create a socket! " << endl;

        }
        if(setsockopt(serverSocket,SOL_SOCKET,SO_REUSEADDR,(char *)&opt,sizeof(opt)) < 0){

            cerr<< "setsockopt" << endl;
            exit(EXIT_FAILURE);
        }
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        inet_pton(AF_INET, "0.0.0.0",&addr.sin_addr);

        if(bind(serverSocket,(sockaddr*)&addr,sizeof (addr)) < 0){
            cerr << "bind failed" << endl;
            exit(EXIT_FAILURE);
        }
        if(listen(serverSocket,3) == 0){
            cout<<"[+] Server is ready for clients to connect on port number "<< PORT <<endl;
        }

        addrlen = sizeof(addr);

        while(TRUE){
            FD_ZERO(&readfds);

            FD_SET(serverSocket, &readfds);
            max_sd = serverSocket;

            for (int i = 0; i < max_clients; ++i) {
                sd=clientSocket[i];
                if(sd > 0)
                    FD_SET(sd,&readfds);
                if(sd > max_sd)
                    max_sd = sd;
            }

            activity = select(max_sd+1,&readfds,NULL,NULL,NULL);
            if((activity < 0) && (errno != EINTR)){
                cout << "SELECT ERROR" << endl;
            }

            if(FD_ISSET(serverSocket,&readfds)){
                if((newSocket = accept(serverSocket,(struct sockaddr*)&addr,(socklen_t*)&addrlen)) < 0){
                    cerr << "ACCEPT" <<endl;
                }
                cout<<"New connection , socket fd: " << newSocket <<" ip is "<< inet_ntoa(addr.sin_addr) <<" port "<<ntohs(addr.sin_port)<<endl;

                if(send(newSocket,message,strlen(message),0) != strlen(message)){
                    cerr << "SEND ERROR";
                }
                for (int i = 0; i < max_clients; ++i) {
                    if(clientSocket[i] == 0){
                        clientSocket[i] = newSocket;
                        break;;
                    }
                }

            }

            for (int i = 0; i < max_clients; ++i) {
                sd = clientSocket[i];
                if(FD_ISSET(sd,&readfds)){

                    memset(buffer,0,8192);
                    int bytesReceived = recv(sd,buffer,8192,0);
                    if(bytesReceived == -1){

                        cerr << "Error in recv(). Quitting"<<endl;
                        break;
                    }
                    if(bytesReceived == 0){
                        close(sd);
                        clientSocket[i] = 0;
                        cout<<"Client Disconnected"<<endl;
                        break;

                    }else{
                        if(bytesReceived > 0){
                            cout<< "Client["<< i << "]:" << string(buffer,0,bytesReceived) << endl;
                            string message = string(buffer,0,bytesReceived);
                            auto huffmanMessage = new Huffman_Message();
                            huffmanMessage = JSON_Management::DeserializetoHuffmanMessage(message);
                            string msg = HuffmanCompression::Decode_Huffman(huffmanMessage->getCompress_Code(),huffmanMessage->getHuffman_Table());
                            string first = JSON_Management::GetJSONString("First_Time", msg);
                            string type1  = JSON_Management::GetJSONString("Client_Type", msg);
                            string type2 =  JSON_Management::GetJSONString("Specific_Type", msg);
                            if(first == "TRUE"){
                                Identify_Client(type1,type2,i);
                            }else{
                                Identify_Controller(type1,type2,msg);
                            }

                        }

                    }

                }
            }
        }


    }
    void Send(int clientSocket, const char *msg) {
        pair<string,SimplyLinkedList<Huffman_pair*>*> compressed;
        compressed = HuffmanCompression::buildHuffmanTree(msg);
        auto final_sms = new Huffman_Message();
        final_sms->setCompress_Code(compressed.first);
        for (int i = 0; i < compressed.second->getLen(); ++i) {
            final_sms->getHuffman_Table()->append(compressed.second->get(i));
        }
        string final = JSON_Management::HuffmanMessageToJSON(final_sms);
        cout << final;
        int sendRes = send(clientSocket, final.c_str(), final.size()+1, 0);
        if (sendRes == -1) {
            std::cout << "SEND MESSAGE FAILED " << std::endl;
        }
    }

    void Identify_Client(const string& client, const string& specific,int num){

        if(client == "DISK"){
            if(specific == "D1"){
                Disk1_Client = num;
                cout<< "EL DISCO 1 SE HA CONECTADO CON EXITO" << endl;
            }else if(specific == "D2"){
                Disk2_Client = num;
                cout<< "EL DISCO 2 SE HA CONECTADO CON EXITO" << endl;
            }else if(specific == "P1"){
                Parity_Disk_Client = num;
                cout<< "EL DISCO DE PARIDAD SE HA CONECTADO CON EXITO" << endl;
            }
        }else {
            App_Client = num;
            cout<< "LA APLICACION DE PRUEBA SE HA CONECTADO CON EXITO" << endl;
        }
    }

    void Identify_Controller(const string& type,string specific,const string& sms){
        /**
         * DEBO DE CORREGIR QUE ENVIE MENSAJES CUANDO LE DE LA GANA
         */
        if(type == "DISK"){
            if(specific == "D1"){
                /**
                 * INFO PARA EL DISCO 1
                 */
                auto app_response = new AppMessage();
                string response = JSON_Management::GetJSONString("Save",sms);
                if(response  == "TRUE"){
                    app_response->setStatus("TRUE");
                    string result = JSON_Management::AppMessageToJSON(app_response);
                    Send(App_Client,result.c_str());
                    cout << "EL MENSAJE SE GUARDO CON EXITO"<< endl;

                }else{
                    string binarycode = JSON_Management::GetJSONString("Binary",sms);
                    App_Controller::getDisk1_Info() = binarycode;
                }

            }else if(specific == "D2"){
                /**
                * INFO PARA EL DISCO 2
                */
                auto app_response = new AppMessage();
                string response = JSON_Management::GetJSONString("Save",sms);
                if(response  == "TRUE"){
                    app_response->setStatus("TRUE");
                    string result = JSON_Management::AppMessageToJSON(app_response);
                    Send(App_Client,result.c_str());
                    cout << "EL MENSAJE SE GUARDO CON EXITO"<< endl;

                }else{
                    string binarycode = JSON_Management::GetJSONString("Binary",sms);
                    App_Controller::getDisk2_Info() = binarycode;
                }
            }else if(specific == "P1"){
                auto app_response = new AppMessage();
                string response = JSON_Management::GetJSONString("Save",sms);
                if(response  == "TRUE"){
                    app_response->setStatus("TRUE");
                    string result = JSON_Management::AppMessageToJSON(app_response);
                    Send(App_Client,result.c_str());
                    cout << "EL MENSAJE SE GUARDO CON EXITO"<< endl;

                }else{
                    string binarycode = JSON_Management::GetJSONString("Binary",sms);
                    App_Controller::getParityD_Info() = binarycode;
                }
            }
        }else {
            string tag =  JSON_Management::GetJSONString("Request", sms);
            if(tag == "SAVE"){

                const char *path = JSON_Management::GetJSONString("Path", sms).c_str();
                string dirpath = JSON_Management::GetJSONString("Path", sms);

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
                    string txt_info = App_Controller::Read_File((dirpath + "/" + filesList->get(i)));
                    string filename = stringList->get(i);
                    string txt_binary = App_Controller::File_Compression(txt_info);
                    App_Controller::Divide_files(txt_binary);
                    auto d1_save = new DiskMessage();
                    auto d2_save = new DiskMessage();
                    auto pd_save = new DiskMessage();
                    d1_save->setBinary_Code(App_Controller::getDisk1_Info());
                    d2_save->setBinary_Code(App_Controller::getDisk1_Info());
                    pd_save->setBinary_Code(App_Controller::getParityD_Info());
                    d1_save->setRequest("SAVE");
                    d2_save->setRequest("SAVE");
                    pd_save->setRequest("SAVE");
                    d1_save->setFilename(filename);
                    d2_save->setFilename(filename);
                    pd_save->setFilename(filename);
                    string d1sms = JSON_Management::DiskMessageToJSON(d1_save);
                    string d2sms = JSON_Management::DiskMessageToJSON(d2_save);
                    string pdsms = JSON_Management::DiskMessageToJSON(pd_save);
                    Send(Disk1_Client,d1sms.c_str());
                    Send(Disk2_Client,d2sms.c_str());
                    Send(Parity_Disk_Client,pdsms.c_str());

                }


            }else if(tag == "OPEN"){

                //App_Controller::Extract_txt(sms);
                string tag =  JSON_Management::GetJSONString("Filename", sms);
                auto d1_sms = new DiskMessage();
                auto d2_sms = new DiskMessage();
                d1_sms->setFilename(tag);
                d1_sms->setRequest("OPEN");
                d2_sms->setFilename(tag);
                d2_sms->setRequest("OPEN");
                string final_sms1 = JSON_Management::DiskMessageToJSON(d1_sms);
                string final_sms2 = JSON_Management::DiskMessageToJSON(d2_sms);
                Send(Server::getInstance()->getDisk1_Client(),final_sms1.c_str());
                Send(Server::getInstance()->getDisk2_Client(),final_sms2.c_str());
                string binary_code = App_Controller::Build_files(App_Controller::getDisk1_Info(),App_Controller::getDisk2_Info());
                string text  = App_Controller::File_Decompression(binary_code);
                auto filesms = new AppMessage();
                filesms->setText(text);
                string final_sms = JSON_Management::AppMessageToJSON(filesms);
                Server::getInstance()->Send(Server::getInstance()->getApp_Client(),final_sms.c_str());

            }else{
                auto response = new AppMessage();
                string kw =  JSON_Management::GetJSONString("Keyword", sms);
                auto s_request = App_Controller::Search_Words(kw);
                response->setKwB1(s_request->get(0));
                response->setKwB2(s_request->get(1));
                response->setKwB3(s_request->get(2));
                response->setKwB4(s_request->get(3));
                response->setKwB5(s_request->get(4));
                response->setKwB6(s_request->get(5));
                response->setKwB7(s_request->get(6));
                response->setKwB8(s_request->get(7));
                string result = JSON_Management::AppMessageToJSON(response);
                Send(App_Client,result.c_str());
            }
        }
    }

    static int getDisk1_Client(){
        return Disk1_Client;
    }
    static int getDisk2_Client(){
        return Disk2_Client;

    }
    static int getParity_Client(){
        return Parity_Disk_Client;
    }
    static int getApp_Client(){
        return App_Client;
    }
};

#endif //TEC_FS_SERVER_H
