#include "pbpch.h"

#include "imgui.h"
#include "imgui_internal.h"

namespace ImGui {
    
    void Spinner(const char* label, const float indicator_radius,
        const ImU32& main_color, const ImU32& backdrop_color,
        const int circle_count, const float speed, const float padding_top) {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems) {
            return;
        }

        ImGuiContext& g = *GImGui;
        const ImGuiID id = window->GetID(label);
        
        const ImVec2 pos = window->DC.CursorPos;
        const float circle_radius = indicator_radius / 10.0f;
        const ImRect bb(pos, ImVec2(pos.x + indicator_radius * 2.0f,
            pos.y + indicator_radius * 2.0f));
        ItemSize(bb);
        if (!ItemAdd(bb, id)) {
            return;
        }

        ImVec4 main_color_vec4 = ImGui::ColorConvertU32ToFloat4(main_color);
        ImVec4 backdrop_color_vec4 = ImGui::ColorConvertU32ToFloat4(backdrop_color);

        const float t = g.Time;
        const auto degree_offset = 2.0f * IM_PI / circle_count;
        for (int i = 0; i < circle_count; ++i) {
            const auto x = indicator_radius * std::sin(degree_offset * i);
            const auto y = -1.0f*padding_top + indicator_radius * std::cos(degree_offset * i);
            const auto growth = std::max(0.0f, std::sin(t * speed - i * degree_offset));
            ImVec4 color;
            color.x = main_color_vec4.x * growth + backdrop_color_vec4.x * (1.0f - growth);
            color.y = main_color_vec4.y * growth + backdrop_color_vec4.y * (1.0f - growth);
            color.z = main_color_vec4.z * growth + backdrop_color_vec4.z * (1.0f - growth);
            color.w = 1.0f;
            window->DrawList->AddCircleFilled(ImVec2(pos.x + indicator_radius + x,
                pos.y + indicator_radius - y),
                circle_radius + growth * circle_radius,
                GetColorU32(color));
        }
    }

}