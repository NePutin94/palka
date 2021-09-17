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
        VertArray vert;
        Vec2f p[7] = {{50,  50},
                      {100, 100},
                      {150, 150},
                      {200, 200},

                      {250, 250},
                      {300, 300},
                      {350, 350}};

        RenderTexture renderTex;
        Sprite renderSp;
    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false), view(RectF(0, 0, size.x, size.y)), vert(VertArray::Type::Quads)
        {
            init();

            tex.LoadFromFile("Data\\tex\\Debug.png");
            test.setTexture(tex);
            w.getViewport().setCenter({1280.f / 2, 720.f / 2});

            s.load("Data\\Shaders\\test.frag");
            vert.add({Vec2f{100, 100}, Color::White(), Vec2f{0, 0}});
            vert.add({Vec2f{200, 100}, Color::White(), Vec2f{1, 0}});
            vert.add({Vec2f{200, 200}, Color::White(), Vec2f{1, 1}});
            vert.add({Vec2f{100, 200}, Color::White(), Vec2f{0, 1}});

            static bool mousePress = false;
            static int selectIndex = -1;
            EventManager::addEvent(MouseEvent::Motion(), [this](EventData& event) {
                float x = event.MouseMotion.x;
                float y = event.MouseMotion.y;
                if (mousePress)
                {
                    if (selectIndex > 0)
                        p[selectIndex] = Vec2f{x, y};
                    else
                    {
                        int i = 0;
                        for (auto& point: p)
                        {
                            Vec2f np1 = point - 5;
                            if (RectF(np1.x, np1.y, 10, 10).contains(Vec2f(x, y)))
                            {
                                point = Vec2f{x, y};
                                selectIndex = i;
                                break;
                            }
                            i++;
                        }
                    }
                }
            });
            EventManager::addEvent(MouseEvent::ButtonPressed(MouseEvent::Left), [](EventData& event) {
                mousePress = true;
                Console::AppLog::addLog("mousePress", Console::info);
            });
            EventManager::addEvent(MouseEvent::ButtonReleased(MouseEvent::Left), [](EventData& event) {
                mousePress = false;
                Console::AppLog::addLog("mousePress false", Console::info);
                selectIndex = -1;
            });
            renderTex.create({500, 500});
            renderTex.getViewport().setCenter({500 / 2.f, 500 / 2.f});
            renderSp.setTexture(renderTex.getTexture());
            renderSp.setPosition({500, 0});
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
        }

        void render()
        {
            w.clear();
            //MaskTexture();
            //w.draw(test);
            RenderTexture mask;
            mask.create({500, 500});
            mask.getViewport().setCenter({500 / 2.f, 500 / 2.f});

            VertArray line(VertArray::Triangle_Fan);
            int i = 0;
            for (auto u = 0.0; u <= 1.0; u += 0.01)
            {
                float xu = pow(1 - u, 3) * p[0].x + 3 * u * pow(1 - u, 2) * p[1].x + 3 * pow(u, 2) * (1 - u) * p[2].x
                           + pow(u, 3) * p[3].x;
                float yu = pow(1 - u, 3) * p[0].y + 3 * u * pow(1 - u, 2) * p[1].y + 3 * pow(u, 2) * (1 - u) * p[2].y
                           + pow(u, 3) * p[3].y;
                line.add({{xu, yu}});

            }
            for (auto u = 0.0; u <= 1.0; u += 0.01)
            {
                float xu = pow(1 - u, 3) * p[3].x + 3 * u * pow(1 - u, 2) * p[4].x + 3 * pow(u, 2) * (1 - u) * p[5].x
                           + pow(u, 3) * p[6].x;
                float yu = pow(1 - u, 3) * p[3].y + 3 * u * pow(1 - u, 2) * p[4].y + 3 * pow(u, 2) * (1 - u) * p[5].y
                           + pow(u, 3) * p[6].y;
                line.add({{xu, yu}});
            }

            mask.bind();
            mask.clear(Color(0, 0, 0, 0));
            mask.draw(line);
            mask.unbind();
            renderTex.bind();
            renderTex.clear(Color(0, 0, 0, 0));
            renderTex.draw(test);
            Sprite s2;
            s2.setTexture(mask.getTexture());
            renderTex.draw(s2, BlendMode(BlendMode::ONE, BlendMode::ONE, BlendMode::Add,
                                         BlendMode::ZERO, BlendMode::ONE_MINUS_SRC_ALPHA, BlendMode::Add));
            renderTex.unbind();

            w.draw(test);
            w.draw(renderSp);
            w.draw(line);

            VertArray points(VertArray::Points);
            for (auto& point: p)
            {
                points.add(Vertex(point, Color(255, 0, 0)));
            }
            glPointSize(8);
            RenderContext c;
            c.blend = BlendMode::BlendAdd();
            w.draw(points);
            glPointSize(1);

            Console::AppLog::Draw("Console", &console_open);
            w.ImGuiEndFrame();
            w.EndFrame();
        }

        void update()
        {
            debug(renderTex.getViewport(), "view234");
            debug(w.getViewport(), "view");
            debug(test, "test");
            debug(renderSp, "renderSp");
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
