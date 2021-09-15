//
// Created by NePutin on 7/25/2021.
//

#ifndef PALKA_WINDOW_H
#define PALKA_WINDOW_H

#include <glew.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>


#include "Vec2.h"
#include "Color.h"
#include "Viewport.h"
#include "ConsoleLog.h"
#include "EventManager.h"
#include "RenderContext.h"
#include "VertexData.h"
#include "Renderer.h"

namespace palka
{
    class Window : public Renderer
    {
    private:
        Vec2i size;
        GLFWwindow* window;
        //Viewport* view;
        ImGuiIO* io;
        Color bg_color{80, 180, 250};
        EventManager eManager;

    public:
        static void error_callback(int error, const char* description)
        {
            Console::AppLog::addLog_("Error: %s", Console::error, description);
        }

        Window(const Vec2i& size) : Renderer(size), size(size)
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

            ImGui::StyleColorsDark();
            //ImGui::StyleColorsClassic();

            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 130");
        }

        void create()
        {
            if (!glfwInit())
                Console::AppLog::addLog("Failed to initialize GLFW", Console::fatal);
            glfwSetErrorCallback(error_callback);
            glfwDefaultWindowHints();
            window = glfwCreateWindow(1280, 720, "palka", NULL, NULL);
            if (!window)
                Console::AppLog::addLog("Failed to open GLFW window", Console::fatal);

            glfwMakeContextCurrent(window);
            glfwSwapInterval(0);
            glewExperimental = GL_TRUE;
            GLenum err = glewInit();
            if (GLEW_OK != err)
            {
                std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
                glfwTerminate();
            }
            Console::AppLog::addLog_("GL_VERSION: %s", Console::info, glGetString(GL_VERSION));
            initImgui();
            EventManager::bindEvents(window);
            EventManager::addEvent(WINDOWRESIZE, [this](EventData e) {

                size.x = e.WindowResize.newX;
                size.y = e.WindowResize.newY;
                Console::AppLog::addLog_("Window resized new size is w: %i h: %i", Console::info, size.x, size.y);
            });
        }

//        void setViewport(Viewport& v)
//        {
//            if (view != &v)
//                view = &v;
//        }
//
//        Viewport* getViewport()
//        {
//            return view;
//        }

        GLFWwindow* getWindow()
        {
            return window;
        }

        auto getSize()
        {
            return size;
        }

//        void draw(const Drawable& d)
//        {
//            //d.draw(*this);
//        }
//
//        void draw(VertArray array, RenderContext context = {})
//        {
//            glMatrixMode(GL_PROJECTION);
//            glLoadIdentity();
//            glMatrixMode(GL_MODELVIEW);
//            glLoadIdentity();
//            glEnable(GL_TEXTURE_2D);
//            glEnable(GL_BLEND);
//            context.texture->bind();
//            glBlendFuncSeparate(
//                    BlendMode::enumToGlConstant(context.blend.colorSrcFactor), BlendMode::enumToGlConstant(context.blend.colorDstFactor),
//                    BlendMode::enumToGlConstant(context.blend.alphaSrcFactor), BlendMode::enumToGlConstant(context.blend.alphaDstFactor));
//            glBlendEquationSeparate(
//                    BlendMode::enumToGlConstant(context.blend.colorEquation),
//                    BlendMode::enumToGlConstant(context.blend.alphaEquation));
//            glEnableClientState(GL_VERTEX_ARRAY);
//            glEnableClientState(GL_COLOR_ARRAY);
//            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//            glLoadMatrixf(context.transform.getMatrix());
//            applyView();
//
//            Vertex* pointer = &array[0];
//
//            glVertexPointer(2,
//                            GL_FLOAT,
//                            sizeof(Vertex),
//                            &pointer->pos.x);
//
//            glColorPointer(3,
//                           GL_UNSIGNED_BYTE,
//                           sizeof(Vertex),
//                           &pointer->color.r);
//
//            glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &pointer->texCoord.x);
//
//            glDrawArrays(VertArray::type_to_gl(array.getType()), static_cast<GLint>(0), array.getSize());
//
//            glDisableClientState(GL_COLOR_ARRAY);
//            glDisableClientState(GL_VERTEX_ARRAY);
//            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//            glDisable(GL_BLEND);
//            glDisable(GL_TEXTURE_2D);
//        }

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

//        void applyView()
//        {
//            glViewport(0, 0, 1280, 720);
//            glMatrixMode(GL_PROJECTION);
//            glLoadMatrixf(view->getView().getMatrix());
//            glMatrixMode(GL_MODELVIEW);
//            //glLoadIdentity();
//        }

        void NewFrame()
        {
            glClearColor(0, 120, 120, 255);
            glClear(GL_COLOR_BUFFER_BIT);
            applyView();
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
