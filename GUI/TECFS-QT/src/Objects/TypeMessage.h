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

    string appName;
    string keyWord;
    string Path;
    string firstTime;
    string clientType;
    string specificType;
    string fileName;
    string request;
public:
    const string &getRequest() const {
        return request;
    }

    void setRequest(const string &request) {
        TypeMessage::request = request;
    }

    const string &getFileName() const {
        return fileName;
    }

    void setFileName(const string &fileName) {
        TypeMessage::fileName = fileName;
    }

    const string &getAppName() const {
        return appName;
    }

    void setAppName(const string &appName) {
        TypeMessage::appName = appName;
    }

    const string &getFirstTime() const {
        return firstTime;
    }

    void setFirstTime(const string &firstTime) {
        TypeMessage::firstTime = firstTime;
    }

    const string &getClientType() const {
        return clientType;
    }

    void setClientType(const string &clientType) {
        TypeMessage::clientType = clientType;
    }

    const string &getSpecificType() const {
        return specificType;
    }

    void setSpecificType(const string &specificType) {
        TypeMessage::specificType = specificType;
    }

    const string &getPath() const {
        return Path;
    }

    void setPath(const string &path) {
        Path = path;
    }

    const string &getKeyWord() const {
        return keyWord;
    }

    void setKeyWord(const string &keyWord) {
        TypeMessage::keyWord = keyWord;
    }

};

#endif //TECFS-QT_TYPEMESSAGE_H
