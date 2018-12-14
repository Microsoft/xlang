#include "pch.h"
#include "winrt/Windows.Foundation.h"

using namespace winrt;
using namespace Windows::Foundation;

namespace
{
    // Some custom exception type unknown to C++/WinRT
    struct WilException
    {
    };

    struct Sample : implements<Sample, IStringable>
    {
        hstring ToString()
        {
            // Throw custom exception inside C++/WinRT projection
            throw WilException();
        }
    };

    // Global handler to translate custom exception
    int32_t WINRT_CALL handler(void* address) noexcept
    {
        REQUIRE(address);

        try
        {
            throw;
        }
        catch (WilException)
        {
            return 0x80000018; // E_ILLEGAL_DELEGATE_ASSIGNMENT
        }

        REQUIRE(false);
        return 0;
    }
}

TEST_CASE("Wil")
{
    // Set up global handler
    REQUIRE(!winrt_to_hresult_handler);
    winrt_to_hresult_handler = handler;

    // Validate that handler translated exception
    REQUIRE_THROWS_AS(make<Sample>().ToString(), hresult_illegal_delegate_assignment);

    // Remove global handler
    winrt_to_hresult_handler = nullptr;
}
