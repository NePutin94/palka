#include <algorithm>
#include "Vec2.h"
#include "Engine.h"
#include "Transform.h"
#include "ReflectionDebug.h"
#include "Test.h"
#include <chrono>
using namespace std;
int main(int argc, char* argv[])
{
    TTF_Init();
    palka::Engine e(palka::Vec2(1280, 720));
    e.run();
    TTF_Quit();
    return 0;
}

//#include "imgui.h"
//#include "imgui_impl_sdl.h"
//#include "imgui_impl_opengl3.h"
//#include <stdio.h>
//#include <SDL.h>
//#include <glad/glad.h>          // Initialize with gladLoadGL()
//#include <SDL_image.h>
//
//
//// Main code
//int main(int, char**)
//{
//    // Setup SDL
//    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
//    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
//    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
//    {
//        printf("Error: %s\n", SDL_GetError());
//        return -1;
//    }
//    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
//
//    const char* glsl_version = "#version 130";
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
//
//    // Create window with graphics context
//    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
//    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
//    SDL_WindowFlags window_flags = (SDL_WindowFlags) (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
//    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720,
//                                          window_flags);
//    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
//    SDL_GL_MakeCurrent(window, gl_context);
//    SDL_GL_SetSwapInterval(1); // Enable vsync
//    bool err = gladLoadGL() == 0;
//
//    if(err)
//    {
//        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
//        return 1;
//    }
//
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO();
//    //(void) io;
//    ImGui::StyleColorsDark();
//    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
//    ImGui_ImplOpenGL3_Init(glsl_version);
//
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    SDL_RendererInfo info;
//    SDL_GetRendererInfo(renderer, &info);
//    printf("%s", info.name);
//
//    bool show_demo_window = true;
//    bool show_another_window = false;
//    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//    auto txt = IMG_LoadTexture(renderer, "Data\\tex\\test.png");
//
//    bool done = false;
//    while(!done)
//    {
//        SDL_Event event;
//        while(SDL_PollEvent(&event))
//        {
//            ImGui_ImplSDL2_ProcessEvent(&event);
//            if(event.type == SDL_QUIT)
//                done = true;
//            if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
//               event.window.windowID == SDL_GetWindowID(window))
//                done = true;
//        }
//
//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplSDL2_NewFrame(window);
//        ImGui::NewFrame();
//
//        if(show_demo_window)
//            ImGui::ShowDemoWindow(&show_demo_window);
//
//        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
//        {
//            static float f = 0.0f;
//            static int counter = 0;
//
//            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//            ImGui::Checkbox("Another Window", &show_another_window);
//
//            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//            ImGui::ColorEdit3("clear color", (float*) &clear_color); // Edit 3 floats representing a color
//
//            if(ImGui::Button(
//                    "Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//                counter++;
//            ImGui::SameLine();
//            ImGui::Text("counter = %d", counter);
//
//            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//            ImGui::End();
//        }
//
//        ImGui::Render();
//        glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
//        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        SDL_Rect rct2;
//        rct2.x = rct2.y = 200;
//        rct2.w = rct2.h = 400;
//        SDL_RenderCopy(renderer, txt, 0, &rct2);
//
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//        SDL_GL_SwapWindow(window);
//    }
//
//    // Cleanup
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplSDL2_Shutdown();
//    ImGui::DestroyContext();
//
//    SDL_GL_DeleteContext(gl_context);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}


