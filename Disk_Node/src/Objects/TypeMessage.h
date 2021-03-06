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
    string first,client,specific,save,binary_code;
public:
    const string &getBinaryCode() const {
        return binary_code;
    }

    void setBinaryCode(const string &binaryCode) {
        binary_code = binaryCode;
    }

    const string &getSave() const {
        return save;
    }

    void setSave(const string &save) {
        TypeMessage::save = save;
    }

    const string &getClient() const {
        return client;
    }

    void setClient(const string &client) {
        TypeMessage::client = client;
    }

    const string &getSpecific() const {
        return specific;
    }

    void setSpecific(const string &specific) {
        TypeMessage::specific = specific;
    }

    const string& getFirst() const {
        return first;
    }

    void setFirst(const string& newfirst) {
        first = newfirst;
    }

};

#endif //TEC_FS_TYPEMESSAGE_H
