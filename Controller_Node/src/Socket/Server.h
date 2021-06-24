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


#define TRUE 1

using namespace std;
class Server{
public:
    [[noreturn]] static void InitServer()
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
                            cout << "Soy el message" << " " << message << endl;
                            auto huffmanMessage = new Huffman_Message();
                            huffmanMessage = JSON_Management::DeserializetoHuffmanMessage(message);

                            string msg = HuffmanCompression::Decode_Huffman(huffmanMessage->getCompress_Code(),huffmanMessage->getHuffman_Table());
                            cout << "SOY EL MESAJEJE  " << " "<< msg << endl;
                            string first = JSON_Management::GetJSONString("First_Time", msg);
                            string type1  = JSON_Management::GetJSONString("Client_Type", msg);

                            if(first == "TRUE"){
                                string type2 =  JSON_Management::GetJSONString("Specific_Type", msg);
                                Identify_Client(type1,type2,i);
                            }else{
                                Identify_Controller(type1,message);
                            }

                            send(clientSocket[i],buffer, strlen(buffer),0);
                        }


                    }

                }
            }
        }


    }

    static void Identify_Client(const string& client, const string& specific,int num){

        static int Disk1_Client;
        static int Disk2_Client;
        static int Parity_Disk_Client;
        static int App_Client;

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

    static void Identify_Controller(const string& type,const string& sms){

        if(type == "DISK"){
            Disk_Controller::Controller_Disk(sms);
        }else {
            App_Controller::Controller_App(sms);
        }
    }
};

#endif //TEC_FS_SERVER_H
