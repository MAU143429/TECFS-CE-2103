#include <iostream>
#include <thread>
#include "src/Socket/Client.cpp"
#include "src/Algorithms/HuffmanCompression.h"
#include "src/UtilJSON/JSON_Management.h"

void RunClient() {
    InitClient();

}

void sendMain(const string& client){
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
    Send(newjson.c_str());
}

int main() {

    string client;
    string userInput;
    cout<< "Define the type of the Disk: " ;
    getline(cin, userInput);
    client = userInput;
    thread runs(RunClient);
    thread runs2(sendMain, client);
    runs.join();
    runs2.join();
    return 0;
}
