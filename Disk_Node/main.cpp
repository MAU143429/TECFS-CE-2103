#include <iostream>
#include <thread>
#include "src/Socket/Client.cpp"
#include "src/Algorithms/HuffmanCompression.h"
#include "src/UtilJSON/JSON_Management.h"
#include "src/Disk_Source/Disk_Manager.h"

static string PATH;
void RunClient(string client) {
    InitClient();
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

void RunDIsks(string path) {
    Disk_Manager::InitDisk(path);
    PATH = path;

}

int main() {

    string client;
    string newpath;
    string userInput;
    string userInput2;
    cout<< "Define the type of the Disk: " ;
    getline(cin, userInput);
    cout<< "Define the path of the Disk: " ;
    getline(cin, userInput2);
    client = userInput;
    newpath = userInput2;
    thread runs(RunClient,client);
    thread runs1(RunDIsks,newpath);
    runs.join();
    runs1.join();
    return 0;
}
