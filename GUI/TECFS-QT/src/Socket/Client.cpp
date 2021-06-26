//
// Created by mau on 6/14/21.
//

#include "Client.h"

Client* Client::unique_instance {nullptr};
mutex Client::mutex_;

Client::Client() {}
Client::~Client() {}
/**
 * @brief Getter for the unique instance of the client
 * @return the client instance
 */
Client *Client::getInstance() {
    lock_guard<std::mutex> lock(mutex_);
    if (unique_instance == nullptr){unique_instance = new Client();}
    return unique_instance;
}

void Client::Send(const char *msg) {

    pair<string,SimplyLinkedList<Huffman_pair*>*> compressed;
    compressed = HuffmanCompression::buildHuffmanTree(msg);
    auto final_sms = new Huffman_Message();
    final_sms->setCompress_Code(compressed.first);
    for (int i = 0; i < compressed.second->getLen(); ++i) {
        final_sms->getHuffman_Table()->append(compressed.second->get(i));
    }
    string final = JSON_Management::HuffmanMessageToJSON(final_sms);
    cout << "\n Soy el mensaje Final :\n" << final;
    int sendRes = send(clientSocket, final.c_str(), final.size()+1, 0);
    if (sendRes == -1) {
        std::cout << "SEND MESSAGE FAILED " << std::endl;
    }
}
int Client::InitClient()
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

    auto Connect_sms = new TypeMessage();
    Connect_sms->setClientType("APP");
    Connect_sms->setFirstTime("TRUE");
    Connect_sms->setSpecificType("APP");
    string newjson = JSON_Management::TypeMessageToJSON(Connect_sms);
    Send(newjson.c_str());


    if(connectRes == -1){
        return 1;
    }
    char buf[4096];
    string userInput;


    do{

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
            server_response = string(buf, bytesReceived);
        }

    }while(true);

}

string Client::ReadString(){
    return server_response;
}

string Client::setResponse(string newresponse){
    server_response = newresponse;
}