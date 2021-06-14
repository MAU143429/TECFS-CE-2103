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
#include "../DataStructures/SimplyList.h"
#include "../Objects/TypeMessage.h"

using namespace rapidjson;
using namespace std;

class JSON_Management
{
public:
    static string TypeMessageToJSON(TypeMessage* message){
        Document json_document;
        StringBuffer buffer;

        Document::AllocatorType& allocator = json_document.GetAllocator();

        Writer<rapidjson::StringBuffer> writer(buffer);

        writer.StartObject();

        writer.EndObject();

        return buffer.GetString();
    }
};
#endif //TEC_FS_JSON_MANAGEMENT_H
