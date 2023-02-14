#include "utils.h"


void SubApertureImaging(cMatrix data, int Na, int Nr, double Va, double startFreq, double PRF, double Kr, double fs, 
	double Rmax, double Rmin, int range_weight, int azm_weight) {

	/*参数预定义*/
	double Tp = Nr / fs;	// 脉冲宽度
	double BW = Kr * Tp;	// 带宽
	double fc = startFreq + BW / 2;		// 中心载频

	/*系统误差校正*/
	double R0SysError = 0.08;


}