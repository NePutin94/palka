//
// Created by NePutin on 6/23/2021.
//

#ifndef PALKA_ENGINE_H
#define PALKA_ENGINE_H

#include <string>

#include "Vec2.h"
#include "ConsoleLog.h"
#include "Window.h"
#include "EventManager.h"
#include "ReflectionDebug.h"

namespace palka
{
    class Engine
    {
    private:
        bool console_open = false;
        Viewport view;
        Window w;

        bool isRuning = true;

    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false), view(RectF(0, 0, size.x, size.y))
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
            w.setViewport(view);
            isRuning = true;
            EventManager::addEvent(KBoardEvent::KeyPressed(GLFW_KEY_GRAVE_ACCENT), [this](EventData e) {
                console_open = !console_open;
            });
        }

        void render()
        {
            w.NewFrame();
            glPointSize(10);
            glLineWidth(2.5);
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_LINES);
            glVertex3f(10.0, 10.0, 0.0);
            glVertex3f(200.0, 200.0, 0.0);
            glEnd();
            Console::AppLog::Draw("Console", &console_open);

            w.ImGuiEndFrame();
            w.EndFrame();
        }

        void update()
        {
            debug(view, "view");
        }

        void handleEvents()
        {
            w.eventHandler();
        }
    };
}

#endif //PALKA_ENGINE_H
