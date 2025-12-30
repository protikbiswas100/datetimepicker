// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

// TimePickerFabric: Fabric component implementation for declarative <DateTimePicker mode="time"/> usage
// This is NOT the TurboModule - see TimePickerModuleWindows.cpp for imperative API
// This provides declarative component rendering using XAML Islands

#include "pch.h"

#include "TimePickerFabric.h"

#if defined(RNW_NEW_ARCH)

#include <winrt/Microsoft.ReactNative.Xaml.h>

namespace winrt::DateTimePicker {

// TimePickerComponentView method implementations

void TimePickerComponentView::InitializeContentIsland(
    const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView &islandView) noexcept {
  m_xamlIsland = winrt::Microsoft::UI::Xaml::XamlIsland{};
  m_timePicker = winrt::Microsoft::UI::Xaml::Controls::TimePicker{};
  islandView.Connect(m_xamlIsland.ContentIsland());

  RegisterEvents();
  
  // Mount the TimePicker immediately so it's visible
  m_xamlIsland.Content(m_timePicker);
}

void TimePickerComponentView::RegisterEvents() {
  // Register the TimeChanged event handler
  m_timePicker.TimeChanged([this](auto &&sender, auto &&args) {
    if (m_updating) {
      return;
    }

    if (m_eventEmitter) {
      auto newTime = args.NewTime();
      
      // Convert TimeSpan to hour and minute
      auto totalMinutes = newTime.count() / 10000000 / 60; // 100-nanosecond intervals to minutes
      auto hour = static_cast<int32_t>(totalMinutes / 60);
      auto minute = static_cast<int32_t>(totalMinutes % 60);
      
      winrt::Microsoft::ReactNative::JSValueObject eventData;
      eventData["hour"] = hour;
      eventData["minute"] = minute;
      
      m_eventEmitter(L"topChange", std::move(eventData));
    }
  });
}

void TimePickerComponentView::UpdateProps(
    const winrt::Microsoft::ReactNative::ComponentView &view,
    const winrt::Microsoft::ReactNative::IJSValueReader &propsReader) noexcept {
  
  m_updating = true;

  const winrt::Microsoft::ReactNative::JSValueObject props =
      winrt::Microsoft::ReactNative::JSValueObject::ReadFrom(propsReader);

  // Update clock format (12-hour vs 24-hour)
  if (props.find("is24Hour") != props.end()) {
    bool is24Hour = props["is24Hour"].AsBoolean();
    m_timePicker.ClockIdentifier(
        is24Hour 
            ? winrt::to_hstring("24HourClock")
            : winrt::to_hstring("12HourClock"));
  }

  // Update minute increment
  if (props.find("minuteInterval") != props.end()) {
    int32_t minuteInterval = static_cast<int32_t>(props["minuteInterval"].AsInt64());
    m_timePicker.MinuteIncrement(minuteInterval);
  }

  // Update selected time
  if (props.find("selectedTime") != props.end()) {
    int64_t timeInMilliseconds = props["selectedTime"].AsInt64();
    auto timeInSeconds = timeInMilliseconds / 1000;
    auto hours = (timeInSeconds / 3600) % 24;
    auto minutes = (timeInSeconds / 60) % 60;
    
    // Create TimeSpan (100-nanosecond intervals)
    winrt::Windows::Foundation::TimeSpan timeSpan{
        static_cast<int64_t>((hours * 3600 + minutes * 60) * 10000000)
    };
    m_timePicker.Time(timeSpan);
  }

  m_updating = false;
}

void TimePickerComponentView::SetEventEmitter(
    winrt::Microsoft::ReactNative::Composition::ViewComponentView::EventEmitterDelegate const &eventEmitter) noexcept {
  m_eventEmitter = eventEmitter;
}

} // namespace winrt::DateTimePicker

#endif // defined(RNW_NEW_ARCH)
