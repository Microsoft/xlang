﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#ifndef WINRT_Component_Structs_2_H
#define WINRT_Component_Structs_2_H
#include "winrt/impl/Component.Structs.1.h"
namespace winrt::Component::Structs
{
    struct Simple
    {
        uint8_t A;
        uint8_t R;
        uint8_t G;
        uint8_t B;
    };
    inline bool operator==(Simple const& left, Simple const& right) noexcept
    {
        return left.A == right.A && left.R == right.R && left.G == right.G && left.B == right.B;
    }
    inline bool operator!=(Simple const& left, Simple const& right) noexcept
    {
        return !(left == right);
    }
}
#endif
