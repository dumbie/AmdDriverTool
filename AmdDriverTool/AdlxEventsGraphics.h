#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::toggleswitch_EnhancedSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get enhanced sync settings
		IADLX3DEnhancedSyncPtr pp3DEnhancedSync;
		adlx_Res0 = pp3DSettingsServices->GetEnhancedSync(ppGpuInfo, &pp3DEnhancedSync);

		if (sender.as<ToggleSwitch>().IsOn())
		{
			adlx_Res0 = pp3DEnhancedSync->SetEnabled(true);
			textblock_Status().Text(L"Enhanced Sync enabled");
			AVDebugWriteLine(L"Enhanced Sync enabled");
		}
		else
		{
			adlx_Res0 = pp3DEnhancedSync->SetEnabled(false);
			textblock_Status().Text(L"Enhanced Sync disabled");
			AVDebugWriteLine(L"Enhanced Sync disabled");
		}
	}

	void MainPage::combobox_VerticalRefresh_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get vertical refresh value
		auto newValue = sender.as<ComboBox>().SelectedIndex();

		//Set vertical refresh setting
		IADLX3DWaitForVerticalRefreshPtr pp3DWaitForVerticalRefresh;
		adlx_Res0 = pp3DSettingsServices->GetWaitForVerticalRefresh(ppGpuInfo, &pp3DWaitForVerticalRefresh);
		adlx_Res0 = pp3DWaitForVerticalRefresh->SetMode((ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE)newValue);
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_Status().Text(L"Failed setting vertical refresh");
			AVDebugWriteLine(L"Failed setting vertical refresh");
		}
		else
		{
			//Set result
			textblock_Status().Text(L"Vertical refresh set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"Vertical refresh set to " << newValue);
		}
	}

	void MainPage::toggleswitch_RadeonChill_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Get chill settings
		IADLX3DChillPtr pp3DChill;
		adlx_Res0 = pp3DSettingsServices->GetChill(ppGpuInfo, &pp3DChill);

		if (sender.as<ToggleSwitch>().IsOn())
		{
			adlx_Res0 = pp3DChill->SetEnabled(true);
			slider_RadeonChill_Min().IsEnabled(true);
			slider_RadeonChill_Max().IsEnabled(true);
			textblock_Status().Text(L"Radeon Chill enabled");
			AVDebugWriteLine(L"Radeon Chill enabled");
		}
		else
		{
			adlx_Res0 = pp3DChill->SetEnabled(false);
			slider_RadeonChill_Min().IsEnabled(false);
			slider_RadeonChill_Max().IsEnabled(false);
			textblock_Status().Text(L"Radeon Chill disabled");
			AVDebugWriteLine(L"Radeon Chill disabled");
		}
	}

	void MainPage::slider_RadeonChill_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Convert new value
		int newValue = (int)e.NewValue();

		//Set chill settings
		IADLX3DChillPtr pp3DChill;
		adlx_Res0 = pp3DSettingsServices->GetChill(ppGpuInfo, &pp3DChill);
		adlx_Res0 = pp3DChill->SetMinFPS(newValue);
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_RadeonChill_Min().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
			textblock_Status().Text(L"Failed setting chill fps");
			AVDebugWriteLine(L"Failed setting chill fps");
		}
		else
		{
			//Match values
			if (newValue > slider_RadeonChill_Max().Value())
			{
				slider_RadeonChill_Max().Value(newValue);
			}

			//Set result
			textblock_RadeonChill_Min().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
			textblock_Status().Text(L"Chill minimum set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"Chill minimum set to " << newValue);
		}
	}

	void MainPage::slider_RadeonChill_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		//Check if saving is disabled
		if (disable_saving) { return; }

		//Convert new value
		int newValue = (int)e.NewValue();

		//Set chill setting
		IADLX3DChillPtr pp3DChill;
		adlx_Res0 = pp3DSettingsServices->GetChill(ppGpuInfo, &pp3DChill);
		adlx_Res0 = pp3DChill->SetMaxFPS(newValue);
		if (ADLX_FAILED(adlx_Res0))
		{
			//Set result
			textblock_RadeonChill_Max().Foreground(SolidColorBrush(Windows::UI::Colors::Red()));
			textblock_Status().Text(L"Failed setting chill fps");
			AVDebugWriteLine(L"Failed setting chill fps");
		}
		else
		{
			//Match values
			if (newValue < slider_RadeonChill_Min().Value())
			{
				slider_RadeonChill_Min().Value(newValue);
			}

			//Set result
			textblock_RadeonChill_Max().Foreground(SolidColorBrush(Windows::UI::Colors::Green()));
			textblock_Status().Text(L"Chill maximum set to " + number_to_wstring(newValue));
			AVDebugWriteLine(L"Chill maximum set to " << newValue);
		}
	}
}