
#ifndef META_H
#define META_H

#include <string>
using std::string;

typedef struct Meta{
    string StoreID;
    string Mac;
    string UniqueID; //reserved

    int Type;   //1-request new customer id,
                //2-id request
                //3-data upload
                //etc
    double Feature[128];
    int Gender; //0-femail, 1-mail
    int Age;    //0-chiled, 1-youny, 2-middle, 3-older
    int ROI[4];
    long TimeStamp; //java: System.currentTimeMillis()
                    //c++11: milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    int CustomerID; //-1 for invalid ID
}Meta_t;

#if 0
{
    "StoreID":"idsample",
    "Mac":"b4:a3:82:5e:5f:15",
    "UniqueID":"internalid",
    "Type": 0,
    "Feature":[
        1.1,
        2.2,
        3.3,
        ...
        128.8
    ],
    "Gender":0,
    "Age":0,
    "ROI":[1,2,3,4],
    "TimeStamp":12345678,
    "CustomerID":-1
}
#endif

#endif
