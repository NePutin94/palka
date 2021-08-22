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

    public:
        explicit Engine(Vec2i size) : w(size), isRuning(false), v({0, 0, static_cast<float>(size.x), static_cast<float>(size.y)}), o(std::make_shared<Object>("test"))
        {
            init();
            Texture test;
            test.LoadFromFile("Data\\tex\\Hero.png");
            o->setTexture(std::move(test), {18, 26, 29, 38});
            //o->setPosition({0, 0});
            w.setViewport(v);
            w.getEManager().addInput(SDLK_t, []()
            {
                Console::AppLog::addLog("key press", Console::info);
            });
            w.getEManager().addInput(SDLK_BACKQUOTE, [this]()
            {
                console_open = !console_open;
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
            w.inputHandler();


        }

        void handleEvents()
        {
            SDL_Event event;
            w.eventHandler(event);

//            while (w.pollEvent(event))
//            {
//                if (event.type == SDL_QUIT)
//                    isRuning = false;
//                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKQUOTE)
//
//                tets.updateEvent(event);
//            }
        }
    };
}

#endif //PALKA_ENGINE_H
