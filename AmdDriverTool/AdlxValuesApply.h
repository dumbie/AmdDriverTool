#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	bool MainPage::AdlxValuesApply()
	{
		//Get fan manual tuning
		IADLXManualFanTuningPtr ppManualFanTuning;
		adlx_Res0 = ppGPUTuningServices->GetManualFanTuning(ppGpuInfo, (IADLXInterface**)&ppManualFanTuning);

		//Set fan zero rpm setting
		adlx_Res0 = ppManualFanTuning->SetZeroRPMState(toggleswitch_Fan_Zero_Rpm().IsOn());
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_Status().Text(L"Failed setting fan zero rpm");
			AVDebugWriteLine(L"Failed setting fan zero rpm");
			return false;
		}

		//Get empty fan curve
		IADLXManualFanTuningStatePtr ppFanState;
		IADLXManualFanTuningStateListPtr ppFanStates;
		adlx_Res0 = ppManualFanTuning->GetEmptyFanTuningStates(&ppFanStates);
		for (UINT i = 0; i < ppFanStates->Size(); i++)
		{
			ppFanStates->At(i, &ppFanState);
			if (i == 0)
			{
				ppFanState->SetFanSpeed((int)slider_Fan_Speed_0().Value());
				ppFanState->SetTemperature((int)slider_Fan_Temp_0().Value());
			}
			else if (i == 1)
			{
				ppFanState->SetFanSpeed((int)slider_Fan_Speed_1().Value());
				ppFanState->SetTemperature((int)slider_Fan_Temp_1().Value());
			}
			else if (i == 2)
			{
				ppFanState->SetFanSpeed((int)slider_Fan_Speed_2().Value());
				ppFanState->SetTemperature((int)slider_Fan_Temp_2().Value());
			}
			else if (i == 3)
			{
				ppFanState->SetFanSpeed((int)slider_Fan_Speed_3().Value());
				ppFanState->SetTemperature((int)slider_Fan_Temp_3().Value());
			}
			else if (i == 4)
			{
				ppFanState->SetFanSpeed((int)slider_Fan_Speed_4().Value());
				ppFanState->SetTemperature((int)slider_Fan_Temp_4().Value());
			}
		}

		//Validate fan curve
		adlx_Res0 = ppManualFanTuning->IsValidFanTuningStates(ppFanStates, &adlx_Int0);
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_Status().Text(L"Invalid fan curve");
			AVDebugWriteLine(L"Invalid fan curve");
			return false;
		}

		//Set fan curve
		adlx_Res0 = ppManualFanTuning->SetFanTuningStates(ppFanStates);
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_Status().Text(L"Failed setting fan curve");
			AVDebugWriteLine(L"Failed setting fan curve");
			return false;
		}

		//Set gpu clock setting
		IADLXManualGraphicsTuning2Ptr ppManualGFXTuning;
		adlx_Res0 = ppGPUTuningServices->GetManualGFXTuning(ppGpuInfo, (IADLXInterface**)&ppManualGFXTuning);
		adlx_Res0 = ppManualGFXTuning->SetGPUMinFrequency((int)slider_Core_Min().Value());
		adlx_Res0 = ppManualGFXTuning->SetGPUMaxFrequency((int)slider_Core_Max().Value());
		adlx_Res0 = ppManualGFXTuning->SetGPUVoltage((int)slider_Power_Voltage().Value());

		//Set gpu memory clock setting
		IADLXManualVRAMTuning2Ptr ppManualVRAMTuning;
		adlx_Res0 = ppGPUTuningServices->GetManualVRAMTuning(ppGpuInfo, (IADLXInterface**)&ppManualVRAMTuning);
		adlx_Res0 = ppManualVRAMTuning->SetMaxVRAMFrequency((int)slider_Memory_Max().Value());
		adlx_Res0 = ppManualVRAMTuning->SetMemoryTimingDescription((ADLX_MEMORYTIMING_DESCRIPTION)combobox_Memory_Timing().SelectedIndex());

		//Set gpu power setting
		IADLXManualPowerTuningPtr ppManualPowerTuning;
		adlx_Res0 = ppGPUTuningServices->GetManualPowerTuning(ppGpuInfo, (IADLXInterface**)&ppManualPowerTuning);
		adlx_Res0 = ppManualPowerTuning->SetPowerLimit((int)slider_Power_Limit().Value());

		textblock_Status().Text(L"Tuning and fans applied");
		AVDebugWriteLine(L"Tuning and fans applied");
		return true;
	}
}