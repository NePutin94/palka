//
// Created by NePutin on 6/23/2021.
//

#ifndef PALKA_ENGINE_H
#define PALKA_ENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <glad/glad.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <GL/gl.h>
#include <string>
#include "config.h"
#include "Vec2.h"
#include "Texture.h"
#include "Matrix.h"
#include "Sprite.h"
#include "ConsoleLog.h"
#include "DebugDraw.h"
#include "Transform.h"
#include "Viewport.h"
#include "ReflectionDebug.h"
#include "Window.h"
#include "../palka_entities/Object.h"
#include "EventManager.h"

namespace palka
{
    class Engine
    {
    private:
        bool console_open = false;
        Window w;
        bool isRuning;
        Viewport v;
        std::shared_ptr<Object> o;
        DebugDraw deb_draw;
        Vec2f p[4] = {{150, 150},
                      {200, 200},
                      {250, 250},
                      {300, 300}};
    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false), v({0, 0, static_cast<float>(size.x), static_cast<float>(size.y)}),
                                      o(std::make_shared<Object>("test"))
        {
            init();
            Texture test;
            test.LoadFromFile("Data\\tex\\Hero.png", w);
            o->setTexture(std::move(test), {18, 26, 29, 38});
            w.setViewport(v);
            static bool mousePress = false;
            static int selectIndex = -1;
            w.getEManager().addEvent(MouseEvent::Motion(), [this](SDL_Event& event) {
                float x = event.motion.x;
                float y = event.motion.y;
                if (mousePress)
                {
                    if(selectIndex > 0)
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
            w.getEManager().addEvent(MouseEvent::ButtonPressed(MouseEvent::Left), [this](SDL_Event& event) {
                mousePress = true;
            });
            w.getEManager().addEvent(MouseEvent::ButtonReleased(MouseEvent::Left), [this](SDL_Event& event) {
                mousePress = false;
                selectIndex = -1;
            });
        }

        void run()
        {
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
            isRuning = true;
        }

        float getPt(float n1, float n2, float perc)
        {
            float diff = n2 - n1;

            return n1 + (diff * perc);
        }

        void render()
        {
            w.NewFrame();
            SDL_FPoint pointsX[100];
            int i = 0;
            for (auto u = 0.0; u <= 1.0; u += 0.01)
            {
                // The Green Lines
                float xu = pow(1 - u, 3) * p[0].x + 3 * u * pow(1 - u, 2) * p[1].x + 3 * pow(u, 2) * (1 - u) * p[2].x
                           + pow(u, 3) * p[3].x;
                float yu = pow(1 - u, 3) * p[0].y + 3 * u * pow(1 - u, 2) * p[1].y + 3 * pow(u, 2) * (1 - u) * p[2].y
                           + pow(u, 3) * p[3].y;
                pointsX[i++] = {xu, yu};
                SDL_SetRenderDrawColor(w.getContext(), 255, 120, 120, 255);
            }
            SDL_RenderDrawLinesF(w.getContext(), pointsX, 100);

            SDL_SetRenderDrawColor(w.getContext(), 255, 0, 120, 255);
            for (auto& point: p)
            {
                Vec2f np1 = point - 5;
                DebugDraw::DrawBoxF(RectF(np1.x, np1.y, 10, 10), w.getContext());
            }

            DebugDraw::DrawSpriteDebug(o->sprite, w);
            Console::AppLog::Draw("Console", &console_open);
            w.ImGuiEndFrame();
            w.EndFrame();
        }

        void update()
        {
            palka::debug(o, o->getName());
            palka::debug(v, "Viewport");
            palka::debug(deb_draw, "DebugDraw");
            w.inputHandler();
        }

        void handleEvents()
        {
            SDL_Event event;
            w.eventHandler(event);
        }
    };
}

#endif //PALKA_ENGINE_H
