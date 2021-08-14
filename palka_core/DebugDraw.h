//
// Created by NePutin on 6/30/2021.
//

#ifndef PALKA_DEBUGDRAW_H
#define PALKA_DEBUGDRAW_H

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "Window.h"
#include <vector>
#include <SDL_render.h>
#include <imgui.h>
#include <rttr/type>

namespace palka
{
    struct Color
    {
    RTTR_ENABLE()
    public:
        Color(int r, int g, int b) noexcept: r(r), g(g), b(b) {}
        unsigned int r = 0;
        unsigned int g = 0;
        unsigned int b = 0;
    };

    class DebugDraw
    {
    RTTR_ENABLE()
    public:
        static void DrawVertexF(std::vector<Vec2f> points, SDL_Renderer* renderer)
        {
            int size = points.size();
            SDL_FPoint points2[points.size()];
            for (int i = 0; i < size; ++i)
            {
                auto p = points[i];
                points2[i] = {p.x, p.y};
            }
            SDL_SetRenderDrawColor(renderer, point_color.r, point_color.g, point_color.b, 255);
            SDL_RenderDrawPointsF(renderer, points2, size);
        }

        static void DrawVertex(std::vector<Vec2i> points, SDL_Renderer* renderer)
        {
            int size = points.size();
            SDL_Point points2[points.size()];
            for (int i = 0; i < size; ++i)
            {
                auto p = points[i];
                points2[i] = {p.x, p.y};
            }
            SDL_SetRenderDrawColor(renderer, point_color.r, point_color.g, point_color.b, 255);
            SDL_RenderDrawPoints(renderer, points2, size);
        }

        static void DrawBoxF(Quad<float> q, int scale, SDL_Renderer* renderer)
        {
            SDL_SetRenderDrawColor(renderer, line_color.r, line_color.g, line_color.b, 255);
            SDL_RenderDrawLineF(renderer, q.leftTop.x, q.leftTop.y, q.rightTop.x, q.rightTop.y);
            SDL_RenderDrawLineF(renderer, q.rightTop.x, q.rightTop.y, q.rightBottom.x, q.rightBottom.y);
            SDL_RenderDrawLineF(renderer, q.rightBottom.x, q.rightBottom.y, q.leftBottom.x, q.leftBottom.y);
            SDL_RenderDrawLineF(renderer, q.leftBottom.x, q.leftBottom.y, q.leftTop.x, q.leftTop.y);
        }

        static void DrawBox(RectI rect, SDL_Renderer* renderer)
        {
            SDL_Rect r = rect.getRect();
            SDL_SetRenderDrawColor(renderer, line_color.r, line_color.g, line_color.b, 255);
            SDL_RenderDrawRect(renderer, &r);
        }

        static void DrawBox(Quad<int> q, SDL_Renderer* renderer)
        {
            SDL_SetRenderDrawColor(renderer, line_color.r, line_color.g, line_color.b, 255);
            SDL_RenderDrawLine(renderer, q.leftTop.x, q.leftTop.y, q.rightTop.x, q.rightTop.y);
            SDL_RenderDrawLine(renderer, q.rightTop.x, q.rightTop.y, q.rightBottom.x, q.rightBottom.y);
            SDL_RenderDrawLine(renderer, q.rightBottom.x, q.rightBottom.y, q.leftBottom.x, q.leftBottom.y);
            SDL_RenderDrawLine(renderer, q.leftBottom.x, q.leftBottom.y, q.leftTop.x, q.leftTop.y);
        }

