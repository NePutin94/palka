//
// Created by NePutin on 7/11/2021.
//

#ifndef PALKA_TEST_H
#define PALKA_TEST_H

#include <rttr/type>
#include <rttr/registration_friend>
#include "ReflectionDebug.h"
using namespace rttr;

class Test1 : public palka::utility::DebugTree
{
    RTTR_ENABLE(palka::utility::DebugTree)
    RTTR_REGISTRATION_FRIEND
    int x;
    int y;
public:
    void setXY(int z, int t)
    { x = z, y = t; }
};

class Test2 : public palka::utility::DebugTree
{
public:
    RTTR_ENABLE(palka::utility::DebugTree)
    RTTR_REGISTRATION_FRIEND
public:
    std::string z;
    float ftest2;
    Test1 t;

    Test2()
    {
        z = "fdsgsh";
        t.setXY(12, 14);
    }
};

class Test3 : public palka::utility::DebugTree
{

    RTTR_ENABLE(palka::utility::DebugTree)
    RTTR_REGISTRATION_FRIEND
public:
    Test2 asd;
    float ftest;
    std::string stest;

    Test3() = default;
};


#endif //PALKA_TEST_H
