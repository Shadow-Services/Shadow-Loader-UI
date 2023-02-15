#ifndef UI_H
#define UI_H

#include <Windows.h>
#include <d3d11.h>
#include <tchar.h>
#include <thread>
#include <vector>
#include <string>

#include "globals.hpp"
#include "ImGui/imgui_internal.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class UI
{
private:
	static ID3D11Device* pd3dDevice;
	static ID3D11DeviceContext* pd3dDeviceContext;
	static IDXGISwapChain* pSwapChain;
	static ID3D11RenderTargetView* pMainRenderTargetView;

	static bool CreateDeviceD3D(HWND hWnd);
	static void CleanupDeviceD3D();
	static void CreateRenderTarget();
	static void CleanupRenderTarget();
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	static void Render();
	static std::size_t write_callback(char* in, size_t size, size_t nmemb, std::string* out);
	static bool ModulesCallback(void* data, int n, const char** out_text);
	static void StatusWorker();
	static void InjectionWorker(char* mod);
	static ID3D11ShaderResourceView* gtaIcon;
	//static bool g_once;
	//static bool g_injectionOnce;
	//static bool g_injecting;
	//static bool g_statusWorker ;
	//static std::string g_status;

};

#endif