        static void DrawSpriteDebug(Sprite& sp, Window& w)
        {
            w.draw(sp);

            float x, y;
            SDL_RenderGetScale(Window::GetContext(), &x, &y);
            //w.draw(sp);
            //auto v = w.getViewport();
            // auto offset = v.getStaticOffset(w.getSize());
            auto r2 = sp.getLocalRect();
            auto r = sp.getQuad(RectF(r2.left, r2.top, r2.w, r2.h));
            // const float viewPortScaleX = std::round(((w.getSize().x / v.getSize().x) * 100) / 100);
            // const float viewPortScaleY = std::round(((w.getSize().y / v.getSize().y) * 100) / 100);
            //Vec2f scale = {viewPortScaleX,viewPortScaleY};
            //auto rr = Quad(sp.getGlobalRect().getPoints());
            DebugDraw::DrawBoxF(w.getViewport()->applyTranslate(r), 4, Window::GetContext());
            //auto offset2 = v.mapPixelToCoords({0, 0});
            //Vec2f test = trasform.rotate(v.getRotation(), (sp.getCenter() + r.leftTop) + offset).transformPoint(r.leftBottom + offset);
//            SimpleTextF(r.leftTop*scale + offset, &open, "drawspdebug1", "1", Pos::LeftSideTop);
//            SimpleTextF(r.leftBottom*scale + offset, &open, "drawspdebug2", "2", Pos::RightSideTop);
//            SimpleTextF(r.rightBottom*scale + offset, &open, "drawspdebug3", "3", Pos::RightSideBottom);
//            SimpleTextF(r.rightTop*scale + offset, &open, "drawspdebug4", "4", Pos::LeftSideBottom);
//            SimpleTextF(rr.leftTop, &open, "asd", rr.leftTop.toString(), Pos::LeftSideTop);
//            SimpleTextF(rr.leftBottom, &open, "xcvb", rr.leftBottom.toString(), Pos::LeftSideBottom);
//            SimpleTextF(rr.rightTop, &open, "gh", rr.rightTop.toString(), Pos::RightSideTop);
//            SimpleTextF(rr.rightBottom, &open, "zxc", rr.rightBottom.toString(), Pos::RightSideBottom);
            DebugDraw::DrawVertexF({r.leftTop, r.rightBottom, sp.getPosition() + sp.getCenter() * sp.getScale()}, Window::GetContext());
        }

        enum Pos
        {
            LeftSideTop,
            LeftSideBottom,
            RightSideTop,
            RightSideBottom
        };

        static void SimpleText(Vec2i position, bool* open, std::string name, std::string text, Pos pos)
        {
            ImVec2 size = {128, 48};
            ImVec2 window_pos{};
            switch (pos)
            {
                case LeftSideTop:
                    window_pos = ImVec2(position.x - size.x, position.y - size.y);
                    break;
                case LeftSideBottom:
                    window_pos = ImVec2(position.x - size.x, position.y);
                    break;
                case RightSideTop:
                    window_pos = ImVec2(position.x, position.y - size.y);
                    break;
                case RightSideBottom:
                    window_pos = ImVec2(position.x, position.y);
                    break;
            }
            ImGui::SetNextWindowSize(size);
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, ImVec2(0, 0));
            ImGui::SetNextWindowBgAlpha(0.6f);
            if (ImGui::Begin(name.c_str(), open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
                                                 ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
                                                 ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
            {
                if (!text.empty())
                    ImGui::Text("%s", text.c_str());
                //ImGui::Separator();
                ImGui::Text("(X,Y): (%.1d, %.1d)", position.x, position.y);
                ImGui::End();
            }

        }

        static void SimpleTextF(Vec2f position, bool* open, std::string name, std::string text, Pos pos)
        {
            ImVec2 size = {128, 48};
            ImVec2 window_pos{};
            switch (pos)
            {
                case LeftSideTop:
                    window_pos = ImVec2(position.x - size.x, position.y - size.y);
                    break;
                case LeftSideBottom:
                    window_pos = ImVec2(position.x - size.x, position.y);
                    break;
                case RightSideTop:
                    window_pos = ImVec2(position.x, position.y - size.y);
                    break;
                case RightSideBottom:
                    window_pos = ImVec2(position.x, position.y);
                    break;
            }
            ImGui::SetNextWindowSize(size);
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, ImVec2(0, 0));
            ImGui::SetNextWindowBgAlpha(0.6f);
            if (ImGui::Begin(name.c_str(), open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
                                                 ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
                                                 ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
            {
                if (!text.empty())
                    ImGui::Text("%s", text.c_str());
                //ImGui::Separator();
                ImGui::Text("(X,Y): (%.1d, %.1d)", position.x, position.y);
                ImGui::End();
            }
        }

        static Color point_color;
        static Color line_color;
    };
}

#endif //PALKA_DEBUGDRAW_H
