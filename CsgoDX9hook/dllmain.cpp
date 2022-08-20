// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

typedef HRESULT(WINAPI* Reset_t)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*); // 16
typedef long(__stdcall* EndScene_t)(LPDIRECT3DDEVICE9);                      // 42
typedef LRESULT(__stdcall* WndProc_t)(const HWND, UINT, WPARAM, LPARAM);


D3DPRESENT_PARAMETERS   g_present;
IDirect3D9* g_Direct3D9 = NULL;
IDirect3DDevice9* g_pd3dDevice = NULL;

HWND g_hWnd = NULL;

//声明类型
Reset_t oReset;
EndScene_t oEndScene;
WndProc_t oWndProc;

DWORD* dDeviceVT = NULL;

//(EndScene)(THIS) PURE;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) return true;
	return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);


}

HRESULT __stdcall hkReset(IDirect3DDevice9* PD3DdEVICE, D3DPRESENT_PARAMETERS* pPresentationParmeters)
{
	/*Helpers::UnHookFunction((PVOID*)(&oReset), hkReset);
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT tmpReset = PD3DdEVICE->Reset(pPresentationParmeters);
	ImGui_ImplDX9_CreateDeviceObjects();
	Helpers::StartHookFunction((PVOID*)(&oReset), hkReset);
	return tmpReset;*/
	printf("已被HOOk");
	return 0;
}

void MineImGuiInit(IDirect3DDevice9* pd3dDevice)
{
	// 检查IMGUI 版本
	IMGUI_CHECKVERSION();

	// 创建IMGUI上下文
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	// 关闭imgui  配置文件的显示
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;//配置文件打开配置标识
	io.WantSaveIniSettings = false;
	io.IniFilename = NULL;//目录

	//ImGuiStyle& style = ImGui::GetStyle();//设置风格
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();
	//ImGui::StyleColorsLight();
	//LoadMyStype();

	//SetLayeredWindowAttributes();
	// 设置字体---为了显示中文
	ImFontConfig f_cfg;
	f_cfg.FontDataOwnedByAtlas = false;

	const ImFont* font = io.Fonts->AddFontFromMemoryTTF((void*)baidu_font_data, baidu_font_size, 17.0f, &f_cfg, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

	ImGui_ImplWin32_Init(g_hWnd);//win32初始化
	ImGui_ImplDX9_Init(pd3dDevice);//d3d9初始化


}

HRESULT __stdcall hkEndScene(IDirect3DDevice9* pd3dDevice)
{
	//Helpers::UnHookFunction((PVOID*)(&oEndScene), hkEndScene);
	////IMGUI初始化
	//int FirstCall = 1;
	//if (FirstCall)//第一次初始化
	//{
	//	FirstCall--;
	//	MineImGuiInit(pd3dDevice);
	//	oWndProc = (WNDPROC)SetWindowLongPtr(g_hWnd, GWL_WNDPROC, (LONG_PTR)hkWndProc);
	//}
	//LoadMyWin();


	//HRESULT result = pd3dDevice->EndScene();//运行原窗口函数
	//Helpers::StartHookFunction((PVOID*)(&oEndScene), hkEndScene);//继续HOOK
	//return result;
	return  0;
}


void InitD3d()
{
	AllocConsole();
	freopen("CON", "w", stdout);
	SetConsoleTitle("调试窗口");

	//获取目标游戏窗口句柄
	g_hWnd = FindWindowA("Direct3DWindowClass", NULL);
	//创建D3D设备对象
	g_Direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	// 初始化参数结构体
	memset(&g_present, 0, sizeof(g_present));
	g_present.Windowed = TRUE;
	g_present.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_present.BackBufferFormat = D3DFMT_UNKNOWN;
	g_present.EnableAutoDepthStencil = TRUE;
	g_present.AutoDepthStencilFormat = D3DFMT_D16;

	//创建D3D9设备标识
	HRESULT result = g_Direct3D9->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd, //窗口句柄
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&g_present,
		&g_pd3dDevice//重要指针  Reset 和 EndScene
	);


	//开始Hook对应的函数
	dDeviceVT = (DWORD*)*(DWORD*)g_pd3dDevice;
	oReset = (Reset_t)dDeviceVT[16];
	oEndScene = (EndScene_t)dDeviceVT[42];

	//Reset_t oReset;
	//EndScene_t oEndScene;



	Helpers::StartHookFunction((PVOID*)(&oReset), hkReset);
	Helpers::UnHookFunction((PVOID*)(&oEndScene), hkEndScene);



}
//void unLoad()
//{
//	Helpers::UnHookFunction((PVOID*)(&oReset), hkReset);
//	Helpers::UnHookFunction((PVOID*)(&oEndScene), hkEndScene);
//	//g_pd3dDevice->Release();
//	g_Direct3D9->Release();
//}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InitD3d, NULL, NULL, NULL);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:

		break;
	}
	return TRUE;
}

