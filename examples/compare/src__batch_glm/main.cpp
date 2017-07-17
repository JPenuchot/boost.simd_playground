#include <array>
#include <numeric>

#include <glm/glm.hpp>

#include <iacaMarks.h>

int main(){
	const std::size_t N = 1024;

	glm::mat4 mat {
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	};

	std::array<float, 4 * N> vecarr;
	std::iota(vecarr.begin(), vecarr.end(), 0.f);

	for(std::size_t i = 0; i < 4 * N; i+=4){
		IACA_START
		glm::vec4 vec(0.f);

		vec.x = vecarr[i];
		vec.y = vecarr[i + 1];
		vec.z = vecarr[i + 2];
		vec.w = vecarr[i + 3];

		vec = vec * mat;

		vecarr[i] = vec.x;
		vecarr[i + 1] = vec.y;
		vecarr[i + 2] = vec.z;
		vecarr[i + 3] = vec.w;
	}
	
	IACA_END

	return 0;
}