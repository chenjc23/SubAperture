#pragma once
#include "fftw3.h"
#include <complex>
using namespace std;

#define PI 3.14159265358979323846
#define cMatrix complex<double>**			// 复数矩阵宏定义

// 矩阵内存的请求与释放函数模板
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

// 矩阵转置
template <typename T>
T** transpose(T** m, int row, int col) {
	T** m_trans = malloc_matrix<T>(col, row);
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			m_trans[i][j] = m[j][i];
		}
	}
	return m_trans;
}

// fft与ifft
void fft_c(cMatrix inMatrix, int row, int col, int flag, cMatrix outMatrix);
void ifft_c(cMatrix inMatrix, int row, int col, int flag, cMatrix outMatrix);

// 实数fft函数模板
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
	free_matrix(temp, row, col);
}

