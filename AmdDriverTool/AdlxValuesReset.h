#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	bool MainPage::AdlxValuesReset()
	{
		//Check if variable is available
		if (ppGPUTuningServices == nullptr)
		{
			//Set result
			textblock_Status().Text(L"Tuning and fans not reset");
			AVDebugWriteLine(L"Tuning and fans not reset");
			return false;
		}

		//Reset gpu tuning and fan settings
		adlx_Res0 = ppGPUTuningServices->ResetToFactory(ppGpuInfo);
		if (ADLX_FAILED(adlx_Res0))
		{
			textblock_Status().Text(L"Tuning and fans reset failed");
			AVDebugWriteLine(L"Tuning and fans reset failed");
			return false;
		}
		else
		{
			textblock_Status().Text(L"Tuning and fans reset");
			AVDebugWriteLine(L"Tuning and fans reset");
			return true;
		}
	}
}