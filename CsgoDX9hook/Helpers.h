#pragma once
#include"pch.h"

class Helpers
{
public:

	static void StartHookFunction(PVOID* OldFunction, PVOID NEWFunction);
	static void UnHookFunction(PVOID* OldFunction, PVOID NEWFunction);


};

