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
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"

namespace palka
{
    class Engine
    {
    private:
        bool console_open = false;
        Viewport view;
        Window w;

        bool isRuning = true;

        double oldTimeSinceStart = 0;
        double timeSinceStart;
        float t = 0;
        float delta;
        palka::VertArray cub;
        VertexBuffer buff;
        Shader vertexShader;
        VertexBufferObject vbo;
        VertexArrayObject vao;
    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false), view(RectF(0, 0, size.x, size.y))

        {
            init();
            w.getViewport().setCenter({1280.f / 2, 720.f / 2});
            //s.loadVF("Data\\Shaders\\Default.frag", "Data\\Shaders\\Default.vert");
            //s.load("Data\\Shaders\\test.frag");
//            glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f),
//            glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f)
            cub.add({{-0.5f, -0.5f, -0.5f,},Color{255,0,0}, {0.0f,  0.0f}});
            cub.add({{0.5f, -0.5f, -0.5f,},Color{255,0,0},{1.0f, 0.0f}});
            cub.add({{0.5f, 0.5f, -0.5f,},Color{255,0,0},{1.0f, 1.0f}});
            cub.add({{0.5f, 0.5f, -0.5f,},Color{255,0,0},{1.0f, 1.0f}});
            cub.add({{-0.5f, 0.5f, -0.5f,},Color{255,0,0},{0.0f,  1.0f}});
            cub.add({{-0.5f, -0.5f, -0.5f,},Color{255,0,0},{0.0f,  0.0f}});
            cub.add({{-0.5f, -0.5f, 0.5f,},Color{255,0,255},{0.0f,  0.0f}});
            cub.add({{0.5f, -0.5f, 0.5f,},Color{255,0,255},{1.0f, 0.0f}});
            cub.add({{0.5f, 0.5f, 0.5f,},Color{255,0,255},{1.0f, 1.0f}});
            cub.add({{0.5f, 0.5f, 0.5f,},Color{255,0,255},{1.0f, 1.0f}});
            cub.add({{-0.5f, 0.5f, 0.5f,},Color{255,0,255},{0.0f,  1.0f}});
            cub.add({{-0.5f, -0.5f, 0.5f,},Color{255,0,255},{0.0f,  0.0f}});
            cub.add({{-0.5f, 0.5f, 0.5f,},{1.0f,  0.0f}});
            cub.add({{-0.5f, 0.5f, -0.5f,},{1.0f,  1.0f}});
            cub.add({{-0.5f, -0.5f, -0.5f,},{0.0f,  1.0f}});
            cub.add({{-0.5f, -0.5f, -0.5f,},{0.0f,  1.0f}});
            cub.add({{-0.5f, -0.5f, 0.5f,},{0.0f,  0.0f}});
            cub.add({{-0.5f, 0.5f, 0.5f,},{1.0f,  0.0f}});
            cub.add({{0.5f, 0.5f, 0.5f,},{1.0f, 0.0f}});
            cub.add({{0.5f, 0.5f, -0.5f,},{1.0f, 1.0f}});
            cub.add({{0.5f, -0.5f, -0.5f,},{0.0f, 1.0f}});
            cub.add({{0.5f, -0.5f, -0.5f,},{0.0f, 1.0f}});
            cub.add({{0.5f, -0.5f, 0.5f,},{0.0f, 0.0f}});
            cub.add({{0.5f, 0.5f, 0.5f,},{1.0f, 0.0f}});
            cub.add({{-0.5f, -0.5f, -0.5f,},{0.0f,  1.0f}});
            cub.add({{0.5f, -0.5f, -0.5f,},{1.0f, 1.0f}});
            cub.add({{0.5f, -0.5f, 0.5f,},{1.0f, 0.0f}});
            cub.add({{0.5f, -0.5f, 0.5f,},{1.0f, 0.0f}});
            cub.add({{-0.5f, -0.5f, 0.5f,},{0.0f,  0.0f}});
            cub.add({{-0.5f, -0.5f, -0.5f,},{0.0f,  1.0f}});
            cub.add({{-0.5f, 0.5f, -0.5f,},{0.0f,  1.0f}});
            cub.add({{0.5f, 0.5f, -0.5f,},{1.0f, 1.0f}});
            cub.add({{0.5f, 0.5f, 0.5f,},{1.0f, 0.0f}});
            cub.add({{0.5f, 0.5f, 0.5f,},{1.0f, 0.0f}});
            cub.add({{-0.5f, 0.5f, 0.5f,},{0.0f,  0.0f}});
            cub.add({{-0.5f, 0.5f, -0.5f,},{0.0f,  1.0f}});
            vertexShader.loadVF("Data\\Shaders\\Default.frag", "Data\\Shaders\\Default.vert");
            vertexShader.UseUbo();
            buff.create(cub.getSize());
            buff.update(&cub[0], cub.getSize(), vertexShader.getId());

            vao.create(cub.getSize());
            vao.bind();
            vbo.create(sizeof(Vertex) * cub.getSize());
            vbo.setData(&cub[0],sizeof(Vertex) * cub.getSize());
            vao.setPointers<Vertex>();
            vbo.unbind();
            vao.unbind();

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
            //w.init();
        }

        void render()
        {
            w.clear();
            //w.draw(p);
            // w.draw(test);
            static TransformObject test;
            static float angle = 0;
            angle +=    0.005;
            test.setRotation(angle);
            RenderContext cont;
            cont.transform = test.getTransform();
//            w.draw(pyr);
            //w.VBODraw(ver);
            test.setRotation(angle);
            RenderContext con;
            con.transform = test.getTransform();
            w.VAODraw(vao, vertexShader, con);
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
