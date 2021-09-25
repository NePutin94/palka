//
// Created by NePutin on 6/23/2021.
//

#ifndef PALKA_ENGINE_H
#define PALKA_ENGINE_H

#include <string>
#include <glm/vec2.hpp>
#include "Vec2.h"
#include "ConsoleLog.h"
#include "Window.h"
#include "EventManager.h"
#include "ReflectionDebug.h"
#include "Texture.h"
#include "Shader.h"
#include "Sprite.h"
#include "RenderTexture.h"
#include "Rectangle.h"
#include "DebugDraw.h"
#include "VertexBuffer.h"

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
        Sprite test;
        Shader s;
        double oldTimeSinceStart = 0;
        double timeSinceStart;
        float t = 0;
        float delta;
        Rectangle p;
        VertArray ver;
        VertexBuffer buff;
        Shader vertexShader;
    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false), view(RectF(0, 0, size.x, size.y)), p({0, 0, 180, 180}, 5),
                                      ver(VertArray::Quads)
        {
            init();
            p.setOutlineColor(Color{250, 0, 50, 255});
            p.setPosition({10, 0});
            tex.LoadFromFile("Data\\tex\\Debug.png");
            test.setTexture(tex);
            w.getViewport().setCenter({1280.f / 2, 720.f / 2});
            //s.loadVF("Data\\Shaders\\Default.frag", "Data\\Shaders\\Default.vert");
            //s.load("Data\\Shaders\\test.frag");
            ver.add(Vertex{{0, 0}, Color{255, 0, 0}});
            ver.add(Vertex{{100, 0}, Color{0, 255, 0}});
            ver.add(Vertex{{100, 100}, Color{0, 0, 255}});
            ver.add(Vertex{{0, 100}, Color{255, 0, 255}});
            vertexShader.loadVF("Data\\Shaders\\Default.frag", "Data\\Shaders\\Default.vert");
            buff.create(ver.getSize());
            buff.update(&ver[0], ver.getSize(), vertexShader.getId());
            vertexShader.UseUbo();
            //w.initVbo(ver);
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
            //w.setViewport(view);
            isRuning = true;
            EventManager::addEvent(KBoardEvent::KeyPressed(GLFW_KEY_GRAVE_ACCENT), [this](EventData e) {
                console_open = !console_open;
            });
            EventManager::addEvent(EventType::WINDOWCLOSE, [this](EventData e) {
                isRuning = false;
            });
        }

        void render()
        {
            w.clear();
            //w.draw(p);
            // w.draw(test);
            w.draw(ver);
            //w.VBODraw(ver);
            static TransformObject test;
            RenderContext con;
            con.transform = test.getTransform();
            w.VAODraw(buff, vertexShader, con);
            Console::AppLog::Draw("Console", &console_open);
            w.ImGuiEndFrame();
            w.EndFrame();
        }

        void update()
        {
            debug(w.getViewport(), "view");
            debug(test, "test");
            debug(p, "rect");
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
