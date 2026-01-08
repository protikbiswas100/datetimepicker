// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#if defined(RNW_NEW_ARCH)

#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.ReactNative.h>
#include <winrt/Microsoft.ReactNative.Composition.h>

namespace winrt::DateTimePicker {

// TimePickerComponentView implements the Fabric architecture for TimePicker
// using XAML TimePicker hosted in a XamlIsland
struct TimePickerComponentView : public winrt::implements<TimePickerComponentView, winrt::IInspectable> {
  void InitializeContentIsland(
      const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView &islandView) noexcept;

  void RegisterEvents();

  void UpdateProps(
      const winrt::Microsoft::ReactNative::ComponentView &view,
      const winrt::Microsoft::ReactNative::IJSValueReader &propsReader) noexcept;

  void SetEventEmitter(
      winrt::Microsoft::ReactNative::Composition::ViewComponentView::EventEmitterDelegate const &eventEmitter) noexcept;

private:
  winrt::Microsoft::UI::Xaml::XamlIsland m_xamlIsland{nullptr};
  winrt::Microsoft::UI::Xaml::Controls::TimePicker m_timePicker{nullptr};
  winrt::Microsoft::UI::Xaml::Controls::TimePicker::TimeChanged_revoker m_timeChangedRevoker;
  winrt::Microsoft::ReactNative::Composition::ViewComponentView::EventEmitterDelegate m_eventEmitter;
};

} // namespace winrt::DateTimePicker

// Registers the TimePicker component view with the React Native package builder
void RegisterTimePickerComponentView(winrt::Microsoft::ReactNative::IReactPackageBuilder const &packageBuilder);

#endif // defined(RNW_NEW_ARCH)
