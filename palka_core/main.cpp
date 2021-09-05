//
//#include <glew.h>
//#include <SDL_image.h>
//#include <SDL.h>
//
//SDL_Surface *texture;
//GLuint textureID=0;
//void close(GLuint gProgramID, SDL_Window* window);
//
//bool initGL(GLuint* gProgramID, GLint* gVertexPos2DLocation, GLuint* gVBO, GLuint* gIBO);
//
//void printProgramLog(GLuint program);
//
//void printShaderLog(GLuint shader);
//
//void render(GLuint* gProgramID, GLint* gVertexPos2DLocation, GLuint* gVBO, GLuint* gIBO);
//
//
//void close(GLuint gProgramID, SDL_Window* window)
//{
//    //Deallocate program
//    glDeleteProgram(gProgramID);
//
//    //Destroy window
//    SDL_DestroyWindow(window);
//    window = NULL;
//
//    //Quit SDL subsystems
//    SDL_Quit();
//}
//
//bool initGL(GLuint* gProgramID)
//{
//    *gProgramID = glCreateProgram();
//}
//
//
//void render(GLuint* gProgramID)
//{
//    //Clear color buffer
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    //Bind program
//    glUseProgram(*gProgramID);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    GLfloat Vertices[] = {(float)0, (float)0, 0,
//                          (float)100, (float)0, 0,
//                          (float)100, (float)100, 0,
//                          (float)0, (float)100, 0};
//    GLfloat TexCoord[] = {0, 0,
//                          1, 0,
//                          1, 1,
//                          0, 1,
//    };
//    GLubyte indices[] = {0,1,2, // first triangle (bottom left - top left - top right)
//                         0,2,3}; // second triangle (bottom left - top right - bottom right)
//
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, Vertices);
//
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//    glTexCoordPointer(2, GL_FLOAT, 0, TexCoord);
//
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
//
//    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//    glDisableClientState(GL_VERTEX_ARRAY);
//
//    //Unbind program
//    glUseProgram(NULL);
//}
//
//int main(int argc, char* argv[])
//{
//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
//    {
//        printf("SDL_Init error: %s\n", SDL_GetError());
//    }
//    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//
//    SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
//
//
//    SDL_GLContext context = SDL_GL_CreateContext(window);
//
//    if (context == NULL)
//    {
//        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
//        return 1;
//    }
//    GLuint gProgramID;
//    glewExperimental = GL_TRUE;
//    GLenum glewError = glewInit();
//
//    if (glewError != GLEW_OK)
//    {
//        printf("Error initializing glew! %s\n", glewGetErrorString(glewError));
//        return 1;
//    }
//
//    if (SDL_GL_SetSwapInterval(1) < 0)
//    {
//        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
//    }
//
//    //Initialize OpenGL
//    if (!initGL(&gProgramID))
//    {
//        printf("Unable to initialize OpenGL!\n");
//        return 1;
//    }
//
//    bool quit = false;
//
//    SDL_Event e;
//
//    texture=IMG_Load("Data\\tex\\Hero.png");
//
//
//    GLenum textureFormat;
//    /* Find out pixel format type */
//    auto bpp = texture->format->BytesPerPixel;
//    if (bpp == 4) {
//        if (texture->format->Rmask == 0x000000ff)
//            textureFormat = GL_RGBA;
//        else
//            textureFormat = GL_BGRA;
//    } else if (bpp == 3) {
//        if (texture->format->Rmask == 0x000000ff)
//            textureFormat = GL_RGB;
//        else
//            textureFormat = GL_BGR;
//    } else {
//
//    }
//    glGenTextures(1, &textureID);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
//    glTexImage2D(
//            GL_TEXTURE_2D,                  // texture type
//            0,                              // level
//            bpp,                            // internal format
//            texture->w,                       // width
//            texture->h,                       // height
//            0,                              // border
//            textureFormat,                  // format(in this texture?)
//            GL_UNSIGNED_BYTE,               // data type
//            texture->pixels                   // pointer to data
//    );
//    auto err = SDL_GetError();
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glDisable(GL_TEXTURE_2D);
//    SDL_FreeSurface(texture);
//    while (!quit)
//    {
//        while (SDL_PollEvent(&e) != 0)
//        {
//            if (e.type == SDL_QUIT)
//            {
//                quit = true;
//            }
//
//            if (e.type == SDL_KEYDOWN)
//            {
//                SDL_Keycode keyPressed = e.key.keysym.sym;
//
//                switch (keyPressed)
//                {
//                    case SDLK_ESCAPE:
//                        quit = true;
//                        break;
//                }
//            }
//        }
//
//        render(&gProgramID);
//
//        SDL_GL_SwapWindow(window);
//    }
//
//    SDL_StopTextInput();
//    close(gProgramID, window);
//
//    return 0;
//}
#include <algorithm>
#include "Vec2.h"
#include "Engine.h"

