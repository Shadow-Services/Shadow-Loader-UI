#include "Drawing.h"

LPCSTR Drawing::lpWindowName = "Shadow Loader";
ImVec2 Drawing::vWindowSize = { 600, 400 };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
bool Drawing::bDraw = true;
std::string g_welcomeMsg;
std::vector<std::string> g_modules;
int g_moduleIndex = 0;

bool g_once = false;
void Drawing::Active()
{
	bDraw = true;
}

bool Drawing::isActive()
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

void Drawing::Draw()
{

	if (isActive())
	{
		
		ImGui::SetNextWindowSize(vWindowSize);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin(lpWindowName, &bDraw, WindowFlags);
		{
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.f);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 0.4));
			ImGui::ImageButtonWithText((PVOID)UI::gtaIcon, "     Grand Theft Auto V", ImVec2(116.4,66.4), ImVec2(0,0), ImVec2(1,1), 1.f);
            ImGui::PopStyleVar(1);
            ImGui::PopStyleColor(1);
            ImGui::Text("Test");
			ImGui::Text("Welcome back %s", std::string(GetUsername()).c_str());

			ImGui::ListBox("", &g_moduleIndex, UI::ModulesCallback, &g_modules, g_modules.size(), 12);
		}
		ImGui::End();
	}

	#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
	#endif
}
