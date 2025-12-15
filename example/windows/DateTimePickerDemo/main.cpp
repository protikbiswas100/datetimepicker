#include "pch.h"

#include <windows.h>
#include <winrt/Microsoft.ReactNative.h>
#include <winrt/Microsoft.ReactNative.Composition.h>
#include <winrt/Microsoft.UI.Composition.h>

#include "AutolinkedNativeModules.g.h"
#include "ReactPackageProvider.h"

using namespace winrt;
using namespace Microsoft::ReactNative;

// Forward declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

// Global React context
ReactNativeHost g_reactNativeHost;
HWND g_hwnd = nullptr;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, PWSTR /*pCmdLine*/, int nCmdShow) {
    // Initialize WinRT
    init_apartment();

    // Create window class
    const wchar_t CLASS_NAME[] = L"DateTimePickerDemoClass";
    
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    // Create the window
    g_hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"DateTimePicker Demo - Win32", // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 960, 640,
        
        nullptr,        // Parent window    
        nullptr,        // Menu
        hInstance,      // Instance handle
        nullptr         // Additional application data
    );

    if (g_hwnd == nullptr) {
        return 0;
    }

    ShowWindow(g_hwnd, nCmdShow);

    // Initialize React Native
    try {
        g_reactNativeHost = ReactNativeHost();
        
        // Configure bundle
        auto jsMainModuleName = L"index";
        g_reactNativeHost.InstanceSettings().JavaScriptBundleFile(jsMainModuleName);
        
        #if _DEBUG
        g_reactNativeHost.InstanceSettings().UseDirectDebugger(true);
        g_reactNativeHost.InstanceSettings().UseDeveloperSupport(true);
        #else
        g_reactNativeHost.InstanceSettings().UseDirectDebugger(false);
        g_reactNativeHost.InstanceSettings().UseDeveloperSupport(false);
        #endif

        // Register autolinked native modules
        auto packageProviders = g_reactNativeHost.PackageProviders();
        RegisterAutolinkedNativeModulePackages(packageProviders);
        
        // Register this app's package provider
        packageProviders.Append(make<DateTimePickerDemo::ReactPackageProvider>());

        // Initialize React
        g_reactNativeHost.LoadInstance();

        // Create XAML root view
        auto rootView = g_reactNativeHost.GetOrCreateRootView(
            L"DateTimePickerDemo",  // Component name from index.js
            g_hwnd                  // Parent HWND
        );

    } catch (const std::exception& ex) {
        MessageBoxA(
            g_hwnd,
            ex.what(),
            "React Native Error",
            MB_ICONERROR | MB_OK
        );
        return 1;
    }

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        
        case WM_SIZE: {
            if (g_reactNativeHost) {
                // Notify React of size changes
                RECT rect;
                GetClientRect(hwnd, &rect);
                // The RootView will handle resizing
            }
            return 0;
        }
        
        default:
            return DefWindowProc(hwnd, msg, wparam, lparam);
    }
}
