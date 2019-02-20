#include "pal.h"
#include "winrt/base.h"

// test_component_dll is a WinRT component. xlang's get activation factory has
// a different signature, so we need to adapt xlang's function to winrt's until
// we have a C++/xlang projection.

extern int32_t WINRT_CALL WINRT_GetActivationFactory(void* classId, void** factory) noexcept;

xlang_error_info* XLANG_CALL XLANG_get_activation_factory(xlang_string class_name, xlang_guid const& iid, void** factory)  XLANG_NOEXCEPT
{
    winrt::Windows::Foundation::IUnknown temp_factory{};
    winrt::check_hresult(WINRT_GetActivationFactory(class_name, winrt::put_abi(temp_factory)));

    xlang_unknown* unk = (xlang_unknown*)winrt::get_abi(temp_factory);
    winrt::check_hresult(unk->QueryInterface(iid, factory));

    return xlang_error_ok;
}
