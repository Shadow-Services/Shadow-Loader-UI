#ifndef DRAWING_H
#define DRAWING_H
#define IMGUI_DEFINE_MATH_OPERATORS

#include <Windows.h>

#include <globals.hpp>

class Drawing
{
private:
	static LPCSTR lpWindowName;
	static ImVec2 vWindowSize;
	static ImGuiWindowFlags WindowFlags;
	static bool bDraw;

public:
	static void Active();
	static bool isActive();
	static void Draw();
};

namespace ImGui {
	// label is used as id
	// <0 frame_padding uses default frame padding settings. 0 for no padding
	extern IMGUI_API bool ImageButtonWithText(ImTextureID texId, const char* label, const ImVec2& imageSize = ImVec2(0, 0), const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1));
}
#endif
