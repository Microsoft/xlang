﻿#include "pch.h"
#include "$safeitemname$.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::$rootnamespace$::implementation
{
    $safeitemname$::$safeitemname$()
    {
        InitializeComponent();
    }

    int32_t $safeitemname$::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void $safeitemname$::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void $safeitemname$::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
