#include "utils.h"


void SubApertureImaging(cMatrix data, int Na, int Nr, double Va, double startFreq, double PRF, double Kr, double fs, 
	double Rmax, double Rmin, int range_weight, int azm_weight) {

	/*����Ԥ����*/
	double Tp = Nr / fs;	// ������
	double BW = Kr * Tp;	// ����
	double fc = startFreq + BW / 2;		// ������Ƶ

	/*ϵͳ���У��*/
	double R0SysError = 0.08;


}