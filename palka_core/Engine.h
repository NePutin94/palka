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
#include "StaticMesh.h"
#include "ShaderProgram.h"
#include "Mesh.h"


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
        // Shader vertexShader;
        Shader indexShader;
        Shader light;
        VertexBufferObject vbo;
        VertexArrayObject vao;
        UniformBuffer ubo;

        StaticMesh m;
        ShaderProgram p;
        Mesh test;
    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false), view(RectF(0, 0, size.x, size.y))
        {
            init();
            w.getViewport().setCenter({1280.f / 2, 720.f / 2});
            m.init();
            cub.add({{-0.5f, -0.5f, -0.5f,}, Color{255, 0, 0}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}});
            cub.add({{0.5f, -0.5f, -0.5f,}, Color{255, 0, 0}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}});
            cub.add({{0.5f, 0.5f, -0.5f,}, Color{255, 0, 0}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}});
            cub.add({{0.5f, 0.5f, -0.5f,}, Color{255, 0, 0}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}});
            cub.add({{-0.5f, 0.5f, -0.5f,}, Color{255, 0, 0}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}});
            cub.add({{-0.5f, -0.5f, -0.5f,}, Color{255, 0, 0}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}});
            cub.add({{-0.5f, -0.5f, 0.5f,}, Color{255, 0, 0}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});
            cub.add({{0.5f, -0.5f, 0.5f,}, Color{255, 0, 0}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});
            cub.add({{0.5f, 0.5f, 0.5f,}, Color{255, 0, 0}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}});
            cub.add({{0.5f, 0.5f, 0.5f,}, Color{255, 0, 0}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}});
            cub.add({{-0.5f, 0.5f, 0.5f,}, Color{255, 0, 0}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}});
            cub.add({{-0.5f, -0.5f, 0.5f,}, Color{255, 0, 0}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});
            cub.add({{-0.5f, 0.5f, 0.5f,}, Color{255, 0, 0}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}});
            cub.add({{-0.5f, 0.5f, -0.5f,}, Color{255, 0, 0}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}});
            cub.add({{-0.5f, -0.5f, -0.5f,}, Color{255, 0, 0}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}});
            cub.add({{-0.5f, -0.5f, -0.5f,}, Color{255, 0, 0}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}});
            cub.add({{-0.5f, -0.5f, 0.5f,}, Color{255, 0, 0}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}});
            cub.add({{-0.5f, 0.5f, 0.5f,}, Color{255, 0, 0}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}});
            cub.add({{0.5f, 0.5f, 0.5f,}, Color{255, 0, 0}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}});
            cub.add({{0.5f, 0.5f, -0.5f,}, Color{255, 0, 0}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}});
            cub.add({{0.5f, -0.5f, -0.5f,}, Color{255, 0, 0}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}});
            cub.add({{0.5f, -0.5f, -0.5f,}, Color{255, 0, 0}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}});
            cub.add({{0.5f, -0.5f, 0.5f,}, Color{255, 0, 0}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}});
            cub.add({{0.5f, 0.5f, 0.5f,}, Color{255, 0, 0}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}});
            cub.add({{-0.5f, -0.5f, -0.5f,}, Color{255, 0, 0}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}});
            cub.add({{0.5f, -0.5f, -0.5f,}, Color{255, 0, 0}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}});
            cub.add({{0.5f, -0.5f, 0.5f,}, Color{255, 0, 0}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}});
            cub.add({{0.5f, -0.5f, 0.5f,}, Color{255, 0, 0}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}});
            cub.add({{-0.5f, -0.5f, 0.5f,}, Color{255, 0, 0}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}});
            cub.add({{-0.5f, -0.5f, -0.5f,}, Color{255, 0, 0}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}});
            cub.add({{-0.5f, 0.5f, -0.5f,}, Color{255, 0, 0}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}});
            cub.add({{0.5f, 0.5f, -0.5f,}, Color{255, 0, 0}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}});
            cub.add({{0.5f, 0.5f, 0.5f,}, Color{255, 0, 0}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
            cub.add({{0.5f, 0.5f, 0.5f}, Color{255, 0, 0}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
            cub.add({{-0.5f, 0.5f, 0.5f}, Color{255, 0, 0}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
            cub.add({{-0.5f, 0.5f, -0.5f,}, Color{255, 0, 0}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}});

//

            // vertexShader.loadVF("Data\\Shaders\\Default.frag", "Data\\Shaders\\Default.vert");
            indexShader.loadVF("Data\\Shaders\\Index.frag", "Data\\Shaders\\Index.vert");
            light.loadVF("Data\\Shaders\\light.frag", "Data\\Shaders\\light.vert");
            ubo.create(sizeof(float[16]) * 3);

            _Shader test1("Data\\Shaders\\Default.frag", _Shader::FRAGMENT);
            _Shader test2("Data\\Shaders\\Default.vert", _Shader::VERTEX);
            p.createProgram();
            p.addShader(test1);
            p.addShader(test2);
            p.linkProgram();
            p.UBOBindingTo(p.getUBOIndex("matrixBuffer"), 0);
            ubo.bindToPoint(0);

            //vertexShader.UseUbo(ubo);
            indexShader.UseUbo(ubo);
            light.UseUbo(ubo);

            vao.create(cub.getSize());
            vbo.create(sizeof(Vertex) * cub.getSize());
            vbo.setData(&cub[0], sizeof(Vertex) * cub.getSize(), &cub[0].pos.x);
            vao.setPointers(vbo, sizeof(Vertex));

            test.load("Data\\model\\monkey.obj");
        }

        void run()
        {
            glfwSetTime(0);
            while(isRuning)
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
            EventManager::addEvent(KBoardEvent::KeyPressed(GLFW_KEY_GRAVE_ACCENT), [this](EventData e)
            {
                console_open = !console_open;
            });
            EventManager::addEvent(EventType::WINDOWCLOSE, [this](EventData e)
            {
                isRuning = false;
            });
            //w.init();
        }

        void render()
        {
            w.clear();
            //w.VAODraw(vao, p, ubo);
            w.VAODraw2(test, indexShader);
//            w.VAODraw3(vao, indexShader);
//            w.VAODtaw2(m, indexShader);
            //w.VAODraw2(vao, light, {-5.f, 0.f, -5.f});
            w.VAODraw3(vao, indexShader);
            //w.VAODtaw2(m, indexShader);
            w.VAODraw2(vao, light, {-5.f, 0.f, -5.f});
            //w.VAODraw2(vao, vertexShader, {10.f, 0.f, 10.f});
            //w.VAODtaw(m, indexShader);
            Console::Draw("Console", &console_open);
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
