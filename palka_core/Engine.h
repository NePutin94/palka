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
    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false), view(RectF(0, 0, size.x, size.y))
        {
            init();
            int x, y, n;
            tex.LoadFromFile("Data\\tex\\Hero.png");
            view.setCenter({1280.f / 2, 720.f / 2});

            s.load("Data\\Shaders\\test.frag");
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
            glUseProgram(s.shaderID);
            float alpha = float(std::sin(timeSinceStart * 10) + 1) / 2;
            GLint loc = glGetUniformLocation(s.shaderID, "time");
            if (loc != -1)
            {
                glUniform1f(loc, alpha);
            }
            glColor3f(0, 0, 0);
            glBegin(GL_QUADS);
            glVertex3f(0, 0, 0.0f);
            glVertex3f(0, 300, 0.0f);
            glVertex3f(300, 300, 0.0f);
            glVertex3f(300, 0, 0.0f);
            glEnd();
            Console::AppLog::Draw("Console", &console_open);
            w.ImGuiEndFrame();
            w.EndFrame();
        }

        void update()
        {
            debug(view, "view");
            timeSinceStart = glfwGetTime();
            delta = timeSinceStart - oldTimeSinceStart;
            oldTimeSinceStart = timeSinceStart;
            int z = 0;
        }

        void handleEvents()
        {
            w.eventHandler();
        }
    };
}

#endif //PALKA_ENGINE_H
