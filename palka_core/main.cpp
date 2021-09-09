#include <algorithm>
#include "Vec2.h"
#include "Engine.h"

using namespace std;

int main(int argc, char* argv[])
{
//    palka::Vertex vert;
//    rttr::variant var{vert};
//    for (auto& p: var.get_type().get_properties())
//    {
//        if (p.get_name() == "color")
//        {
//            auto val = p.get_value(var);
//            for (auto& p2: val.get_type().get_properties())
//            {
//                if (p2.get_name() == "red")
//                {
//                    unsigned char new_value = 255;
//                    p2.set_value(val, new_value);
//                }
//                auto _val = p2.get_value(val);
//                unsigned char test = _val.get_value<unsigned char>();
//                val.get_type().set_property_value("red", val, _val);
//                for (auto& p2: val.get_type().get_properties())
//                {
//                    if (p2.get_name() == "red")
//                    {
//                       auto vv =  p2.get_value(val);
//                       unsigned char asdfas = vv.get_value<unsigned char>();
//                       int z = 1;
//                    }
//                }
//                int z = 1;
//            }
//
//        }
//    }
    palka::Engine e(palka::Vec2(1280, 720));
    e.run();
    return 0;
}
