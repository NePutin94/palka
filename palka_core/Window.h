//
// Created by NePutin on 7/25/2021.
//

#ifndef PALKA_WINDOW_H
#define PALKA_WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <glad/glad.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <GL/gl.h>
#include "Vec2.h"
#include "Drawable.h"
#include "Viewport.h"
#include "ConsoleLog.h"
#include "Context.h"

namespace palka
{
    class Window
    {
    private:
        Vec2i size;
        SDL_Window* window;
        Viewport* view;
        ImGuiIO* io;
        SDL_GLContext gl_context;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    public:
        Window(const Vec2i& size) : size(size)
        {
        }

        ~Window()
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();

            SDL_GL_DeleteContext(gl_context);
            SDL_DestroyWindow(getWindow());
            SDL_Quit();
        }

        void initImgui()
        {
            gl_context = SDL_GL_CreateContext(getWindow());
            SDL_GL_MakeCurrent(getWindow(), gl_context);
            SDL_GL_SetSwapInterval(1); // Enable vsync
            bool err = gladLoadGL() == 0;

            if (err)
                fprintf(stderr, "Failed to initialize OpenGL loader!\n");

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            io = &ImGui::GetIO();
            ImGui::StyleColorsDark();

            const char* glsl_version = "#version 130";
            ImGui_ImplSDL2_InitForOpenGL(getWindow(), gl_context);
            ImGui_ImplOpenGL3_Init(glsl_version);
        }

        void create()
        {
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
                printf("Error: %s\n", SDL_GetError());
            SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

            SDL_WindowFlags window_flags = (SDL_WindowFlags) (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                                                              SDL_WINDOW_ALLOW_HIGHDPI);
            window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      size.x, size.y,
                                      window_flags);

            initImgui();

            SDL_Renderer* renderer = SDL_CreateRenderer(getWindow(), -1, SDL_RENDERER_ACCELERATED);
            SDL_RendererInfo info;
            SDL_GetRendererInfo(renderer, &info);
            Context::SetContext(renderer);
        }

        void setViewport(Viewport& v)
        {
            // if (view != &v)
            view = &v;
        }

        SDL_Window* getWindow()
        {
            return window;
        }

        auto getSize()
        {
            return size;
        }

        void draw(const Drawable& d)
        {
            glViewport(0, 0, getSize().x, getSize().y);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glLoadMatrixf(view->getView().getMatrix());
            glMatrixMode(GL_MODELVIEW);
            d.draw(Context::GetContext());
        }

        void ImGUiNewFrame()
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame(window);
            ImGui::NewFrame();
        }

        void ImGUiEndFrame()
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        }

        void NewFrame()
        {
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void EndFrame()
        {
            SDL_GL_SwapWindow(getWindow());
        }

        bool pollEvent(SDL_Event& e)
        {
            if (SDL_PollEvent(&e))
            {
                if (e.type == SDL_WINDOWEVENT &&
                    e.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    size.x = e.window.data1;
                    size.y = e.window.data2;
                    Console::AppLog::addLog_("Window resized new size is w: %i h: %i", Console::info, size.x, size.y);
                }
                return true;
            }
            return false;
        }
    };
}
#endif //PALKA_WINDOW_H
