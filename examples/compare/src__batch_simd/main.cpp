#include <array>
#include <numeric>

#include <playground/graphics/mat4x4.hpp>
#include <playground/graphics/mat3x3.hpp>

#include <playground/graphics/vec3.hpp>
#include <playground/graphics/vec4.hpp>

#include <playground/graphics/algebra/batch/matvec.hpp>
#include <playground/graphics/algebra/batch/vecmat.hpp>

#include <iacaMarks.h>

int main(){
	const std::size_t N = 1024;

	namespace pgg = pg::graphics;

	pgg::mat4<float> mat {
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	};

	std::array<float, 4 * N> vec;
	std::iota(vec.begin(), vec.end(), 0.f);

	pgg::batch_vecmat4(mat, vec.data(), N, vec.data());	

	return 0;
}