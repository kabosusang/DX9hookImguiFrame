#include"pch.h"
#include "Helpers.h"

void Helpers::StartHookFunction(PVOID* OldFunction, PVOID NEWFunction)
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(OldFunction, NEWFunction);
	DetourTransactionCommit();


}

void Helpers::UnHookFunction(PVOID* OldFunction, PVOID NEWFunction)
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(OldFunction, NEWFunction);
	DetourTransactionCommit();

}
