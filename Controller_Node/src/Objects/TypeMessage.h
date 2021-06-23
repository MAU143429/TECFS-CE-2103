//
// Created by njohnson on 6/13/21.
//

#ifndef TEC_FS_TYPEMESSAGE_H
#define TEC_FS_TYPEMESSAGE_H

#include <iostream>
#include "../../../lib/DataStructures/SimplyList.h"

using namespace std;

class TypeMessage
{
private:
    string message_to_send;
public:

    const string& getMessage() const {
        return message_to_send;
    }

    void setMessage(const string& newsms) {
        message_to_send = newsms;
    }

};

#endif //TEC_FS_TYPEMESSAGE_H
