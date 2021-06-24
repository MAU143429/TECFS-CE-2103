//
// Created by mau on 6/14/21.
//
#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <arpa/inet.h>
#include "../Objects/Huffman_Message.h"
#include "../../../lib/DataStructures/SimplyList.h"
#include "../UtilJSON/JSON_Management.h"
#include "../Algorithms/HuffmanCompression.h"


using namespace std;

int clientSocket = socket(AF_INET,SOCK_STREAM,0);

static void Send(const char *msg) {
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
int InitClient()
{
    int port;
    if(clientSocket == -1){
        return 1;
    }

    cout<<"Type the port address you want to connect : " << endl;
    cin >> port;
    string ipAddress = "127.0.0.1";

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET,ipAddress.c_str(),&addr.sin_addr);

    int connectRes = connect(clientSocket,(sockaddr*)&addr,sizeof (addr));
    if(connectRes == 0){
        cout<< "You have connect to server !" << endl;
    }

    if(connectRes == -1){
        return 1;
    }
    char buf[4096];
    string userInput;


    do{

        getline(cin,userInput);

        int sendRes = send(clientSocket,userInput.c_str(),userInput.size()+1,0);

        if(sendRes == -1){
            cout<<"Could not send to server\r\n";
            continue;
        }
        //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //		Display response
            cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
        }

    }while(true);

}