using namespace std;

int main(int argc, char* argv[])
{
    palka::Engine e(palka::Vec2(1280, 720));
    e.run();
    return 0;
}

//#include "imgui.h"
//#include "imgui_impl_sdl.h"
//#include "imgui_impl_opengl3.h"
//#include <stdio.h>
//#include <SDL.h>
//#include <SDL_main.h>
//#include <glad/glad.h>          // Initialize with gladLoadGL()
//#include <SDL_image.h>
//#include "Viewport.h"
//#include "Sprite.h"
//#include "Texture.h"
//#include "ReflectionDebug.h"
//#include "DebugDraw.h"
//// Main code
//int main(int argc, char* argv[])
//{
//    // Setup SDL
//    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
//    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
//    {
//        printf("Error: %s\n", SDL_GetError());
//        return -1;
//    }
//    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
//    palka::Viewport view({0, 0, 1280, 720});
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
//    if (err)
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
//    palka::Context::SetContext(renderer);
//    SDL_RendererInfo info;
//    SDL_GetRendererInfo(renderer, &info);
//    printf("%s", info.name);
//
//    bool show_demo_window = true;
//    bool show_another_window = false;
//    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//    palka::Texture test;
//    test.LoadFromFile("Data\\tex\\Hero.png");
//    palka::Texture test2;
//    test2.LoadFromFile("Data\\tex\\pix.png");
//    palka::Sprite sp;
//    sp.setTexture(test, {18, 26, 29, 38});
//    sp.setPosition({100, 100});
//
//    bool done = false;
//    while (!done)
//    {
//        SDL_Event event;
//        while (SDL_PollEvent(&event))
//        {
//            ImGui_ImplSDL2_ProcessEvent(&event);
//            if (event.type == SDL_QUIT)
//                done = true;
//            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
//                event.window.windowID == SDL_GetWindowID(window))
//                done = true;
//        }
//
//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplSDL2_NewFrame(window);
//        ImGui::NewFrame();
//
//
//        palka::debug(view);
//
//        SDL_RenderFlush(renderer);
//        glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
//        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//        glClear(GL_COLOR_BUFFER_BIT);
//        SDL_RenderFlush(renderer);
//        static float x = 0;
//        static float y = 0;
//        static float x2 = 1;
//        static float y2 = 1;
//        ImGui::DragFloat("x", &x);
//        ImGui::DragFloat("y", &y);
//        ImGui::DragFloat("x2", &x2);
//        ImGui::DragFloat("y2", &y2);
//
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        glLoadMatrixf(view.getView().getMatrix());
//        auto sc = view.getScale();
//        SDL_RenderSetScale(renderer, sc.x, sc.y);
//        glMatrixMode(GL_MODELVIEW);
////        glMatrixMode(GL_MODELVIEW);
////        glPopMatrix();
////        glLoadIdentity();
////        glTranslatef(-x, -y, 0.f);
////        //glScalef(x2, y2, 0.f);
////        glPushMatrix();
//        SDL_RenderFlush(renderer);
//        //SDL_RenderCopy(renderer, txt, 0, &rct2);
//
//        auto r2 = sp.getLocalRect();
//        auto r = sp.getQuad(palka::RectF(r2.left, r2.top, r2.w, r2.h));
//        //sp2.setScale({1,static_cast<float>(r2.h)});
//        // const float viewPortScaleX = std::round(((w.getSize().x / v.getSize().x) * 100) / 100);
//        // const float viewPortScaleY = std::round(((w.getSize().y / v.getSize().y) * 100) / 100);
//        //Vec2f scale = {viewPortScaleX,viewPortScaleY};
//
//        //auto rr = Quad(sp.getGlobalRect().getPoints());
//        SDL_RenderFlush(renderer);
//        sp.draw(renderer);
//        //sp2.draw(renderer);
//        palka::DebugDraw::DrawBoxF(r, 4, renderer);
////        SDL_Rect outlineRect{static_cast<int>(r.leftTop.x), static_cast<int>(r.leftTop.y), sp.getTextureRect().w,sp.getTextureRect().h};
////        SDL_RenderDrawRect(renderer, &outlineRect);
//        ImGui::Render();
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
//

