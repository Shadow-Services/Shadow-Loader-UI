#define IMGUI_DEFINE_MATH_OPERATORS

#include <Windows.h>

#include <globals.hpp>

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

