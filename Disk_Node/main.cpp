#include <iostream>
#include <thread>
#include "src/Socket/Client.cpp"
#include "src/Algorithms/HuffmanCompression.h"
#include "src/UtilJSON/JSON_Management.h"

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
    pair<string,SimplyLinkedList<Huffman_pair*>*> compressed;
    compressed = HuffmanCompression::buildHuffmanTree(newjson);
    auto final_sms = new Huffman_Message();
    final_sms->setCompress_Code(compressed.first);
    for (int i = 0; i < compressed.second->getLen(); ++i) {
        final_sms->getHuffman_Table()->append(compressed.second->get(i));
    }
    string final = JSON_Management::HuffmanMessageToJSON(final_sms);
    Send(final.c_str());
}

int main() {

    string client;
    string userInput;
    cout<< "Define the type of the Disk: " ;
    getline(cin, userInput);
    client = userInput;
    thread runs(RunClient,client);
    runs.join();
    return 0;
}
