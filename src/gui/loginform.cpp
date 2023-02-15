#include <globals.hpp>

bool loginform::bDraw = true;

void loginform::Active()
{
	bDraw = true;
}

bool loginform::isActive()
{
	return bDraw == true;
}

void ImGui::Spinner(const char* label, const ImVec2& pos, float radius, int thickness, const ImU32& color) {
	ImGuiContext& g = *GImGui;

	ImVec2 size((radius) * 2, radius * 2);

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));

	ImGui::GetBackgroundDrawList()->PathClear();

	int num_segments = 30;
	int start = abs(ImSin(g.Time * 0.5f) * (num_segments - 5));

	const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
	const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

	const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius);

	for (int i = 0; i < num_segments; i++) {
		const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
		ImGui::GetBackgroundDrawList()->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
			centre.y + ImSin(a + g.Time * 8) * radius));
	}

	ImGui::GetBackgroundDrawList()->PathStroke(color, false, thickness);
}


void loginform::Draw()
{

	if (isActive())
	{

		ImGui::SetNextWindowSize(g.window.vWindowSize);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin(g.window.lpWindowName, &bDraw, g.window.WindowFlags);
		{
			auto draw = ImGui::GetWindowDrawList();
			ImGuiStyle style = ImGui::GetStyle();
			ImVec2 windowpos = ImGui::GetWindowPos();

			draw->AddRectFilled(windowpos, ImVec2(g.window.vWindowSize.x + windowpos.x, g.window.vWindowSize.y + windowpos.y), ImColor(12, 12, 12, 255));

			auto tSize = ImGui::CalcTextSize("Shadow Loaders");
			float tCX = (g.window.vWindowSize.x - tSize.x) / 2;
			draw->AddText({ tCX + windowpos.x, 50 + windowpos.y }, ImColor(125, 45, 65, 255), "Shadow Loaders");

			float sCX = (g.window.vWindowSize.x - 100) / 2;
			ImGui::Spinner("loading...", { windowpos.x + sCX, windowpos.y + 150 }, 50, 2.f, ImColor(136, 233, 134, 255));

			if (!g.login.g_once) {
				g.worker.status_worker = true;
				g.login.g_once = true;
				std::thread(runner::login_worker).detach();
				std::thread(runner::status_worker).detach();
			}

			auto sSize = ImGui::CalcTextSize(g.login.g_status.c_str());
			float statusCX = (g.window.vWindowSize.x - sSize.x) / 2;
			draw->AddText({ statusCX + windowpos.x, 300 + windowpos.y }, ImColor(192, 192, 192, 255), g.login.g_status.c_str());
			
		}
		ImGui::End();
	}

#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
#endif
}