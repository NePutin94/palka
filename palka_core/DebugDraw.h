//
// Created by NePutin on 6/30/2021.
//

#ifndef PALKA_DEBUGDRAW_H
#define PALKA_DEBUGDRAW_H

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include <vector>
#include <SDL_render.h>
#include <imgui.h>

namespace palka
{

    class DebugDraw
    {
    public:
        static void DrawVertex(std::vector<Vec2i> points, int scale, SDL_Renderer* renderer)
        {
            int size = points.size();
            for (auto& p : points) {
                p = p / scale;
            }
            SDL_Point points2[points.size()];
            for (int i = 0; i < size; ++i) {
                auto p = points[i];
                points2[i] = {p.x, p.y};
            }
            SDL_RenderSetScale(renderer, scale, scale);
            //Uint8 r, g, b, a;
            //SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
            SDL_SetRenderDrawColor(renderer, 180, 80, 100, 255);
            SDL_RenderDrawPoints(renderer, points2, size);
            SDL_RenderSetScale(renderer, 1, 1);
            //SDL_SetRenderDrawColor(renderer, r, g, b, a);
        }

        static void DrawBox(RectI rect, int scale, SDL_Renderer* renderer)
        {
            SDL_Rect r = rect.getRect();
            //SDL_RenderSetScale(renderer, scale, scale);
            SDL_SetRenderDrawColor(renderer, 180, 80, 100, 255);
            SDL_RenderDrawRect(renderer, &r);
            // SDL_RenderSetScale(renderer, 1, 1);
        }

        static void DrawBox(Quad<int> q, int scale, SDL_Renderer* renderer)
        {
            //SDL_RenderSetScale(renderer, scale, scale);
            SDL_SetRenderDrawColor(renderer, 180, 80, 100, 255);
            SDL_RenderDrawLine(renderer, q.leftTop.x, q.leftTop.y, q.rightTop.x, q.rightTop.y);
            SDL_RenderDrawLine(renderer, q.rightTop.x, q.rightTop.y, q.rightBottom.x, q.rightBottom.y);
            SDL_RenderDrawLine(renderer, q.rightBottom.x, q.rightBottom.y, q.leftBottom.x, q.leftBottom.y);
            SDL_RenderDrawLine(renderer, q.leftBottom.x, q.leftBottom.y, q.leftTop.x, q.leftTop.y);
            // SDL_RenderSetScale(renderer, 1, 1);
        }

        static void DrawSpriteDebug(Sprite& sp)
        {
            sp.draw(Context::GetContext());
            auto rr = sp.dst.TrueQuad;
            DebugDraw::DrawBox(rr, 4, Context::GetContext());
            bool open = true;
            SimpleText(rr.leftTop, &open, "asd", rr.leftTop.toString(), Pos::LeftSideTop);
            SimpleText(rr.leftBottom, &open, "xcvb", rr.leftBottom.toString(), Pos::LeftSideBottom);
            SimpleText(rr.rightTop, &open, "gh", rr.rightTop.toString(), Pos::RightSideTop);
            SimpleText(rr.rightBottom, &open, "zxc", rr.rightBottom.toString(), Pos::RightSideBottom);
            DebugDraw::DrawVertex({rr.leftTop, rr.rightBottom, sp.dst.center}, 4, Context::GetContext());
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
            switch (pos) {
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
                                                 ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav)) {
                if (!text.empty())
                    ImGui::Text("%s", text.c_str());
                //ImGui::Separator();
                ImGui::Text("(X,Y): (%.1d, %.1d)", position.x, position.y);
                ImGui::End();
            }
        }

    private:
    };
}

#endif //PALKA_DEBUGDRAW_H
