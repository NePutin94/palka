//
// Created by NePutin on 7/25/2021.
//

#ifndef PALKA_WINDOW_H
#define PALKA_WINDOW_H


#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "Vec2.h"
#include "Color.h"
#include "Drawable.h"
#include "Viewport.h"
#include "ConsoleLog.h"
#include "EventManager.h"

namespace palka
{
    class Window
    {
    private:
        Vec2i size;
        GLFWwindow* window;
        Viewport* view;
        ImGuiIO* io;
        Color bg_color{80, 180, 250};
        EventManager eManager;

    public:

        Window(const Vec2i& size) : size(size)
        {}

        ~Window()
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            glfwDestroyWindow(window);
            glfwTerminate();
        }

        void initImgui()
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            (void) io;
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

            // Setup Dear ImGui style
            ImGui::StyleColorsDark();
            //ImGui::StyleColorsClassic();

            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 130");
        }

        void create()
        {
            glfwInit();

            const char* glsl_version = "#version 130";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac

            window = glfwCreateWindow(1280, 720, "palka", NULL, NULL);

            glfwMakeContextCurrent(window);
            initImgui();

            EventManager::bindEvents(window);
            EventManager::addEvent(WINDOWRESIZE, [this](EventData e) {

                size.x = e.WindowResize.newX;
                size.y = e.WindowResize.newY;
                Console::AppLog::addLog_("Window resized new size is w: %i h: %i", Console::info, size.x, size.y);
            });
        }

        void setViewport(Viewport& v)
        {
            if (view != &v)
                view = &v;
        }

        Viewport* getViewport()
        {
            return view;
        }

        GLFWwindow* getWindow()
        {
            return window;
        }

        auto getSize()
        {
            return size;
        }

        void draw(const Drawable& d)
        {
            d.draw(*this);
        }

        void ImGUiNewFrame()
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void ImGuiEndFrame()
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        void NewFrame()
        {
            glViewport(0, 0, 1280, 720);
            glClearColor(0, 120, 120, 255);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void EndFrame()
        {
            glfwSwapBuffers(window);
        }

        EventManager& getEManager()
        {
            return eManager;
        }

        void inputHandler()
        {
            //eManager.updateInput();
        }

        void eventHandler()
        {
            glfwPollEvents();
        }

    };
}
#endif //PALKA_WINDOW_H
