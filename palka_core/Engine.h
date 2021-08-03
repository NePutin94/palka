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
#include "Context.h"
#include "Texture.h"
#include "Matrix.h"
#include "Sprite.h"
#include "ConsoleLog.h"
#include "DebugDraw.h"
#include "Transform.h"
#include "Viewport.h"
#include "ReflectionDebug.h"
#include "Window.h"

namespace palka
{
    class Engine
    {
    private:
        bool console_open = false;
        Window w;
        bool isRuning;
        Texture txt2;
        Sprite sp;
        Viewport v;
    public:
        Engine(Vec2i size) : w(size), isRuning(false), v({0, 0, static_cast<float>(size.x), static_cast<float>(size.y)})
        {
            init();
            txt2.LoadFromFile("Data\\tex\\debug.png");
            sp.setTexture(txt2, {0, 0, 330, 303});
            sp.setTextureRect({60,60,120, 120});
            sp.setPosition({0, 0});
            sp.setRotation(0);
            v.setCenter({w.getSize().x / 1.5f, w.getSize().y / 1.5f});
        }

        void run()
        {
            while (isRuning)
            {
                w.ImGUiNewFrame();
                handleEvents();
                update();
                render();
            }
        }

        static void setImGuiStyle()
        {
            ImGuiStyle* style = &ImGui::GetStyle();
            style->WindowRounding = 5.0f;
        }

        void init()
        {
            w.create();
            isRuning = true;
        }

        void render()
        {
            w.NewFrame();

            w.setViewport(v);
            DebugDraw::DrawSpriteDebug(sp);

            w.ImGUiEndFrame();
            w.EndFrame();
        }

        void update()
        {
            palka::draw(sp);
            palka::draw(v);
        }

        void handleEvents()
        {
            SDL_Event event;
            while (w.pollEvent(event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT)
                    isRuning = true;
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKQUOTE)
                    console_open = !console_open;
                if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
                    event.window.windowID == SDL_GetWindowID(this->w.getWindow()))
                    isRuning = true;
            }
        }
    };
}

#endif //PALKA_ENGINE_H
