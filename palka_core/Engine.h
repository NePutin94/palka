//
// Created by NePutin on 6/23/2021.
//

#ifndef PALKA_ENGINE_H
#define PALKA_ENGINE_H

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
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

        bool isRuning = true;

        Shader s;
        double oldTimeSinceStart = 0;
        double timeSinceStart;
        float t = 0;
        float delta;
        palka::VertArray cub;
        VertexBuffer buff;
        Shader vertexShader;
    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false), view(RectF(0, 0, size.x, size.y))

        {
            init();
            w.getViewport().setCenter({1280.f / 2, 720.f / 2});
            //s.loadVF("Data\\Shaders\\Default.frag", "Data\\Shaders\\Default.vert");
            //s.load("Data\\Shaders\\test.frag");

            cub.add({{-0.5f, -0.5f,  -0.5f}, palka::Color{255,0,0}});
            cub.add({{ 0.5f, -0.5f,  -0.5f}, palka::Color{255,0,0}});
            cub.add({{ 0.5f,  0.5f,  -0.5f}, palka::Color{255,0,0}});
            cub.add({{ 0.5f,  0.5f,  -0.5f}, palka::Color{255,0,0}});
            cub.add({{ -0.5f,  0.5f, -0.5f}, palka::Color{255,0,0}});
            cub.add({{ -0.5f, -0.5f, -0.5f}, palka::Color{255,0,0}});
            cub.add({{ -0.5f, -0.5f,  0.5f}, palka::Color{0,0,255}});
            cub.add({{ 0.5f, -0.5f,   0.5f}, palka::Color{0,0,255}});
            cub.add({{ 0.5f,  0.5f,   0.5f}, palka::Color{0,0,255}});
            cub.add({{ 0.5f,  0.5f,   0.5f}, palka::Color{0,0,255}});
            cub.add({{ -0.5f,  0.5f,  0.5f}, palka::Color{0,0,255}});
            cub.add({{ -0.5f, -0.5f,  0.5f}, palka::Color{0,0,255}});
            cub.add({{ -0.5f,  0.5f,  0.5f}, palka::Color{0,255,0}});
            cub.add({{ -0.5f,  0.5f, -0.5f}, palka::Color{0,255,0}});
            cub.add({{ -0.5f, -0.5f, -0.5f}, palka::Color{0,255,0}});
            cub.add({{ -0.5f, -0.5f, -0.5f}, palka::Color{0,255,0}});
            cub.add({{ -0.5f, -0.5f,  0.5f}, palka::Color{0,255,0}});
            cub.add({{ -0.5f,  0.5f,  0.5f}, palka::Color{0,255,0}});
            cub.add({{ 0.5f,  0.5f,   0.5f}, palka::Color{255,0,255}});
            cub.add({{ 0.5f,  0.5f,  -0.5f}, palka::Color{255,0,255}});
            cub.add({{ 0.5f, -0.5f,  -0.5f}, palka::Color{255,0,255}});
            cub.add({{ 0.5f, -0.5f,  -0.5f}, palka::Color{255,0,255}});
            cub.add({{ 0.5f, -0.5f,   0.5f}, palka::Color{255,0,255}});
            cub.add({{ 0.5f,  0.5f,   0.5f}, palka::Color{255,0,255}});
            cub.add({{ -0.5f, -0.5f, -0.5f}, palka::Color{255,255,0}});
            cub.add({{ 0.5f, -0.5f,  -0.5f}, palka::Color{255,255,0}});
            cub.add({{ 0.5f, -0.5f,   0.5f}, palka::Color{255,255,0}});
            cub.add({{ 0.5f, -0.5f,   0.5f}, palka::Color{255,255,0}});
            cub.add({{ -0.5f, -0.5f,  0.5f}, palka::Color{255,255,0}});
            cub.add({{ -0.5f, -0.5f, -0.5f}, palka::Color{255,255,0}});
            cub.add({{ -0.5f,  0.5f, -0.5f}, palka::Color{90,155,180}});
            cub.add({{ 0.5f,  0.5f,  -0.5f}, palka::Color{90,155,180}});
            cub.add({{ 0.5f,  0.5f,   0.5f}, palka::Color{90,155,180}});
            cub.add({{ 0.5f,  0.5f,   0.5f}, palka::Color{90,155,180}});
            cub.add({{ -0.5f,  0.5f,  0.5f}, palka::Color{90,155,180}});
            cub.add({{ -0.5f,  0.5f, -0.5f}, palka::Color{90,155,180}});
            vertexShader.loadVF("Data\\Shaders\\Default.frag", "Data\\Shaders\\Default.vert");
            buff.create(cub.getSize());
            buff.update(&cub[0], cub.getSize(), vertexShader.getId());
            vertexShader.UseUbo();
            //w.initVbo(ver);
        }

        void run()
        {
            glfwSetTime(0);
            glEnable(GL_DEPTH_TEST);
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
            static TransformObject test;
            static float angle = 0;
            angle += 0.005;
            test.setRotation(angle);
            RenderContext cont;
            cont.transform = test.getTransform();
//            w.draw(pyr);
            //w.VBODraw(ver);
//
//
            test.setRotation(angle);
            RenderContext con;
            con.transform = test.getTransform();
            w.VAODraw(buff, vertexShader, con);
            Console::AppLog::Draw("Console", &console_open);
            w.ImGuiEndFrame();
            w.EndFrame();
        }

        void update()
        {
            debug(w.getCamera(), "camera");
            debug(w.getViewport(), "view");
            timeSinceStart = glfwGetTime();
            delta = timeSinceStart - oldTimeSinceStart;
            oldTimeSinceStart = timeSinceStart;
            EventManager::updateInputs();
        }

        void handleEvents()
        {
            w.eventHandler();
        }
    };
}

#endif //PALKA_ENGINE_H
