//
// Created by mau on 6/25/21.
//

#ifndef TEC_FS_DISKMESSAGE_H
#define TEC_FS_DISKMESSAGE_H
#include <iostream>
#include "../../../lib/DataStructures/SimplyList.h"

using namespace std;

class DiskMessage
{
private:
    string binary_code,request,filename;
public:
    const string &getFilename() const {
        return filename;
    }

    void setFilename(const string &file) {
        DiskMessage::filename = file;
    }

    const string &getRequest() const {
        return request;
    }

    void setRequest(const string &request) {
        DiskMessage::request = request;
    }

    const string& getBinary_Code() const {
        return binary_code;
    }

    void setBinary_Code(const string& newsms) {
        DiskMessage::binary_code = newsms;
    }

};
#endif //TEC_FS_DISKMESSAGE_H
