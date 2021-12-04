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
        // Shader indexShader;
        // Shader light;
        VertexBufferObject vbo;
        VertexArrayObject vao;
        UniformBuffer ubo;

        StaticMesh m;
        ShaderProgram p;
        ShaderProgram light;
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
            // indexShader.loadVF("Data\\Shaders\\Index.frag", "Data\\Shaders\\Index.vert");
            // light.loadVF("Data\\Shaders\\light.frag", "Data\\Shaders\\light.vert");
            ubo.create(sizeof(float[16]) * 3);

            _Shader test1("Data\\Shaders\\Index.frag", _Shader::FRAGMENT);
            _Shader test2("Data\\Shaders\\Index.vert", _Shader::VERTEX);
            p.createProgram();
            p.addShader(test1);
            p.addShader(test2);
            p.linkProgram();
            p.UBOBindingTo(p.getUBOIndex("matrixBuffer"), 0);
            ubo.bindToPoint(0);

            _Shader l1("Data\\Shaders\\light.frag", _Shader::FRAGMENT);
            _Shader l2("Data\\Shaders\\light.vert", _Shader::VERTEX);


            light.createProgram();
            light.addShader(l1);
            light.addShader(l2);
            light.linkProgram();
            light.UBOBindingTo(p.getUBOIndex("matrixBuffer"), 0);
            ubo.bindToPoint(0);

            //vertexShader.UseUbo(ubo);
            //  indexShader.UseUbo(ubo);
            //  light.UseUbo(ubo);

            vao.create(cub.getSize());
            vbo.create(sizeof(Vertex) * cub.getSize());
            vbo.setData(sizeof(Vertex) * cub.getSize(), &cub[0].pos.x);
            vao.setPointers(vbo, sizeof(Vertex));

            test.load("Data\\model\\untitled.obj");
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
            Mat4f model = Mat4f{1.f};
            model = glm::translate(model, {0, 0, 0});
            model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.0f, 0, 0.f));
            RenderContext context1(&p, &ubo, model);
            w.draw(test, context1);

            Mat4f model2 = Mat4f{1.f};
            model2 = glm::translate(model, {0, -10, 0});
            context1.model_mat = model2;
            static Vec3f lp = {-5.f, 0.f, -5.f};
            Mat4f lightPos = Mat4f{1.f};
            ImGui::DragFloat("x", &lp.x);
            ImGui::DragFloat("y", &lp.y);
            ImGui::DragFloat("z", &lp.z);
            lightPos = glm::translate(model, lp);

            w.draw(vao, context1, lp);
            Mat4f model3 = Mat4f{1.f};
            model3 = glm::translate(model, {0, -10, -10});
            context1.model_mat = model3;
            w.draw(m, context1, lp);

            RenderContext context2(&light, &ubo, lightPos);
            w.draw(vao, context2, lp);

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
