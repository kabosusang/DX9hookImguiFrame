#include "pch.h"
#include"ImWin.h"

bool mainBeginSate = TRUE;


void LoadMyWin()
{
	// 界面开始绘制0
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	// 窗口大小
	ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(350, 450), ImGuiCond_FirstUseEver);

	ImGui::Begin(u8"游戏辅助窗口", &mainBeginSate);



	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();//绘制
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());


}