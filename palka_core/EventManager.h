//
// Created by NePutin on 8/21/2021.
//

#ifndef PALKA_EVENTMANAGER_H
#define PALKA_EVENTMANAGER_H

#include <SDL_events.h>
#include <set>
#include <map>
#include <functional>
#include <utility>

namespace palka
{
    struct KBoardEvent
    {
        SDL_EventType type = (SDL_EventType) 0;
        SDL_KeyCode key = (SDL_KeyCode) 0;
        //KBoardEvent() : type(), key() {}

        KBoardEvent(SDL_EventType type, SDL_KeyCode key) : type(type), key(key)
        {}

        KBoardEvent(SDL_KeyCode key) : key(key)
        {}

        bool operator==(const KBoardEvent& other) const
        { return key == other.key && type == other.type; }

        bool operator<(const KBoardEvent& o) const
        {
            return type < o.type || (type == o.type && key < o.key);
        }

        static KBoardEvent KeyPressed(SDL_KeyCode k)
        {
            return KBoardEvent{SDL_KEYDOWN, k};
        }

        static KBoardEvent KeyReleased(SDL_KeyCode k)
        {
            return KBoardEvent{SDL_KEYUP, k};
        }
    };

    struct MouseEvent
    {
        enum Mouse_Buttom
        {
            None = 0,
            Left = SDL_BUTTON_LEFT,
            Right = SDL_BUTTON_RIGHT,
            Middle = SDL_BUTTON_MIDDLE
        };

        SDL_EventType type = (SDL_EventType) 0;
        Mouse_Buttom key = None;

        MouseEvent(SDL_EventType type, Mouse_Buttom b) : key(b), type(type)
        {}

        MouseEvent(SDL_EventType type) : type(type)
        {}

        MouseEvent(Mouse_Buttom b) : key(b)
        {}

        bool operator==(const MouseEvent& other) const
        { return key == other.key && type == other.type; }

        bool operator<(const MouseEvent& o) const
        {
            return (type < o.type || (type == o.type && key < o.key));
        }

        static MouseEvent ButtonPressed(Mouse_Buttom b)
        {
            return MouseEvent{SDL_MOUSEBUTTONDOWN, b};
        }

        static MouseEvent ButtonReleased(Mouse_Buttom b)
        {
            return MouseEvent{SDL_MOUSEBUTTONUP, b};
        }

        static MouseEvent WheelScrolled()
        {
            return MouseEvent{SDL_MOUSEWHEEL, Mouse_Buttom::None};
        }
    };

    class EventManager
    {
    private:
        std::multimap<KBoardEvent, std::function<void(SDL_Event&)>> KeyboardEvents;
        std::multimap<MouseEvent, std::function<void(SDL_Event&)>> MouseEvents;
        std::multimap<KBoardEvent, std::function<void()>> KeyboardInputs;
        std::multimap<SDL_EventType, std::function<void(SDL_Event&)>> TypeEvents;
        std::set<SDL_KeyCode> keyPressed;

        bool enable;
    public:
        EventManager(bool enable = true) : enable(enable)
        {};

        void addEvent(SDL_EventType t, std::function<void(SDL_Event&)> callback)
        {
            TypeEvents.emplace(t, callback);
        }

        void addEvent(KBoardEvent e, std::function<void(SDL_Event&)> callback)
        {
            KeyboardEvents.emplace(e, callback);
        }

        void addInput(SDL_KeyCode k, std::function<void()> callback)
        {
            KeyboardInputs.emplace(KBoardEvent::KeyPressed(k), callback);
        }

        void addEvent(MouseEvent e, std::function<void(SDL_Event&)> callback)
        {
            MouseEvents.emplace(e, callback);
        }

        bool isKeyPressed(SDL_KeyCode key)
        {
            return keyPressed.count(key) == 1;
        }

        void clear()
        {
            keyPressed.clear();
        }

        void updateInput()
        {
            for (auto e : keyPressed)
            {
                auto range = KeyboardInputs.equal_range(KBoardEvent::KeyPressed(e));
                for (auto it = range.first; it != range.second; ++it)
                    it->second();
            }
        }

        void updateEvent(SDL_Event& e)
        {
            {
                auto range = TypeEvents.equal_range((SDL_EventType) e.type);
                for (auto it = range.first; it != range.second; ++it)
                    it->second(e);
            }
            switch (e.type)
            {
                case SDL_KEYDOWN:
                {
                    keyPressed.emplace((SDL_KeyCode) e.key.keysym.sym);
                    auto range = KeyboardEvents.equal_range(KBoardEvent{(SDL_EventType) e.type, (SDL_KeyCode) e.key.keysym.sym});
                    for (auto it = range.first; it != range.second; ++it)
                        it->second(e);
                }
                    break;
                case SDL_KEYUP:
                {
                    auto range = KeyboardEvents.equal_range(KBoardEvent{(SDL_EventType) e.type, (SDL_KeyCode) e.key.keysym.sym});
                    for (auto it = range.first; it != range.second; ++it)
                        it->second(e);
                }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                {
                    auto range = MouseEvents.equal_range(MouseEvent{(SDL_EventType) e.type, (MouseEvent::Mouse_Buttom) e.button.button});
                    for (auto it = range.first; it != range.second; ++it)
                        it->second(e);
                }
                    break;
                case SDL_MOUSEBUTTONUP:
                {
                    auto range = MouseEvents.equal_range(MouseEvent{(SDL_EventType) e.type, (MouseEvent::Mouse_Buttom) e.button.button});
                    for (auto it = range.first; it != range.second; ++it)
                        it->second(e);
                }
                    break;
//                case SDL_MOUSEWHEEL:
//                {
//                    auto range = MouseEvents.equal_range(MouseEvent{e.type});
//                    for(auto it = range.first; it != range.second; ++it)
//                        it->second(e);
//                }
//                    break;
//                case SDL_MOUSEMOTION:
//                {
//                    auto range = MouseEvents.equal_range(MouseEvent{e.type});
//                    for(auto it = range.first; it != range.second; ++it)
//                        it->second(e);
//                }
//                    break;
            }
        }

        void setEnable(bool e)
        { enable = e; }

        bool isEneable() const
        { return enable; }
    };
}

#endif //PALKA_EVENTMANAGER_H
