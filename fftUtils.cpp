#include "fftw3.h"
#include "fftUtils.h"
#include <cmath>


/* 构造对应matlab中的fft函数，针对复数矩阵 */
void fft_c(cMatrix inMatrix, int row, int col, int flag, cMatrix outMatrix) {
	if (flag != 1 && flag != 2) throw("flag标志选项仅为1或2");
	fftw_complex* in, * out;
	fftw_plan p{};

	int num = (flag == 1) ? row : col;
	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * num);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * num);
	// 列fft变换
	if (flag == 1) {
		// 遍历每一列做fft
		for (int j = 0; j < col; j++) {
			// 复制每一列为外部库所需的fftw_complex数组
			for (int i = 0; i < row; i++) {
				in[i][0] = inMatrix[i][j].real();
				in[i][1] = inMatrix[i][j].imag();
			}
			// 执行fft操作
			p = fftw_plan_dft_1d(row, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
			fftw_execute(p);
			// 对输出的列结果进行赋值
			for (int i = 0; i < row; i++) {
				outMatrix[i][j].real(out[i][0]);
				outMatrix[i][j].imag(out[i][1]);
			}
		}
	}
	// 行fft变换
	else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				in[j][0] = inMatrix[i][j].real();
				in[j][1] = inMatrix[i][j].imag();
			}
			p = fftw_plan_dft_1d(col, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
			fftw_execute(p);
			for (int j = 0; j < col; j++) {
				outMatrix[i][j].real(out[j][0]);
				outMatrix[i][j].imag(out[j][1]);
			}
		}
	}
	fftw_destroy_plan(p);
	fftw_free(in); 
	fftw_free(out);
}


/* 傅里叶逆变换 */
void ifft_c(cMatrix inMatrix, int row, int col, int flag, cMatrix outMatrix) {
	if (flag != 1 && flag != 2) throw("flag标志选项仅为1或2");
	fftw_complex* in, * out;
	fftw_plan p{};

	int num = (flag == 1) ? row : col;
	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * num);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * num);
	// 列fft变换
	if (flag == 1) {
		// 遍历每一列做fft
		for (int j = 0; j < col; j++) {
			// 复制每一列为外部库所需的fftw_complex数组
			for (int i = 0; i < row; i++) {
				in[i][0] = inMatrix[i][j].real();
				in[i][1] = inMatrix[i][j].imag();
			}
			// 执行fft操作
			p = fftw_plan_dft_1d(row, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
			fftw_execute(p);
			// 对输出的列结果进行赋值
			for (int i = 0; i < row; i++) {
				outMatrix[i][j].real(out[i][0] / row);
				outMatrix[i][j].imag(out[i][1] / row);
			}
		}
	}
	// 行fft变换
	else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				in[j][0] = inMatrix[i][j].real();
				in[j][1] = inMatrix[i][j].imag();
			}
			p = fftw_plan_dft_1d(col, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
			fftw_execute(p);
			for (int j = 0; j < col; j++) {
				outMatrix[i][j].real(out[j][0] / col);
				outMatrix[i][j].imag(out[j][1] / col);
			}
		}
	}
	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
}

double* hamming(int N) {
	double a = 0.54;
	double* win = new double[N];
	for (int i = 0; i < N; i++) {
		win[i] = a - (1.0 - a) * cos(2 * PI * i / (N - 1));
	}
	return win;
}