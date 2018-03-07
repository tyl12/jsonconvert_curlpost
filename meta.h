
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


#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
static int randNum(int min, int max)
{
    srand(time(0));
    return rand() % max + min;
}
static double randomDouble()
{
    const double lower_bound = 0;
    const double upper_bound = 1;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);

    std::random_device rand_dev;          // Use random_device to get a random seed.

    std::mt19937 rand_engine(rand_dev()); // mt19937 is a good pseudo-random number generator.
    double x = unif(rand_engine);
    return x;
}
static int generate_fake_meta_for_debug(Meta_t& meta)
{
    int d = randNum(0,100);
    meta.StoreID    = string("StoreID") + std::to_string(d);
    meta.Mac        = "1234:1234:1234:ffff";
    meta.UniqueID   = std::to_string(d);
    meta.Type       = 0;
    meta.Gender     = 0;
    meta.Age        = 2;
    for (int i=0;i<4;i++)
        meta.ROI[i] = i;
    //meta.TimeStamp =  std::chrono::duration_cast<  std::chrono::milliseconds >( std::chrono::system_clock::now().time_since_epoch());
    std::chrono::milliseconds ms = std::chrono::duration_cast<  std::chrono::milliseconds >( std::chrono::system_clock::now().time_since_epoch());
    meta.TimeStamp = ms.count();

    meta.CustomerID = -1;

    for (int i=0;i<128;i++)
        meta.Feature[i]=randomDouble();

    return 0;
}

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
