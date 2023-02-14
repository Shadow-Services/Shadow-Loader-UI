#pragma once
#include <set>
#include <math.h>
#include <stdint.h>
#include <vector>
#include <D3DX11tex.h>

#include "user_interface.hpp"
#include "utils.hpp"
#include "Drawing.h"

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