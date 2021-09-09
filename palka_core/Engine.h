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
#include "Texture.h"
#include "Shader.h"


namespace palka
{
    class Engine
    {
    private:
        bool console_open = false;
        Viewport view;
        Window w;
        GLuint textureID;
        bool isRuning = true;
        Texture tex;
        Shader s;
        double oldTimeSinceStart = 0;
        double timeSinceStart;
        float t = 0;
        float delta;
        VertArray vert;
    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false), view(RectF(0, 0, size.x, size.y)),vert(VertArray::Type::Quads)
        {
            init();
            int x, y, n;
            tex.LoadFromFile("Data\\tex\\Hero.png");
            view.setCenter({1280.f / 2, 720.f / 2});

            s.load("Data\\Shaders\\test.frag");
            vert.add({Vec2f{100, 100}, Color::White(),     Vec2f{0, 0}});
            vert.add({Vec2f{200, 100}, Color::White(),     Vec2f{1, 0}});
            vert.add({Vec2f{200, 200}, Color::White(),     Vec2f{1, 1}});
            vert.add({Vec2f{100, 200}, Color::White(),     Vec2f{0, 1}});
        }

        void run()
        {
            glfwSetTime(0);
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

            w.draw(vert, tex);

            Console::AppLog::Draw("Console", &console_open);
            w.ImGuiEndFrame();
            w.EndFrame();
        }

        void update()
        {
            //debug(view, "view");
            debug(vert, "vert");
            Color test{0,0,255};
            timeSinceStart = glfwGetTime();
            delta = timeSinceStart - oldTimeSinceStart;
            oldTimeSinceStart = timeSinceStart;
        }

        void handleEvents()
        {
            w.eventHandler();
        }
    };
}

#endif //PALKA_ENGINE_H
