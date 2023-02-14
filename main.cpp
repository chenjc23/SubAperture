#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>	// for exit
#include <complex>
#include <cmath>
#include "utils.h"
#include "fftUtils.h"
#include "fftw3.h"

using namespace std;

int main(){
	/*----------------- 数据提取 --------------------*/
	// 读取dat文件
	const char* dataPath = "./test.dat";
	ifstream fin;
	fin.open(dataPath, ios_base::in | ios_base::binary);

	if (!fin.is_open()) {
		cerr << "Can't open " << dataPath << "for read!" << endl;
		exit(EXIT_FAILURE);
	}

	// 读取文件中前7个double型雷达参数
	double frontParams[7];
	fin.read((char*)frontParams, 7*sizeof(double));

	double startFreq = frontParams[0] * 1e6;
	double stopFreq = frontParams[1] * 1e6;
	double pulseWidth = frontParams[2] * 1e-3;
	double PRF = frontParams[3];
	double channelGain = frontParams[4];
	double ADFreq = frontParams[5] * 1e6;
	double Va = frontParams[6];
	Va = 0.10;

	// 读取文件中后3个雷达参数
	int samplePerRecord, pulseNum;
	double lamda;
	fin.read((char*)&samplePerRecord, sizeof(int));
	fin.read((char*)&pulseNum, sizeof(int));
	fin.read((char*)&lamda, sizeof(double));

	// 根据上述部分参数提取原始雷达回波数据，读数据的时候Nr为行
	int16_t ** rawData = new int16_t*[samplePerRecord];
	for (int i = 0; i < samplePerRecord; i++) {
		int16_t* tempLine = new int16_t[pulseNum];
		fin.read((char*)tempLine, pulseNum * sizeof(int16_t));
		rawData[i] = tempLine;
	}
	// 已读取所有数据，关闭文件连接
	fin.close();

	/*----------------- 原始数据预处理 --------------------*/
	cMatrix tempData = malloc_matrix<complex<double>>(samplePerRecord, pulseNum);
	fft_c(rawData, samplePerRecord, pulseNum, 1, tempData);
	// 取一半的有效带宽做ifft
	cMatrix proData = malloc_matrix<complex<double>>(round(samplePerRecord /2), pulseNum);
	ifft_c(tempData, round(samplePerRecord / 2), pulseNum, 1, proData);
	// 舍弃刚开始采集的一段时间的数据


	// 成像需转置为Na为行
	cMatrix transData = transpose(proData, round(samplePerRecord / 2), pulseNum);

	free_matrix(tempData, samplePerRecord, pulseNum);
	free_matrix(proData, round(samplePerRecord / 2), pulseNum);

	/*----------------- 成像参数预定义 --------------------*/
	double Na = pulseNum;
	double Nr = round(samplePerRecord / 2);
	double KFMCW = (stopFreq - startFreq) / pulseWidth;
	double fs = ADFreq / 2;
	double Rmax = 500;
	double Rmin = 50;
	int range_weight = 2;
	int azm_weight = 2;

	// 调用子孔径成像算法
	SubApertureImaging(transData, Na, Nr, Va, startFreq, PRF, KFMCW, fs, 
						Rmax, Rmin, range_weight, azm_weight);




	
	

	return 0;
}