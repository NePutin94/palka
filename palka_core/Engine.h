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
    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false), v({0, 0, static_cast<float>(size.x), static_cast<float>(size.y)}), o(std::make_shared<Object>("test"))
        {
            init();
            Texture test;
            test.LoadFromFile("Data\\tex\\Hero.png");
            //txt2 = std::move(test);
            //sp.setTexture(txt2, {18, 26, 29, 38});
            // sp.setTextureRect({18, 20, 29, 38});
            //sp.setPosition({0, 0});
            //sp.setRotation(0);
            o->setTexture(std::move(test), {18, 26, 29, 38});
            o->setPosition({0, 0});
           // v.setCenter({w.getSize().x / 2.f, w.getSize().y / 2.f});
            w.setViewport(v);
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

        void render()
        {
            w.NewFrame();
            DebugDraw::DrawSpriteDebug(o->sprite, w);
            Console::AppLog::Draw("Console", &console_open);
            w.ImGUiEndFrame();
            w.EndFrame();
        }

        void update()
        {
            palka::debug(o, o->getName());
            //palka::debug(v);
            //palka::debug(DebugDraw());
        }

        void handleEvents()
        {
            SDL_Event event;
            while (w.pollEvent(event))
            {
                if (event.type == SDL_QUIT)
                    isRuning = false;
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKQUOTE)
                    console_open = !console_open;
            }
        }
    };
}

#endif //PALKA_ENGINE_H
