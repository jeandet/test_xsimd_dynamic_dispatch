#include "simd_impl.hpp"

auto _disp__test_simd_op
    = xsimd::dispatch<TEST_XSIMD_ARCH_LIST>(_test_simd_op {});

void test_simd_op(
    const int64_t* const input, const std::size_t count, int64_t* const output)
{
    _disp__test_simd_op(input, count, output);
}