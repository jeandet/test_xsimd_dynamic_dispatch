#pragma once
#include <xsimd/xsimd.hpp>
#include <cstdint>
#include <iostream>

struct _test_simd_op
{
    template <class Arch>
    void operator()(
        Arch, const int64_t* const input, const std::size_t count, int64_t* const output);
};

template <class Arch>
void _test_simd_op::operator()(
    Arch, const int64_t* const input, const std::size_t count, int64_t* const output)
{
    using batch_type = xsimd::batch<int64_t, Arch>;
    constexpr std::size_t batch_size = batch_type::size;
    std::cout << "Using architecture: " << Arch::name() << " with batch size " << batch_size << std::endl;
    std::size_t i = 0;
    for (; i + batch_size <= count; i += batch_size)
    {
        batch_type in = batch_type::load_unaligned(input + i);
        batch_type out = in + batch_type(1);
        out.store_unaligned(output + i);
    }
    for (; i < count; ++i)
    {
        output[i] = input[i] + 1;
    }
}

#ifdef TEST_XSIMD_ENABLE_SSE2_ARCH
extern template void _test_simd_op::operator()<xsimd::sse2>(
    xsimd::sse2, const int64_t* const input, const std::size_t count, int64_t* const output);
#endif
#ifdef TEST_XSIMD_ENABLE_AVX2_ARCH
extern template void _test_simd_op::operator()<xsimd::avx2>(
    xsimd::avx2, const int64_t* const input, const std::size_t count, int64_t* const output);
#endif
#ifdef TEST_XSIMD_ENABLE_AVX512_ARCH
extern template void _test_simd_op::operator()<xsimd::avx512f>(
    xsimd::avx512f, const int64_t* const input, const std::size_t count, int64_t* const output);
#endif
#ifdef TEST_XSIMD_ENABLE_AVX512BW_ARCH
extern template void _test_simd_op::operator()<xsimd::avx512bw>(
    xsimd::avx512bw, const int64_t* const input, const std::size_t count, int64_t* const output);
#endif