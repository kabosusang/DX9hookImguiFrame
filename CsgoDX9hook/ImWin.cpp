#include "pch.h"
#include"ImWin.h"

bool mainBeginSate = TRUE;


void LoadMyWin()
{
	// ���濪ʼ����0
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	// ���ڴ�С
	ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(350, 450), ImGuiCond_FirstUseEver);

	ImGui::Begin(u8"��Ϸ��������", &mainBeginSate);



	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();//����
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());


}