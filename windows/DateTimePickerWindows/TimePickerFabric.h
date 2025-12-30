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
  bool m_updating = false;
  winrt::Microsoft::ReactNative::Composition::ViewComponentView::EventEmitterDelegate m_eventEmitter;
};

} // namespace winrt::DateTimePicker

inline void RegisterTimePickerComponentView(winrt::Microsoft::ReactNative::IReactPackageBuilder const &packageBuilder) {
  packageBuilder.as<winrt::Microsoft::ReactNative::IReactPackageBuilderFabric>().AddViewComponent(
      L"RNTimePickerWindows",
      [](winrt::Microsoft::ReactNative::IReactViewComponentBuilder const &builder) noexcept {
        builder.XamlSupport(true);
        auto compBuilder = builder.as<winrt::Microsoft::ReactNative::Composition::IReactCompositionViewComponentBuilder>();

        compBuilder.SetContentIslandComponentViewInitializer(
            [](const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView &islandView) noexcept {
              auto userData = winrt::make_self<winrt::DateTimePicker::TimePickerComponentView>();
              userData->InitializeContentIsland(islandView);
              islandView.UserData(*userData);
            });

        builder.SetUpdatePropsHandler([](const winrt::Microsoft::ReactNative::ComponentView &view,
                                         const winrt::Microsoft::ReactNative::IComponentProps &newProps,
                                         const winrt::Microsoft::ReactNative::IComponentProps &oldProps) noexcept {
          auto userData = view.UserData().as<winrt::DateTimePicker::TimePickerComponentView>();
          auto reader = newProps.as<winrt::Microsoft::ReactNative::IComponentProps>().try_as<winrt::Microsoft::ReactNative::IJSValueReader>();
          if (reader) {
            userData->UpdateProps(view, reader);
          }
        });

        compBuilder.SetUpdateEventEmitterHandler([](const winrt::Microsoft::ReactNative::ComponentView &view,
                                                    const winrt::Microsoft::ReactNative::Composition::ViewComponentView::EventEmitterDelegate &eventEmitter) noexcept {
          auto userData = view.UserData().as<winrt::DateTimePicker::TimePickerComponentView>();
          userData->SetEventEmitter(eventEmitter);
        });
      });
}

#endif // defined(RNW_NEW_ARCH)
