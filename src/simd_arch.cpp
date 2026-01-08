#include "simd_impl.hpp"

template void _test_simd_op::operator()<xsimd::TEST_XSIMD_ARCH>(
    xsimd::TEST_XSIMD_ARCH, const int64_t *const input, const std::size_t count,
    int64_t *const output);