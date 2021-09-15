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
        Vec2f p[4] = {{150, 150},
                      {200, 200},
                      {250, 250},
                      {300, 300}};
        Texture renderTex;
    public:
        explicit Engine(Vec2i size) : w( size), isRuning(false), view(RectF(0, 0, size.x, size.y)), vert(VertArray::Type::Quads)
        {
            init();
            int x, y, n;
            tex.LoadFromFile("Data\\tex\\Debug.png");
            test.setTexture(tex);
            view.setCenter({1280.f / 2, 720.f / 2});

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
            });
            EventManager::addEvent(MouseEvent::ButtonPressed(MouseEvent::Left), [](EventData& event) {
                mousePress = true;
            });
            EventManager::addEvent(MouseEvent::ButtonReleased(MouseEvent::Left), [](EventData& event) {
                mousePress = false;
                selectIndex = -1;
            });
            renderTex.empty({500, 500});
            texRedner();
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

        GLuint fbo, texture;

        void texRedner()
        {
            glGenFramebuffers(1, &fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTex.textureID, 0);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void render()
        {
            w.NewFrame();
            static Vec2f pos{500/2.f, 500/2.f};
            Viewport v{{0,0,500,500}};
            v.setCenter(pos);
            ImGui::DragFloat("x", &pos.x);
            ImGui::DragFloat("y", &pos.y);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            glViewport(0, 0, 500, 500);
            glClearColor(255, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glLoadMatrixf(v.getView().getMatrix());
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glColor3f(255, 255, 255);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, tex.textureID);
            glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(0,0);
            glTexCoord2f(1, 0); glVertex2f(100,0);
            glTexCoord2f(1, 1); glVertex2f(100,100);
            glTexCoord2f(0, 1); glVertex2f(0,100);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
//            glColor3f(0, 255, 0);
//            glBegin(GL_QUADS);
//            glVertex2f(50, 50);
//            glVertex2f(70, 50);
//            glVertex2f(70, 70);
//            glVertex2f(50, 70);
//            glEnd();
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

//            VertArray q(VertArray::Quads);
//            q.add({{0, 0},
//                   {0, 0}});
//            q.add({{200, 0},
//                   {1,   0}});
//            q.add({{200, 200},
//                   {1,   1}});
//            q.add({{0, 200},
//                   {0, 1}});

            Sprite s;
            s.setTexture(renderTex);
            w.draw(s);
            //w.draw(test);
//            VertArray line(VertArray::Line_Strip);
//            int i = 0;
//            for (auto u = 0.0; u <= 1.0; u += 0.01)
//            {
//                // The Green Lines
//                float xu = pow(1 - u, 3) * p[0].x + 3 * u * pow(1 - u, 2) * p[1].x + 3 * pow(u, 2) * (1 - u) * p[2].x
//                           + pow(u, 3) * p[3].x;
//                float yu = pow(1 - u, 3) * p[0].y + 3 * u * pow(1 - u, 2) * p[1].y + 3 * pow(u, 2) * (1 - u) * p[2].y
//                           + pow(u, 3) * p[3].y;
//                line.add({{xu, yu}});
//
//            }
//            RenderContext c;
//            w.draw(line, c);
//            VertArray points(VertArray::Points);
//            for (auto& point: p)
//            {
//                Vec2f np1 = point - 5;
//                points.add(Vertex(point, Color(255,0,0)));
//
//            }
//            glPointSize(8);
//            w.draw(points, c);
//            glPointSize(1);
            //

            Console::AppLog::Draw("Console", &console_open);
            w.ImGuiEndFrame();
            w.EndFrame();
        }

        void update()
        {
            debug(test, "sprite");
            debug(view, "view");
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
