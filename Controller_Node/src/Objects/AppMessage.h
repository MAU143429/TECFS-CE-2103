//
// Created by njohnson on 6/13/21.
//

#ifndef TEC_FS_APPMESSAGE_H
#define TEC_FS_APPMESSAGE_H

#include <iostream>
#include "../../../lib/DataStructures/SimplyList.h"

using namespace std;

class AppMessage
{
private:
    string kw_b1,kw_b2,kw_b3,kw_b4,kw_b5,kw_b6,kw_b7,kw_b8,status,text;
public:
    const string &getText() const {
        return text;
    }

    void setText(const string &text) {
        AppMessage::text = text;
    }

    const string &getKwB1() const {
        return kw_b1;
    }

    void setKwB1(const string &kwB1) {
        kw_b1 = kwB1;
    }

    const string &getKwB2() const {
        return kw_b2;
    }

    void setKwB2(const string &kwB2) {
        kw_b2 = kwB2;
    }

    const string &getKwB3() const {
        return kw_b3;
    }

    void setKwB3(const string &kwB3) {
        kw_b3 = kwB3;
    }

    const string &getKwB4() const {
        return kw_b4;
    }

    void setKwB4(const string &kwB4) {
        kw_b4 = kwB4;
    }

    const string &getKwB5() const {
        return kw_b5;
    }

    void setKwB5(const string &kwB5) {
        kw_b5 = kwB5;
    }

    const string &getKwB6() const {
        return kw_b6;
    }

    void setKwB6(const string &kwB6) {
        kw_b6 = kwB6;
    }

    const string &getKwB7() const {
        return kw_b7;
    }

    void setKwB7(const string &kwB7) {
        kw_b7 = kwB7;
    }

    const string &getKwB8() const {
        return kw_b8;
    }

    void setKwB8(const string &kwB8) {
        kw_b8 = kwB8;
    }

    const string &getStatus() const {
        return status;
    }

    void setStatus(const string &status) {
        AppMessage::status = status;
    }

};

#endif //TEC_FS_APPMESSAGE_H
