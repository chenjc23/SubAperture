#include "fftw3.h"

#include "fftUtils.h"




///* �����Ӧmatlab�е�fft���������ʵ������ */
//template <typename T>
//void fft_c(T** inMatrix, int row, int col, int flag, cMatrix outMatrix) {
//	if (flag != 1 && flag != 2) throw("flag��־ѡ���Ϊ1��2");
//	fftw_complex* in, * out;
//	fftw_plan p{};
//
//	int num = (flag == 1) ? row : col;
//	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * num);
//	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * num);
//	// ��fft�任
//	if (flag == 1) {
//		// ����ÿһ����fft
//		for (int j = 0; j < col; j++) {
//			// ����ÿһ��Ϊ�ⲿ�������fftw_complex����
//			for (int i = 0; i < row; i++) {
//				in[i][0] = inMatrix[i][j];
//				in[i][1] = 0;
//			}
//			// ִ��fft����
//			p = fftw_plan_dft_1d(row, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
//			fftw_execute(p);
//			// ��������н�����и�ֵ
//			for (int i = 0; i < row; i++) {
//				outMatrix[i][j].real(out[i][0]);
//				outMatrix[i][j].imag(out[i][1]);
//			}
//		}
//	}
//	// ��fft�任
//	else {
//		for (int i = 0; i < row; i++) {
//			for (int j = 0; j < col; j++) {
//				in[j][0] = inMatrix[i][j];
//				in[j][1] = 0;
//			}
//			p = fftw_plan_dft_1d(col, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
//			fftw_execute(p);
//			for (int j = 0; j < col; j++) {
//				outMatrix[i][j].real(out[j][0]);
//				outMatrix[i][j].imag(out[j][1]);
//			}
//		}
//	}
//	fftw_destroy_plan(p);
//	fftw_free(in);
//	fftw_free(out);
//}

/* �����Ӧmatlab�е�fft��������Ը������� */
void fft_c(cMatrix inMatrix, int row, int col, int flag, cMatrix outMatrix) {
	if (flag != 1 && flag != 2) throw("flag��־ѡ���Ϊ1��2");
	fftw_complex* in, * out;
	fftw_plan p{};

	int num = (flag == 1) ? row : col;
	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * num);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * num);
	// ��fft�任
	if (flag == 1) {
		// ����ÿһ����fft
		for (int j = 0; j < col; j++) {
			// ����ÿһ��Ϊ�ⲿ�������fftw_complex����
			for (int i = 0; i < row; i++) {
				in[i][0] = inMatrix[i][j].real();
				in[i][1] = inMatrix[i][j].imag();
			}
			// ִ��fft����
			p = fftw_plan_dft_1d(row, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
			fftw_execute(p);
			// ��������н�����и�ֵ
			for (int i = 0; i < row; i++) {
				outMatrix[i][j].real(out[i][0]);
				outMatrix[i][j].imag(out[i][1]);
			}
		}
	}
	// ��fft�任
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

void ifft_c(cMatrix inMatrix, int row, int col, int flag, cMatrix outMatrix) {

}