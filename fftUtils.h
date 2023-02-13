#pragma once
#include "fftw3.h"
#include <complex>
using namespace std;

#define cMatrix complex<double>**			// ¸´Êý¾ØÕóºê¶¨Òå


template <typename T>
T** malloc_matrix(int row, int col) {
	T** m = new T * [row];
	for (int i = 0; i < row; i++) {
		m[i] = new T[col];
	}
	return m;
}

template <typename T>
void free_matrix(T m, int row, int col) {
	for (int i = 0; i < row; i++) {
		delete[] m[i];
	}
	delete[] m;
}

void fft_c(cMatrix inMatrix, int row, int col, int flag, cMatrix outMatrix);

template <typename T>
void fft_c(T** inMatrix, int row, int col, int flag, cMatrix outMatrix) {
	cMatrix temp = malloc_matrix<complex<double>>(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			temp[i][j].real(inMatrix[i][j]);
			temp[i][j].imag(0);
		}
	}
	fft_c(temp, row, col, flag, outMatrix);
}

