#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cstddef>
#include <algorithm>
#include <thread>
#include "imgui.h"

#define MOVING_AVERAGE 10
#define BUFFER_SIZE 400


// TO FIX CROSS_COMPATIBILITY: https://github.com/TheCherno/Hazel/pull/174/files

namespace pb{

    using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

    struct ProfileResult
    {
        std::string Name;
        FloatingPointMicroseconds Start, End;
        size_t ThreadID;
    };

    struct ProfilingSession
    {
        std::string Name;
    };

    class Profiler
    {
    private:
        ProfilingSession* m_CurrentSession;
        std::ofstream m_OutputStream;
        int m_ProfileCount;

    public:
        Profiler()
            : m_CurrentSession(nullptr), m_ProfileCount(0)
        {
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            m_OutputStream.open(filepath);
            WriteHeader();
            m_CurrentSession = new ProfilingSession{ name };
        }

        void EndSession()
        {
            WriteFooter();
            m_OutputStream.close();
            delete m_CurrentSession;
            m_CurrentSession = nullptr;
            m_ProfileCount = 0;
        }

        void WriteProfile(const ProfileResult& result)
        {
            if (m_ProfileCount++ > 0)
                m_OutputStream << ",";

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            m_OutputStream << "{";
            m_OutputStream << "\"cat\":\"function\",";
            m_OutputStream << "\"dur\":" << (result.End.count() - result.Start.count()) << ',';
            m_OutputStream << "\"name\":\"" << name << "\",";
            m_OutputStream << "\"ph\":\"X\",";
            m_OutputStream << "\"pid\":0,";
            m_OutputStream << "\"tid\":" << result.ThreadID << ",";
            m_OutputStream << "\"ts\":" << result.Start.count();
            m_OutputStream << "}";

            m_OutputStream.flush();
        }

        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }

        static Profiler& Get()
        {
            static Profiler instance;
            return instance;
        }
    };

    class VisualProfiler
    {
        struct DataBuffer
        {
            DataBuffer(const std::string _name)
                : name(_name), sma_sum(0), sma_average(0), sma_points(), sma_index(0), buffer(), buffer_index(0)
            {}

            DataBuffer()
                : name(""), sma_sum(0), sma_average(0), sma_points(), sma_index(0), buffer(), buffer_index(0)
            {}
            
            float sma_points[MOVING_AVERAGE];
            float sma_sum;
            float sma_average;
            float buffer[BUFFER_SIZE];
            int buffer_index;
            int sma_index;
            std::string name;
        };

    private:
        std::unordered_map<std::string, DataBuffer> buffer_map;

    public:
        VisualProfiler()
        {
        }

        void AddPoint(const ProfileResult& result)
        {
            if (buffer_map.find(result.Name) == buffer_map.end()) {
                buffer_map[result.Name] = DataBuffer(result.Name);
            }

            DataBuffer* data = &buffer_map[result.Name];
            data->sma_sum += result.End.count() - result.Start.count();
            data->sma_sum -= data->sma_points[data->sma_index];
            data->sma_points[data->sma_index] = data->sma_sum/MOVING_AVERAGE;
            data->buffer[data->buffer_index] = data->sma_points[data->sma_index];
            data->sma_index++;
            data->buffer_index++;

            if (data->sma_index == MOVING_AVERAGE) data->sma_index = 0;
            if (data->buffer_index == BUFFER_SIZE) data->buffer_index = 0;
        }

        void Render() 
        {
            ImGui::Begin("Profiler Instance");

            for (auto& it: buffer_map) {
                DataBuffer& data = it.second;
                ImGui::PlotLines(data.name.c_str(), data.buffer, BUFFER_SIZE, data.buffer_index, (const char*)0, 0, 1500, ImVec2(400, 100));
                ImGui::SameLine();
                size_t idx = std::max(0, data.buffer_index - 1);
                ImGui::Text("%.4fus", data.buffer[idx % 50]);
            }

            ImGui::End();
        }

        static VisualProfiler& Get()
        {
            static VisualProfiler instance;
            return instance;
        }
    };

    class ProfilingTimer
    {
    public:
        ProfilingTimer(const char* name, bool _visual=false)
            : m_Name(name), m_Stopped(false), m_Visual(_visual)
        {
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~ProfilingTimer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch();

            size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            Profiler::Get().WriteProfile({ m_Name, start, end, threadID });
            if(m_Visual) VisualProfiler::Get().AddPoint({ m_Name, start, end, threadID });
            m_Stopped = true;
        }
    private:
        const bool m_Visual;
        const char* m_Name;
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
        bool m_Stopped;
    };



}

#define PB_PROFILE 1

#if PB_PROFILE
    #define PB_PROFILE_BEGIN_SESSION(name, filepath)    ::pb::Profiler::Get().BeginSession(name, filepath)
    #define PB_PROFILE_END_SESSION()    ::pb::Profiler::Get().EndSession()
    #define PB_PROFILE_SCOPE(name)  ::pb::ProfilingTimer timer##__LINE__(name)
    #define PB_PROFILE_VISUAL_SCOPE(name)  ::pb::ProfilingTimer timer##__LINE__(name, true)
    #define PB_PROFILE_FUNCTION() PB_PROFILE_SCOPE(__FUNCSIG__)
    #define PB_PROFILE_RENDER() ::pb::VisualProfiler::Get().Render()
#else
    #define PB_PROFILE_BEGIN_SESSION(name, filepath)
    #define PB_PROFILE_END_SESSION()
    #define PB_PROFILE_SCOPE(name)
    #define PB_PROFILE_VISUAL_SCOPE(name)
    #define PB_PROFILE_FUNCTION()
    #define PB_PROFILE_RENDER()
#endif

