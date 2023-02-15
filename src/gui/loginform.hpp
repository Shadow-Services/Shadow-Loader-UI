#pragma once

#include <Windows.h>

#include <globals.hpp>
#include "ImGui/imgui_internal.h"
#define IMGUI_DEFINE_MATH_OPERATORS

class loginform
{
private:
	static bool bDraw;

public:
	static void Active();
	static bool isActive();
	static void Draw();
};

namespace ImGui {
	
	extern IMGUI_API void Spinner(const char* label, const ImVec2& pos, float radius, int thickness, const ImU32& color);
}

