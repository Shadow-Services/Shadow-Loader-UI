#pragma once
#include <set>
#include <math.h>
#include <stdint.h>
#include <vector>
#include <D3DX11tex.h>
#include <format>

#include "gui/user_interface.hpp"
#include "utilities/utils.hpp"
#include "utilities/runners.hpp"
#include "gui/drawing.hpp"
#include "fonts/fonts.hpp"
#include "gui/components/components.hpp"
#include "gui/loginform.hpp"

#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#define IMGUI_DEFINE_MATH_OPERATORS

class project_settings
{
public:
	struct login_form
	{
		bool g_once = false;
		std::string g_status = "";
	} login{};

	struct injection
	{
		std::vector<std::string> module_list;
		int module_index = 0;
		bool inject_once = false;
	} injection{};

	struct window
	{
		ImFont* font_main = nullptr;
		ImVec2 vWindowSize = { 600, 400 };
		LPCSTR lpWindowName = "Shadow Loader";
		bool logged_in = false;
		ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
	} window{};

	struct worker
	{
		bool status_worker = false;
		bool injecting = false;
	} worker{};
};

inline auto g = project_settings();