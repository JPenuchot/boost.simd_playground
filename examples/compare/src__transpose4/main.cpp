
#include <iostream>
#include <algorithm>

#include <boost/simd/pack.hpp>
#include <boost/simd/reduction.hpp>

#include <playground/graphics/types.hpp>

#include <playground/graphics/memory/load.hpp>
#include <playground/graphics/helper/transpose.hpp>

#include <iacaMarks.h>

int main(){
    using namespace pg::graphics;
    namespace bs = boost::simd;

    alignas(32) float arr[16] = {
        0.f, 1.f, 2.f, 3.f,
        4.f, 5.f, 6.f, 7.f,
        8.f, 9.f, 10.f, 11.f,
        12.f, 13.f, 14.f, 15.f
    };

    mat4<float> A(arr);

    IACA_START

    pg::graphics::transpose4(A, A);

    IACA_END

    std::cout
        << A << '\n';
}
