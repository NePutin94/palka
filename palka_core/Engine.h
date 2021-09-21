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
#include "Sprite.h"
#include "RenderTexture.h"
#include "Rectangle.h"
#include "DebugDraw.h"


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
    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false), view(RectF(0, 0, size.x, size.y)), p({0, 0, 180, 180}, 5)
        {
            init();
            p.setColor(Color{250, 0, 50, 255});
            p.setPosition({10, 0});
            tex.LoadFromFile("Data\\tex\\Debug.png");
            test.setTexture(tex);
            w.getViewport().setCenter({1280.f / 2, 720.f / 2});

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
//            RectF rect{0, 0, 120, 120};
//            Vec2f bary;
//            static float sz = 2;
//            ImGui::DragFloat("sz", &sz);
//            VertArray vertices(VertArray::Quads);
//            vertices.add(Vec2f{rect.left, rect.top});
//            vertices.add(Vec2f{rect.w, rect.top});
//            vertices.add(Vec2f{rect.w, rect.h});
//            vertices.add(Vec2f{rect.left, rect.h});
//
//            VertArray vertices2(VertArray::Triangle_Strip);
//            for (int i = 0; i < 4; ++i)
//            {
//                Vec2f a = (i == 0) ? vertices[3].pos : vertices[i - 1].pos;
//                Vec2f b = vertices[i].pos;
//                Vec2f c = (i == 3) ? vertices[0].pos : vertices[i + 1].pos;
//
//                Vec2f normal = (b-a).normalize();
//                Vec2f normal2 = (b-c).normalize();
//
//                float len = 1.f + (normal * normal2).lenght();
//                Vec2f dir = (normal + normal2) / len;
//                Vec2f t = b + dir * sz;
//                //vertices2.add({b + normal * sz, Color{255, 0, 0}});
//                //vertices2.add({b + normal2 * sz, Color{255, 0, 0}});
//                vertices2.add({b, Color{255, 0, 0}});
//                vertices2.add({b + dir * sz, Color{100, 200, 90}});
//            }
//
//            vertices2.add(vertices2[0]);
//            vertices2.add(vertices2[1]);
//
//            glPointSize(8);
//            w.draw(vertices2);
//            //w.draw(vertices);
//            glPointSize(1);
            //DebugDraw::DrawSpriteDebug(test, w);
            w.draw(p);
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
