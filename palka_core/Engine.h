//
// Created by NePutin on 6/23/2021.
//

#ifndef PALKA_ENGINE_H
#define PALKA_ENGINE_H

#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <GL/gl.h>
#include <string>

#include "Vec2.h"
#include "ConsoleLog.h"
#include "Window.h"
#include "EventManager.h"

namespace palka
{
    class Engine
    {
    private:
        bool console_open = false;
        Window w;
        bool isRuning;
    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false)
        {
            init();
        }

        void run()
        {
            while (isRuning)
            {
                handleEvents();
                w.ImGUiNewFrame();
                update();
                render();
            }
        }

        void init()
        {
            w.create();
            isRuning = true;
            EventManager::addEvent(KBoardEvent::KeyPressed(GLFW_KEY_GRAVE_ACCENT), [this](EventData e) {
                console_open = !console_open;
            });
        }

        void render()
        {
            w.NewFrame();

            Console::AppLog::Draw("Console", &console_open);
            w.ImGuiEndFrame();
            w.EndFrame();
        }

        void update()
        {
            w.inputHandler();
        }

        void handleEvents()
        {
            w.eventHandler();
        }
    };
}

#endif //PALKA_ENGINE_H
