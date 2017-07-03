#include <boost/simd/pack.hpp>

#include <iostream>

#include <playground/pmat_r.hpp>

#include <cblas.h>

int main(){
	pg::pmat_r<float, 10, 10> pmattest;
	pmattest.fill(0.f);
}
