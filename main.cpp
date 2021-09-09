#include <algorithm>
#include "palka_core/Engine.h"
using namespace std;

int main(int argc, char* argv[])
{
    palka::Engine e(palka::Vec2(1280, 720));
    e.run();
    return 0;
}
