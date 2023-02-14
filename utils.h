#pragma once
#include "fftUtils.h"

#define c 3e8


void SubApertureImaging(cMatrix data, int Na, int Nr, double Va, double startFreq, double PRF, double Kr, double fs,
	double Rmax, double Rmin, int range_weight, int azm_weight);

