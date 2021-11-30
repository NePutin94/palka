#include "palka_core/Engine.h"

int main(int argc, char* argv[])
{
    palka::Engine e({1280, 720});
    e.run();
    return 0;
}
