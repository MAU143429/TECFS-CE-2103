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
    cout << "Soy el final" << final << "\n";
    int sendRes = send(clientSocket, final.c_str(), final.size()+1, 0);
    cout << "se envio el mensaje\n";
    if (sendRes == -1) {
        std::cout << "SEND MESSAGE FAILED " << std::endl;
    }
}
int Client::InitClient(string client)
{
    NUM_CLIENT = client;
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
    Connect_sms->setClient("DISK");
    Connect_sms->setFirst("TRUE");
    if(client == "1"){
        Connect_sms->setSpecific("D1");
    }else if(client == "2"){
        Connect_sms->setSpecific("D2");
    }else{
        Connect_sms->setSpecific("P1");
    }
    string newjson = JSON_Management::TypeMessageToJSON(Connect_sms);

    cout << "Antes de enviar\n" << newjson << "\n";
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
            client_message = string(buf, 0, bytesReceived);
            if(!client_message.empty()){
                const string &response = Disk_Manager::Select_Request(client_message,NUM_CLIENT);
                Send(response.c_str());

            }
        }

    }while(true);

}
