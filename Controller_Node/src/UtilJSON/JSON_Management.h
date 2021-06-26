//
// Created by njohnson on 6/13/21.
//

#ifndef TEC_FS_JSON_MANAGEMENT_H
#define TEC_FS_JSON_MANAGEMENT_H

#include <iostream>
#include "../../../lib/rapidjson/stringbuffer.h"
#include "../../../lib/rapidjson/stringbuffer.h"
#include "../../../lib/rapidjson/writer.h"
#include "../../../lib/rapidjson/document.h"
#include "../../../lib/DataStructures/SimplyList.h"
#include "../Objects/AppMessage.h"
#include "../Objects/DiskMessage.h"
#include "../Objects/Huffman_Message.h"
#include "../Objects/Huffman_pair.h"

using namespace rapidjson;
using namespace std;

class JSON_Management
{
public:

    /**
     * @brief Method that gets the key searched from the JSON.
     * @param key the string that gets searched
     * @param jsonString  the JSON where the search is done
     * @return the string key from the JSON.
     */
    static string GetJSONString(string key, const string& jsonString) {
        rapidjson::Document document;
        document.Parse<kParseDefaultFlags>(jsonString.c_str());
        const char* searchedString;
        if (document.HasMember(key.c_str())) {
            if (document[key.c_str()].IsString()) {
                searchedString = document[key.c_str()].GetString();
                return searchedString;
            }
        }
        else {
            cout << "ERROR : KEY NOT FOUND" << endl;
            return " ";

        }
    }
    static string GetJSONStringArray(string key, const string& jsonString) {
        rapidjson::Document document;
        document.Parse<kParseDefaultFlags>(jsonString.c_str());
        const char* searchedString;
        if (document.HasMember(key.c_str())) {
            if (document[key.c_str()].IsString()) {
                searchedString = document[key.c_str()].GetString();
                return searchedString;
            }
        }
        else {
            cout << "ERROR : KEY NOT FOUND" << endl;
            return " ";

        }
    }
    /**
   * @brief Method that serializes a DiskMessage.h method to a JSON string
   * @param DIskmessageObject is the TypeMessage.h object that contains all the information
   * @return the serialized object into a JSON string
   */
    static string DiskMessageToJSON(DiskMessage* message){
        Document json_document;
        StringBuffer buffer;

        Document::AllocatorType& allocator = json_document.GetAllocator();

        Writer<rapidjson::StringBuffer> writer(buffer);

        writer.StartObject();

        writer.Key("Binary_Script");
        writer.String(message->getBinary_Code().c_str());

        writer.Key("Request");
        writer.String(message->getRequest().c_str());

        writer.Key("Filename");
        writer.String(message->getFilename().c_str());

        writer.EndObject();

        return buffer.GetString();
    }

    /**
* @brief Method that serializes a AppMessage.h method to a JSON string
* @param AppmessageObject is the AppMessage.h object that contains all the information
* @return the serialized object into a JSON string
*/
    static string AppMessageToJSON(AppMessage *message){
        Document json_document;
        StringBuffer buffer;

        Document::AllocatorType& allocator = json_document.GetAllocator();

        Writer<rapidjson::StringBuffer> writer(buffer);

        writer.StartObject();

        writer.Key("Message");
        writer.String(message->getMessage().c_str());

        writer.EndObject();

        return buffer.GetString();
    }

    /**
    * @brief Method that serializes a Huffman_Message.h method to a JSON string
    * @param huffmanmessageObject is the Huffman_Message.h object that contains all the information
    * @return the serialized object into a JSON string
    */
    static string HuffmanMessageToJSON(Huffman_Message* huffmanmessageObject) {
        Document json_document;
        StringBuffer stringbuffer;

        SimplyLinkedList<Huffman_pair*> *jsonHuffmanList = huffmanmessageObject->getHuffman_Table();
        int list_lenght = huffmanmessageObject->getHuffman_Table()->getLen();


        json_document.SetArray();
        Document::AllocatorType& allocator = json_document.GetAllocator();

        Writer<rapidjson::StringBuffer> writer(stringbuffer);

        writer.StartObject();

        writer.Key("Code");
        writer.String(huffmanmessageObject->getCompress_Code().c_str());

        writer.Key("HuffmanTable");
        writer.StartArray();

        for (int i = 0; i < list_lenght; i++)
        {
            Huffman_pair* object = jsonHuffmanList->get(i);
            SerializeHuffmanToJSON(&writer, object);
        }
        writer.EndArray();

        writer.EndObject();

        return stringbuffer.GetString();
    }

    /**
    * @brief Method that serializes a Huffman_pair.h object using a writer object
    * @param writer object used for serializing object and huffmanObject is the Huffman_pair.h object
    */
    static void SerializeHuffmanToJSON(rapidjson::Writer<rapidjson::StringBuffer> *writer, Huffman_pair* huffmanObject){
        writer->StartObject();
        writer->Key("huffman_ch");
        string ch(1, huffmanObject->getCH());
        writer->String(ch.c_str());
        writer->Key("huffman_codes");
        writer->String(huffmanObject->getCode().c_str());

        writer->EndObject();
    }
    /**
    * @brief Method that serializes a Huffman_pair.h object using a writer object
    * @param writer object used for serializing object and huffmanObject is the Huffman_pair.h object
    */
    static Huffman_Message *DeserializetoHuffmanMessage(const string &s){
        rapidjson::Document doc;
        auto huffmanMessageObject = new Huffman_Message();
        doc.Parse(s.c_str());

        huffmanMessageObject->setCompress_Code(doc["Code"].GetString());
        Value& huffmanTable = doc["HuffmanTable"];
        assert(huffmanTable.IsArray());
        for (SizeType i = 0; i < huffmanTable.Size(); i++) {
            auto huffman = new Huffman_pair();
            huffman->setCH(huffmanTable[i]["huffman_ch"].GetString()[0]);
            huffman->setCode(huffmanTable[i]["huffman_codes"].GetString());
            huffmanMessageObject->getHuffman_Table()->append(huffman);

        }
        return huffmanMessageObject;
    }


};
#endif //TEC_FS_JSON_MANAGEMENT_H
