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

	auto arr_beg = vecarr.data();
	auto arr_end = vecarr.data() + vecarr.size();

	for(; arr_beg + 16 <= arr_end; arr_beg+=16){
			IACA_START

			//	Unroll unroll unroll unroll...
			glm::vec4 vec0(0.f);
			glm::vec4 vec1(0.f);
			glm::vec4 vec2(0.f);
			glm::vec4 vec3(0.f);

			vec0.x = arr_beg[0];
			vec0.y = arr_beg[1];
			vec0.z = arr_beg[2];
			vec0.w = arr_beg[3];

			vec1.x = arr_beg[4];
			vec1.y = arr_beg[5];
			vec1.z = arr_beg[6];
			vec1.w = arr_beg[7];

			vec2.x = arr_beg[8];
			vec2.y = arr_beg[9];
			vec2.z = arr_beg[10];
			vec2.w = arr_beg[11];

			vec3.x = arr_beg[12];
			vec3.y = arr_beg[13];
			vec3.z = arr_beg[14];
			vec3.w = arr_beg[15];

			vec0 = vec0 * mat;
			vec1 = vec1 * mat;
			vec2 = vec2 * mat;
			vec3 = vec3 * mat;

			arr_beg[0] = vec0.x;
			arr_beg[1] = vec0.y;
			arr_beg[2] = vec0.z;
			arr_beg[3] = vec0.w;

			arr_beg[4] = vec1.x;
			arr_beg[5] = vec1.y;
			arr_beg[6] = vec1.z;
			arr_beg[7] = vec1.w;

			arr_beg[8] = vec2.x;
			arr_beg[9] = vec2.y;
			arr_beg[10] = vec2.z;
			arr_beg[11] = vec2.w;

			arr_beg[12] = vec3.x;
			arr_beg[13] = vec3.y;
			arr_beg[14] = vec3.z;
			arr_beg[15] = vec3.w;
		}

		IACA_END

		for(; arr_beg + 4 <= arr_end; arr_beg+=4){
			glm::vec4 vec0(0.f);
			
			vec0.x = arr_beg[0];
			vec0.y = arr_beg[1];
			vec0.z = arr_beg[2];
			vec0.w = arr_beg[3];

			vec0 = vec0 * mat;

			arr_beg[0] = vec0.x;
			arr_beg[1] = vec0.y;
			arr_beg[2] = vec0.z;
			arr_beg[3] = vec0.w;
		}
	
	

	return 0;
}