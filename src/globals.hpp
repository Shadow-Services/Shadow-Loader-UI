#pragma once
#include <set>
#include <math.h>
#include <stdint.h>
#include <vector>
#include <D3DX11tex.h>

#include "gui/user_interface.hpp"
#include "utilities/utils.hpp"
#include "gui/drawing.hpp"
#include "fonts/fonts.hpp"


#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#define IMGUI_DEFINE_MATH_OPERATORS

class project_settings
{
public:
	struct window
	{
		ImFont* font_main = nullptr;
	} window{};
};

inline auto g = project_settings();