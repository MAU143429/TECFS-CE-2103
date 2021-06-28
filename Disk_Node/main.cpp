#include <iostream>
#include <thread>
#include "src/Socket/Client.cpp"
#include "src/Algorithms/HuffmanCompression.h"
#include "src/UtilJSON/JSON_Management.h"
#include "src/Disk_Source/Disk_Manager.h"

static string PATH;
static string DISK;

void RunClient(const string& client) {
    Client::getInstance()->InitClient(client);

}

void RunDisks(const string& path){
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
    DISK = userInput;
    newpath = userInput2;
    thread runs(RunClient,client);
    thread runs2(RunDisks, newpath);
    runs.join();
    runs2.join();
    return 0;
}

