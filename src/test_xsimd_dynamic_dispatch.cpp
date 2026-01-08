#include <vector>
#include <cstdint>
#include <iostream>

extern void test_simd_op(
    const int64_t* const input, const std::size_t count, int64_t* const output);


int main()
{
    std::vector<int64_t> input(1000);
    std::vector<int64_t> output(1000);
    test_simd_op(input.data(), input.size(), output.data());
    std::cout << "Test completed successfully." << std::endl;
    return 0;
}