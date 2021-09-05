//
// Created by NePutin on 6/30/2021.
//

#ifndef PALKA_CONSOLELOG_H
#define PALKA_CONSOLELOG_H

#include <imgui.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <shared_mutex>

namespace palka
{
    namespace Console
    {
        enum logType
        {
            error = 1,
            info,
            fatal,
            system,
            script,
            message
        };

        constexpr std::string_view logType_s[] =
                {
                        "all", "error", "info", "fatal", "system", "script", "message"
                };

        struct Log
        {
            Log(std::string s, logType t);

            std::string text;
            std::string pervText;

            void count_update(int count);

            int log_count;
            ImVec4 color;
            logType type;
        };

        class AppLog
        {
        private:
            static bool ScrollToBottom;
            static std::vector <std::string> current_input;
            static std::vector<Log> Buffer;
            static bool newLog;
            static size_t offset;
            static std::shared_mutex globalMutex;
        public:
            AppLog() = default;

            ~AppLog()
            { saveLog("Data/log.txt"); }

            static void Clear()
            {
                Buffer.clear();
                Buffer.shrink_to_fit();
            }

            static bool hasNewLog()
            {
                bool prev = newLog;
                newLog = false;
                return prev;
            }

            static bool hasNewLogByTyp(logType t);

            static void addLog(Log log);

            static void addLog(std::string s, logType t);

            static void addLog_(std::string s, logType t, ...);

            static void saveLog(std::string_view path);

            static void Draw(const char* title, bool* p_open);

            static std::string lastLog()
            {
                std::shared_lock <std::shared_mutex> lock{globalMutex};

                if (offset == 0)
                    return Buffer.back().pervText;
                else
                    return (Buffer.begin() + offset)->pervText;
                //return Buffer.back().pervText;
            }
        };
    } // namespace Console
}

#endif //PALKA_CONSOLELOG_H
