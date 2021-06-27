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

        if(type == "DISK"){
            if(specific == "D1"){
                Disk_Controller::Controller_Disk(sms,1);
            }else if(specific == "D2"){
                Disk_Controller::Controller_Disk(sms,2);
            }else if(specific == "P1"){
                Disk_Controller::Controller_Disk(sms,3);
            }
        }else {
            string tag =  JSON_Management::GetJSONString("Request", sms);
            if(tag == "SAVE"){
                App_Controller::Save_Info(sms);
            }else if(tag == "OPEN"){
                App_Controller::Extract_txt(sms);
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
