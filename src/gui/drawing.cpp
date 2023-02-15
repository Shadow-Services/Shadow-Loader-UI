#include "drawing.hpp"

bool drawing::bDraw = true;
int selected_tab = 0;
void drawing::Active()
{ 
	bDraw = true;
}

bool drawing::isActive()
{
	return bDraw == true;
}

namespace ImGui {
    bool ImageButtonWithText(ImTextureID texId, const char* label, const ImVec2& imageSize, const ImVec2& uv0, const ImVec2& uv1, int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col) {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImVec2 size = imageSize;
        if (size.x <= 0 && size.y <= 0) { size.x = size.y = ImGui::GetTextLineHeightWithSpacing(); }
        else {
            if (size.x <= 0)          size.x = size.y;
            else if (size.y <= 0)     size.y = size.x;
            size *= window->FontWindowScale * ImGui::GetIO().FontGlobalScale;
        }

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;

        const ImGuiID id = window->GetID(label);
        const ImVec2 textSize = ImGui::CalcTextSize(label, NULL, true);
        const bool hasText = textSize.x > 0;

        const float innerSpacing = hasText ? ((frame_padding >= 0) ? (float)frame_padding : (style.ItemInnerSpacing.x)) : 0.f;
        const ImVec2 padding = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;
        const ImVec2 totalSizeWithoutPadding(size.x + innerSpacing + textSize.x, size.y > textSize.y ? size.y : textSize.y);
        const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + totalSizeWithoutPadding + padding * 2);
        ImVec2 start(0, 0);
        start = window->DC.CursorPos + padding; if (size.y < textSize.y) start.y += (textSize.y - size.y) * .5f;
        const ImRect image_bb(start, start + size);
        start = window->DC.CursorPos + padding; start.x += size.x + innerSpacing; if (size.y > textSize.y) start.y += (size.y - textSize.y) * .5f;
        ItemSize(bb);
        if (!ItemAdd(bb, id)) 
            return false;

        bool hovered = false, held = false;
        bool pressed = ButtonBehavior(bb, id, &hovered, &held);

        // Render
        const ImU32 col = GetColorU32((hovered && held) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
        RenderFrame(bb.Min, ImVec2(bb.Max.x + 50, bb.Max.y), col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
        if (bg_col.w > 0.0f)
            window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, GetColorU32(bg_col));

        window->DrawList->AddImage(texId, image_bb.Min, image_bb.Max, uv0, uv1, GetColorU32(tint_col));

        if (textSize.x > 0) ImGui::RenderText(start, label);
        return pressed;
    }
}
bool do_once = false;
void drawing::Draw()
{

	if (isActive())
	{
        if (!do_once)
        {
            g.injection.module_list = utils::string_splice(std::string(GetModules()), "##");
            do_once = true;
        }
		ImGui::SetNextWindowSize(g.window.vWindowSize);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin(g.window.lpWindowName, &bDraw, g.window.WindowFlags);
		{
            auto draw = ImGui::GetWindowDrawList();
            ImGuiStyle style = ImGui::GetStyle();
            ImVec2 windowpos = ImGui::GetWindowPos();

            // Side bar background / line draw
            draw->AddRectFilled((windowpos + ImVec2(0, 0)), (ImVec2(163, g.window.vWindowSize.y)+ windowpos), ImColor(24, 24, 26), style.WindowRounding, ImDrawFlags_RoundCornersLeft);
            draw->AddLine((ImVec2(163, 2) + windowpos), (ImVec2(163, g.window.vWindowSize.y - 2) + windowpos), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
            draw->AddLine((ImVec2( 16, 47) + windowpos), (ImVec2(148, 47) + windowpos), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
            
            // Tab Draw Region
            ImGui::SetCursorPos({ 8, 56 });
            if (components::tab("Home", selected_tab == 0)) { selected_tab = 0; }

            // Active view draw region
            ImGui::SetCursorPos({ 165, 18 });
            ImGui::BeginGroup();
            ImGui::Text("Test");
			ImGui::Text("Welcome back %s", GetUsername());
            ImGui::ListBox("", &g.injection.module_index, runner::module_callback, &g.injection.module_list, g.injection.module_list.size(), 12);
            ImGui::EndGroup();
            //ImGui::ImageButtonWithText((PVOID)UI::gtaIcon, "     Grand Theft Auto V", ImVec2(116.4f,66.4f), ImVec2(0.f,0.f), ImVec2(1.f,1.f), 1.f);
			//ImGui::ListBox("", &g_moduleIndex, UI::ModulesCallback, &g_modules, g_modules.size(), (int)12);
		}
		ImGui::End();
	}

	#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
	#endif
}
