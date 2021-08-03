//
// Created by NePutin on 7/11/2021.
//

#include "Test.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<Test1>("Test1")
            .property("x", &Test1::x)
            .property("y", &Test1::y);

    registration::class_<Test2>("Test2")
            .property("z", &Test2::z)
            .property("ftest2", &Test2::ftest2)
            .property("t", &Test2::t);

    registration::class_<Test3>("Test3")
            .property("ftest", &Test3::ftest)
            .property("stest", &Test3::stest)
            .property("asd", &Test3::asd);
}
