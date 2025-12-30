// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#if defined(RNW_NEW_ARCH)

#include "codegen/react/components/DateTimePicker/DateTimePicker.g.h"

#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Windows.Globalization.h>
#include <winrt/Microsoft.ReactNative.Xaml.h>
#include <winrt/Microsoft.ReactNative.Composition.h>

namespace winrt::DateTimePicker {

// DateTimePickerComponentView implements the Fabric architecture for DateTimePicker
// using XAML CalendarDatePicker hosted in a XamlIsland
struct DateTimePickerComponentView : public winrt::implements<DateTimePickerComponentView, winrt::IInspectable>,
                                     Codegen::BaseDateTimePicker<DateTimePickerComponentView> {
  void InitializeContentIsland(
      const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView &islandView) noexcept;

  void RegisterEvents();

  void UpdateProps(
      const winrt::Microsoft::ReactNative::ComponentView &view,
      const winrt::com_ptr<Codegen::DateTimePickerProps> &newProps,
      const winrt::com_ptr<Codegen::DateTimePickerProps> &oldProps) noexcept override;

private:
  winrt::Microsoft::UI::Xaml::XamlIsland m_xamlIsland{nullptr};
  winrt::Microsoft::UI::Xaml::Controls::CalendarDatePicker m_calendarDatePicker{nullptr};
  int64_t m_timeZoneOffsetInSeconds = 0;
  bool m_updating = false;
};

} // namespace winrt::DateTimePicker

inline void RegisterDateTimePickerComponentView(winrt::Microsoft::ReactNative::IReactPackageBuilder const &packageBuilder) {
  winrt::DateTimePicker::Codegen::RegisterDateTimePickerNativeComponent<
      winrt::DateTimePicker::DateTimePickerComponentView>(
      packageBuilder,
      [](const winrt::Microsoft::ReactNative::Composition::IReactCompositionViewComponentBuilder &builder) {
        builder.as<winrt::Microsoft::ReactNative::IReactViewComponentBuilder>().XamlSupport(true);
        builder.SetContentIslandComponentViewInitializer(
            [](const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView &islandView) noexcept {
              auto userData = winrt::make_self<winrt::DateTimePicker::DateTimePickerComponentView>();
              userData->InitializeContentIsland(islandView);
              islandView.UserData(*userData);
            });
      });
}

#endif // defined(RNW_NEW_ARCH)
